/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2024 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "t85apu.h"
#include "sound/attiny85apu/t85apu.h"
#include "sound/attiny85apu/t85apu_regdefines.h"
#include "../engine.h"
#include "IconsFontAwesome4.h"
#include <math.h>
#include "../../ta-log.h"

/*  reg map lmao
___________ _______ _______________________________________________________________
|           | Bit → |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
|   Index   |  Name |=======|=======|=======|=======|=======|=======|=======|=======|
|   0x0n    | PILOX |          Pitch increment value for tone on channel X          |    n = 0..4, X = A..E
|   0x05    | PILON |           Pitch increment value for noise generator           |
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x06    | PHIAB |Ch.B PR|Channel B octave number|Ch.A PR|Channel A octave number|
|   0x07    | PHICD |Ch.D PR|Channel D octave number|Ch.C PR|Channel C octave number|
|   0x08    | PHIEN |NoisePR|Noise gen octave number|Ch.E PR|Channel E octave number|
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x0n    | DUTYX |                   Channel X tone duty cycle                   |    n = 9..D, X = A..E
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x0E    | NTPLO |             Noise LFSR inversion value (low byte)             |
|   0x0F    | NTPHI |             Noise LFSR inversion value (high byte)            |
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x1n    | VOLX  |                    Channel X static volume                    |    n = 0..4, X = A..E
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x1n    | CFGX  |NoiseEn| EnvEn |Env/Smp| Slot# |  Right volume |  Left volume  |    n = 5..9, X = A..E
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x1A    | ELLO  |             Low byte of envelope phase load value             |
|   0x1B    | ELHI  |            High byte of envelope phase load value             |
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x1C    | ESHP  |EnvB PR|    Envelope B shape   |EnvA PR|    Envelope A shape   |
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x1D    | EPLA  |             Pitch increment value for envelope A              |
|   0x1E    | EPLB  |             Pitch increment value for envelope B              |
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|   0x1F    | EPH   |     Envelope B octave num     |     Envelope A octave num     |
|===========|=======|=======|=======|=======|=======|=======|=======|=======|=======|
|___________|_______|_______|_______|_______|_______|_______|_______|_______|_______| */

#define my_min(a, b) (((a) < (b)) ? (a) : (b))
#define my_max(a, b) (((a) > (b)) ? (a) : (b))

#define CHIP_FREQBASE 524288
#define CHIP_FREQBASE_ENV CHIP_FREQBASE*256

#define CHIP_DEFAULTCLOCK 8000000

#define T85_OUTPUT_IDEAL_PB4 0
#define T85_OUTPUT_EARRAPE_FUCKING_31kHz_PWM 1

#define NOISE_CH 5
#define ENV_CH_START 6
#define ENV_A_CH 6
#define ENV_B_CH 7

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }

void DivPlatformT85APU::acquire(short** buf, size_t len) 
{
  static uint32_t cycle;
  cycle = 0;
  for (size_t h=0; h<len; h++) 
  {
    if((cycle == 511) || audio_type == T85_OUTPUT_IDEAL_PB4)
    {
      if (!writes.empty()) 
      {
        QueuedWrite w=writes.front();
        t85APU_writeReg(t85_synth, w.addr, w.val);
        regPool[w.addr&0x1f]=w.val;
        writes.pop();
      }
    }

    if(audio_type == T85_OUTPUT_EARRAPE_FUCKING_31kHz_PWM)
    {
      cycle++;
      if(cycle > 511) cycle = 0;
    }

    for(int i = 0; i < chipClock / rate; i++)
    {
      t85APU_tick(t85_synth);
    }

    for (int j=0; j<T85APU_NUM_REAL_CHANS; j++) //without noise and env channels...
    {
      oscBuf[j]->data[oscBuf[j]->needle++]=isMuted[j] ? 0 : (t85_synth->channelOutput[j])<<5; // Tone channels
    }
    oscBuf[ENV_A_CH]->data[oscBuf[ENV_A_CH]->needle++]=isMuted[ENV_A_CH] ? 0 : (t85_synth->envSmpVolume[0])<<7;  // Envelope A
    oscBuf[ENV_B_CH]->data[oscBuf[ENV_B_CH]->needle++]=isMuted[ENV_B_CH] ? 0 : (t85_synth->envSmpVolume[1])<<7;  // Envelope B

    oscBuf[NOISE_CH]->data[oscBuf[NOISE_CH]->needle++]=(t85_synth->noiseMask&0x80 && !isMuted[NOISE_CH] ) ? INT16_MAX : 0; // Noise

    buf[0][h]=t85_synth->currentOutput << ((16-1)-t85_synth->outputBitdepth);
    buf[1][h]=t85_synth->currentOutput << ((16-1)-t85_synth->outputBitdepth);
  }
}

void DivPlatformT85APU::tick(bool sysTick) 
{
  for (int i=0; i<T85APU_NUM_CHANS; i++) 
  {
    chan[i].std.next();

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->had) \
    {
      if(i < T85APU_NUM_REAL_CHANS)
      {
        chan[i].outVol=VOL_SCALE_LINEAR(chan[i].vol&255,MIN(255,chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->val),255);
        rWrite(VOL_A + i, chan[i].outVol);
      }
    }

    if (NEW_ARP_STRAT) {
      chan[i].handleArp();
    } else if (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->had) {
      if (!chan[i].inPorta) {
        chan[i].baseFreq=NOTE_FREQUENCY(parent->calcArp(chan[i].note,chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val));
      }
      chan[i].freqChanged=true;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->had) {
      if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->mode) {
        chan[i].pitch2+=chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
        CLAMP_VAR(chan[i].pitch2,-65535,65535);
      } else {
        chan[i].pitch2=chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
      }
      chan[i].freqChanged=true;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->had) 
    {
      if(i < T85APU_NUM_REAL_CHANS)
      {
        chan[i].duty=chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val & 255;
        rWrite(DUTYA + i, chan[i].duty);
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->had) 
    {
      if(i < T85APU_NUM_REAL_CHANS)
      {
        chan[i].tone = chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->val&1;
        chan[i].noise = chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->val&2;
        chan[i].envelope = chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->val&4;

        rWrite(CFG_A + i, 
          (chan[i].noise && !isMuted[NOISE_CH] ? 1<<NOISE_EN : 0) | 
          (chan[i].envelope && !isMuted[ENV_CH_START+chan[i].env_num] ? 1<<ENV_EN : 0) | (chan[i].env_num << SLOT_NUM) | 0xF);

        if(chan[i].envelope)
        {
          switch(chan[i].env_num)
          {
            case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
            case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
            default: break;
          }
        }

        if(!chan[i].tone) //disable tone
        {
          rWrite(PILOA + i, 0); //0 freq

          if(chan[i].noise) //write proper duty
          {
            rWrite(DUTYA + i, 0);
          }
          else
          {
            rWrite(DUTYA + i, 0xff);
          }

          chan[i].enabled = false; //so subsequent pitch changes do not break 0 freq

          switch(i) //do phase reset
          {
            case 0: rWrite(PHIAB, (0 >> 8) | ((chan[1].freq >> 8) << 4) | 0x8); break;
            case 1: rWrite(PHIAB, (chan[0].freq >> 8) | ((0 >> 8) << 4) | 0x80); break;

            case 2: rWrite(PHICD, (0 >> 8) | ((chan[3].freq >> 8) << 4) | 0x8); break;
            case 3: rWrite(PHICD, (chan[2].freq >> 8) | ((0 >> 8) << 4) | 0x80); break;

            case 4: rWrite(PHIEN, (0 >> 8) | ((chan[NOISE_CH].freq >> 8) << 4) | 0x8); break;
            default: break;
          }
        }

        if(chan[i].tone)
        {
          chan[i].enabled = true;
          chan[i].freqChanged = true;
          rWrite(DUTYA + i, chan[i].duty); //restore duty!
        }
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->had) 
    {
      if(i == ENV_A_CH || i == ENV_B_CH)
      {
        env_shape[i-ENV_CH_START] = chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->val&7;

        rWrite(E_SHP, (env_shape[1] << 4) | env_shape[0]);
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX2)->had) 
    {
      if(i == NOISE_CH)
      {
        int bits = chan[i].std.get_div_macro_struct(DIV_MACRO_EX2)->val;
        noise_lsfr_feedback_bits = bits;

        rWrite(NTPLO, bits & 0xff);
        rWrite(NTPHI, bits >> 8);
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX3)->had) 
    {
      if(i < T85APU_NUM_REAL_CHANS)
      {
        int bits = chan[i].std.get_div_macro_struct(DIV_MACRO_EX3)->val;
        env_init_phase[chan[i].env_num] = bits;

        rWrite(ELDLO, bits & 0xff);
        rWrite(ELDHI, bits >> 8);

        if(chan[i].envelope)
        {
          switch(chan[i].env_num)
          {
            case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
            case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
            default: break;
          }
        }
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->had) 
    {
      if(i < T85APU_NUM_REAL_CHANS)
      {
        chan[i].env_num = chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->val;

        rWrite(CFG_A + i, 
          (chan[i].noise && !isMuted[NOISE_CH] ? 1<<NOISE_EN : 0) | 
          (chan[i].envelope && !isMuted[ENV_CH_START+chan[i].env_num] ? 1<<ENV_EN : 0) | (chan[i].env_num << SLOT_NUM) |
          0xF);

        if(chan[i].envelope)
        {
          switch(chan[i].env_num)
          {
            case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
            case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
            default: break;
          }
        }
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PHASE_RESET)->had) 
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_PHASE_RESET)->val)
      {
        switch(i)
        {
          case 0: rWrite(PHIAB, (chan[0].freq >> 8) | ((chan[1].freq >> 8) << 4) | 0x8); break;
          case 1: rWrite(PHIAB, (chan[0].freq >> 8) | ((chan[1].freq >> 8) << 4) | 0x80); break;

          case 2: rWrite(PHICD, (chan[2].freq >> 8) | ((chan[3].freq >> 8) << 4) | 0x8); break;
          case 3: rWrite(PHICD, (chan[2].freq >> 8) | ((chan[3].freq >> 8) << 4) | 0x80); break;

          case 4: rWrite(PHIEN, (chan[4].freq >> 8) | ((chan[NOISE_CH].freq >> 8) << 4) | 0x8); break;
          case NOISE_CH: rWrite(PHIEN, (chan[4].freq >> 8) | ((chan[NOISE_CH].freq >> 8) << 4) | 0x80); break;

          case ENV_A_CH:
          {
            rWrite(ELDLO, env_init_phase[0] & 0xff);
            rWrite(ELDHI, env_init_phase[0] >> 8);
            rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]);
            break;
          }
          case ENV_B_CH:
          {
            rWrite(ELDLO, env_init_phase[1] & 0xff);
            rWrite(ELDHI, env_init_phase[1] >> 8);
            rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]);
            break;
          }

          default: break;
        }
      }
    }

    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) 
    {
      if(chan[i].freqChanged && chan[i].enabled)
      {
        if(i <= NOISE_CH) // Tone and noise
        {
          chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,8,chan[i].pitch2,chipClock,CHIP_FREQBASE);
          CLAMP_VAR(chan[i].freq, 0, 0xFFFF);

          chan[i].octave = my_max(floor(std::log2(chan[i].freq) - 8 + 1), 0);
          chan[i].increment = round(chan[i].freq / std::pow(2, chan[i].octave));
          if (chan[i].increment > UINT8_MAX && chan[i].octave < 7)
          {
            chan[i].increment /= 2; chan[i].octave++;
          }

          CLAMP_VAR(chan[i].octave, 0, 7);
          CLAMP_VAR(chan[i].increment, 0, 0xff);

          chan[i].freq = chan[i].increment | (chan[i].octave << 8);


          rWrite(PILOA + i, chan[i].freq & 0xff);

          if(i == 0 || i == 1) 
          {
            rWrite(PHIAB, (chan[0].freq >> 8) | ((chan[1].freq >> 8) << 4));
          } 
          else if(i == 2 || i == 3) 
          {
            rWrite(PHICD, (chan[2].freq >> 8) | ((chan[3].freq >> 8) << 4));
          } 
          else if(i == NOISE_CH || i == 4) 
          {
            rWrite(PHIEN, (chan[4].freq >> 8) | ((chan[NOISE_CH].freq >> 8) << 4));
          }
        }

        if(i == ENV_A_CH || i == ENV_B_CH)
        { // envelope channels
          chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,8,chan[i].pitch2,chipClock,CHIP_FREQBASE_ENV);
          CLAMP_VAR(chan[i].freq, 0, 0xFFFFFF);
          
          chan[i].octave = my_max(floor(std::log2(chan[i].freq) - 8 + 1), 0);
          chan[i].increment = round(chan[i].freq / std::pow(2, chan[i].octave));
          if (chan[i].increment > UINT8_MAX && chan[i].octave < 15)
          {
            chan[i].increment /= 2; chan[i].octave++;
          }

          CLAMP_VAR(chan[i].octave, 0, 15);
          CLAMP_VAR(chan[i].increment, 0, 0xff);

          chan[i].freq = chan[i].increment | (chan[i].octave << 8);

          if(i == ENV_A_CH) 
          {
            rWrite(EPLOA, chan[ENV_A_CH].freq & 0xff);
          } 
          else if(i == ENV_B_CH) 
          {
            rWrite(EPLOB, chan[ENV_B_CH].freq & 0xff);
          }

          rWrite(EPIHI, ((chan[ENV_B_CH].freq >> 8) << 4) | (chan[ENV_A_CH].freq >> 8));
        }
      }

      if(chan[i].keyOn && i < T85APU_NUM_REAL_CHANS)
      {
        //chan[i].tone = true;
        if(chan[i].tone)
        {
          rWrite(DUTYA + i, chan[i].duty);
        }
        rWrite(VOL_A + i, chan[i].outVol);
      }

      if(chan[i].keyOn && (i == ENV_A_CH || i == ENV_B_CH))
      {
        // envelope channels
        chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,8,chan[i].pitch2,chipClock,CHIP_FREQBASE_ENV);
        CLAMP_VAR(chan[i].freq, 0, 0xFFFFFF);
        
        chan[i].octave = my_max(floor(std::log2(chan[i].freq) - 8 + 1), 0);
        chan[i].increment = round(chan[i].freq / std::pow(2, chan[i].octave));
        if (chan[i].increment > UINT8_MAX && chan[i].octave < 15)
        {
          chan[i].increment /= 2; chan[i].octave++;
        }

        CLAMP_VAR(chan[i].octave, 0, 15);
        CLAMP_VAR(chan[i].increment, 0, 0xff);

        chan[i].freq = chan[i].increment | (chan[i].octave << 8);

        if(i == ENV_A_CH) 
        {
          rWrite(EPLOA, chan[ENV_A_CH].freq & 0xff);
        } 
        else if(i == ENV_B_CH) 
        {
          rWrite(EPLOB, chan[ENV_B_CH].freq & 0xff);
        }

        rWrite(EPIHI, ((chan[ENV_B_CH].freq >> 8) << 4) | (chan[ENV_A_CH].freq >> 8));
      }

      if (chan[i].keyOn) chan[i].keyOn=false;
      if (chan[i].keyOff) chan[i].keyOff=false;
      chan[i].freqChanged=false;
    }
  }
}

int DivPlatformT85APU::dispatch(DivCommand c) {
  if (c.chan > T85APU_NUM_CHANS - 1) return 0;
  int envNum = 0;
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_AT85APU);
      if (c.value!=DIV_NOTE_NULL) {
        chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value);
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;
      chan[c.chan].enabled=true;
      chan[c.chan].macroInit(ins);
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].enabled=false;
      chan[c.chan].macroInit(NULL);
      chan[c.chan].freq = 0; chan[c.chan].increment = 0;

      if (c.chan < T85APU_NUM_REAL_CHANS)
      {
        rWrite(VOL_A + c.chan, 0);
      }

      if (c.chan <= NOISE_CH) 
      {
        rWrite(PILOA + c.chan, chan[c.chan].freq & 0xff);
      } 
      else if (c.chan == ENV_A_CH || c.chan == ENV_B_CH) 
      {
        rWrite(EPLOA + (c.chan - ENV_CH_START), chan[c.chan].freq & 0xff);
      }
      break;
    case DIV_CMD_NOTE_OFF_ENV:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].std.release();
      break;
    case DIV_CMD_ENV_RELEASE:
      chan[c.chan].std.release();
      break;
    case DIV_CMD_INSTRUMENT:
      if (chan[c.chan].ins!=c.value || c.value2==1) {
        chan[c.chan].insChanged=true;
        chan[c.chan].ins=c.value;
      }
      break;
    case DIV_CMD_VOLUME:
      if (chan[c.chan].vol!=c.value) {
        chan[c.chan].vol=c.value;
        if (!chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->has) {
          chan[c.chan].outVol=c.value;
          chan[c.chan].vol=chan[c.chan].outVol;

          if(c.chan < T85APU_NUM_REAL_CHANS)
          {
            rWrite(VOL_A + c.chan,chan[c.chan].vol);
          }
        }
      }
      break;
    case DIV_CMD_GET_VOLUME:
      if (chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->has) {
        return chan[c.chan].vol;
      }
      return chan[c.chan].outVol;
      break;
    case DIV_CMD_PITCH:
      chan[c.chan].pitch=c.value;
      chan[c.chan].freqChanged=true;
      break;
    case DIV_CMD_NOTE_PORTA: {
      int destFreq=NOTE_FREQUENCY(c.value2);
      bool return2=false;
      if (destFreq>chan[c.chan].baseFreq) {
        chan[c.chan].baseFreq+=c.value;
        if (chan[c.chan].baseFreq>=destFreq) {
          chan[c.chan].baseFreq=destFreq;
          return2=true;
        }
      } else {
        chan[c.chan].baseFreq-=c.value;
        if (chan[c.chan].baseFreq<=destFreq) {
          chan[c.chan].baseFreq=destFreq;
          return2=true;
        }
      }
      chan[c.chan].freqChanged=true;
      if (return2) {
        chan[c.chan].inPorta=false;
        return 2;
      }
      break;
    }
    case DIV_CMD_LEGATO:
      chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value+((HACKY_LEGATO_MESS)?(chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->val):(0)));
      chan[c.chan].freqChanged=true;
      chan[c.chan].note=c.value;
      break;
    case DIV_CMD_PRE_PORTA:
      if (chan[c.chan].active && c.value2) {
        if (parent->song.resetMacroOnPorta || parent->song.preNoteNoEffect) {
          chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_SID2));
          chan[c.chan].keyOn=true;
        }
      }
      if (!chan[c.chan].inPorta && c.value && !parent->song.brokenPortaArp && chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=NOTE_FREQUENCY(chan[c.chan].note);
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_WAVE:
    {
      if(c.chan < T85APU_NUM_REAL_CHANS)
      {
        chan[c.chan].tone = c.value&1;
        chan[c.chan].noise = c.value&2;
        chan[c.chan].envelope = c.value&4;

        rWrite(CFG_A + c.chan, 
          (chan[c.chan].noise && !isMuted[NOISE_CH] ? 1<<NOISE_EN : 0) | 
          (chan[c.chan].envelope && !isMuted[ENV_CH_START+chan[c.chan].env_num] ? 1<<ENV_EN : 0) | (chan[c.chan].env_num << SLOT_NUM) | 0xF);

        if(chan[c.chan].envelope)
        {
          switch(chan[c.chan].env_num)
          {
            case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
            case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
            default: break;
          }
        }

        if(!chan[c.chan].tone) //disable tone
        {
          rWrite(PILOA + c.chan, 0); //0 freq

          if(chan[c.chan].noise) //write proper duty
          {
            rWrite(DUTYA + c.chan, 0);
          }
          else
          {
            rWrite(DUTYA + c.chan, 0xff);
          }

          chan[c.chan].enabled = false; //so subsequent pitch changes do not break 0 freq

          switch(c.chan) //do phase reset
          {
            case 0: rWrite(PHIAB, (0 >> 8) | ((chan[1].freq >> 8) << 4) | 0x8); break;
            case 1: rWrite(PHIAB, (chan[0].freq >> 8) | ((0 >> 8) << 4) | 0x80); break;

            case 2: rWrite(PHICD, (0 >> 8) | ((chan[3].freq >> 8) << 4) | 0x8); break;
            case 3: rWrite(PHICD, (chan[2].freq >> 8) | ((0 >> 8) << 4) | 0x80); break;

            case 4: rWrite(PHIEN, (0 >> 8) | ((chan[NOISE_CH].freq >> 8) << 4) | 0x8); break;
            default: break;
          }
        }

        if(chan[c.chan].tone)
        {
          chan[c.chan].enabled = true;
          chan[c.chan].freqChanged = true;
          rWrite(DUTYA + c.chan, chan[c.chan].duty); //restore duty!
        }
      }
      break;
    }
    case DIV_CMD_C64_FINE_DUTY:
      if(c.chan < T85APU_NUM_REAL_CHANS)
      {
        chan[c.chan].duty=c.value & 255;
        rWrite(DUTYA + c.chan, chan[c.chan].duty);
      }
      break;
    case DIV_CMD_AY_ENVELOPE_SET:
      if(c.chan == ENV_A_CH || c.chan == ENV_B_CH)
      {
        env_shape[c.chan-ENV_CH_START] = c.value & 7;

        rWrite(E_SHP, (env_shape[1] << 4) | env_shape[0]);
      }
      break;
    case DIV_CMD_AY_ENVELOPE_LOW:
    {
      if(c.chan < T85APU_NUM_REAL_CHANS)
      {
        envNum = chan[c.chan].env_num;
      } 
      else if (c.chan == ENV_A_CH || c.chan == ENV_B_CH) 
      {
        envNum = c.chan - ENV_CH_START;
      }
      if (c.chan == NOISE_CH)
      {
        break;
      }
      env_init_phase[envNum] &= 0xff00;
      env_init_phase[envNum] |= c.value & 0xff;

      rWrite(ELDLO, env_init_phase[envNum] & 0xff);
      rWrite(ELDHI, env_init_phase[envNum] >> 8);

      if(chan[c.chan].envelope)
      {
        switch(envNum)
        {
          case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
          case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
          default: break;
        }
      }
      break;
    }
    case DIV_CMD_AY_ENVELOPE_HIGH:
    {
      if(c.chan < T85APU_NUM_REAL_CHANS)
      {
        envNum = chan[c.chan].env_num;
      } 
      else if (c.chan == ENV_A_CH || c.chan == ENV_B_CH) 
      {
        envNum = c.chan - ENV_CH_START;
      }
      if (c.chan == NOISE_CH)
      {
        break;
      }

      env_init_phase[envNum] &= 0x00ff;
      env_init_phase[envNum] |= (c.value & 0xff) << 8;

      rWrite(ELDLO, env_init_phase[envNum] & 0xff);
      rWrite(ELDHI, env_init_phase[envNum] >> 8);

      if(chan[c.chan].envelope)
      {
        switch(envNum)
        {
          case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
          case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
          default: break;
        }
      }
      break;
    }
    case DIV_CMD_POWERNOISE_COUNTER_LOAD:
      if(c.chan == NOISE_CH)
      {
        switch(c.value)
        {
          case 0: noise_lsfr_feedback_bits &= 0xff00; noise_lsfr_feedback_bits |= c.value2 & 0xff; break;
          case 1: noise_lsfr_feedback_bits &= 0x00ff; noise_lsfr_feedback_bits |= (c.value2 & 0xff) << 8; break;
          default: break;
        }

        rWrite(NTPLO, noise_lsfr_feedback_bits & 0xff);
        rWrite(NTPHI, noise_lsfr_feedback_bits >> 8);
      }
      break;
    case DIV_CMD_AY_AUTO_ENVELOPE:
      if(c.chan < T85APU_NUM_REAL_CHANS)
      {
        chan[c.chan].env_num = c.value & 1;

        rWrite(CFG_A + c.chan, 
          (chan[c.chan].noise && !isMuted[NOISE_CH] ? 1<<NOISE_EN : 0) | 
          (chan[c.chan].envelope && !isMuted[ENV_CH_START+chan[c.chan].env_num] ? 1<<ENV_EN : 0) | (chan[c.chan].env_num << SLOT_NUM) |
          0xF);

        if(chan[c.chan].envelope)
        {
          switch(chan[c.chan].env_num)
          {
            case 0: rWrite(E_SHP, (env_shape[1] << 4) | 0x8 | env_shape[0]); break;
            case 1: rWrite(E_SHP, 0x80 | (env_shape[1] << 4) | env_shape[0]); break;
            default: break;
          }
        }
      }
      break;
    case DIV_CMD_GET_VOLMAX:
      return 255;
      break;
    case DIV_CMD_MACRO_OFF:
      chan[c.chan].std.mask(c.value,true);
      break;
    case DIV_CMD_MACRO_ON:
      chan[c.chan].std.mask(c.value,false);
      break;
    case DIV_CMD_MACRO_RESTART:
      chan[c.chan].std.restart(c.value);
      break;
    default:
      break;
  }
  return 1;
}

void DivPlatformT85APU::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
  if (parent->isExporting()) {
    isMuted[ENV_A_CH] = 0;
    isMuted[ENV_B_CH] = 0;
    isMuted[NOISE_CH] = 0;
  }
  t85APU_setMute(t85_synth, ch, mute);
}

void DivPlatformT85APU::forceIns() {
  for (int i=0; i<T85APU_NUM_CHANS; i++) {
    chan[i].insChanged=true;
    if (chan[i].active) {
      chan[i].keyOn=true;
      chan[i].freqChanged=true;
    }
  }
}

void DivPlatformT85APU::notifyInsChange(int ins) {
  for (int i=0; i<T85APU_NUM_CHANS; i++) {
    if (chan[i].ins==ins) {
      chan[i].insChanged=true;
    }
  }
}

void DivPlatformT85APU::notifyInsDeletion(void* ins) {
  for (int i=0; i<T85APU_NUM_CHANS; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void* DivPlatformT85APU::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformT85APU::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivChannelModeHints DivPlatformT85APU::getModeHints(int ch) {
  DivChannelModeHints ret;
  return ret;
}

DivDispatchOscBuffer* DivPlatformT85APU::getOscBuffer(int ch) {
  return oscBuf[ch];
}

bool DivPlatformT85APU::getWantPreNote() {
  return true;
}

unsigned char* DivPlatformT85APU::getRegisterPool() {
  return regPool;
}

int DivPlatformT85APU::getRegisterPoolSize() {
  return 0x20;
}

float DivPlatformT85APU::getPostAmp() {
  return 1.0f;
}

void DivPlatformT85APU::reset() {
  while (!writes.empty()) writes.pop();
  for (int i=0; i<T85APU_NUM_CHANS; i++) 
  {
    chan[i]=DivPlatformT85APU::Channel();
    chan[i].std.setEngine(parent);

    chan[i].vol = 0xff;
    chan[i].noise = false;
    chan[i].envelope = false;
    chan[i].tone = true;
    chan[i].duty = 0x80;
    chan[i].env_num = 0;

    chan[i].enabled = false;
  }

  env_shape[0] = 0;
  env_shape[1] = 0;

  env_init_phase[0] = 0;
  env_init_phase[1] = 0;

  noise_lsfr_feedback_bits = 0x2400;

  memset(regPool,0,0x20);
  memset(regPool+0x15,0x0F,T85APU_NUM_REAL_CHANS);  // Initial channel config settings
  regPool[0x0F] = 0x24; // Initial noise XOR setting

  t85APU_reset(t85_synth);
}

int DivPlatformT85APU::getOutputCount() {
  return 2;
}

void DivPlatformT85APU::setFlags(const DivConfig& flags) {
  audio_type=flags.getInt("audioRenderType",T85_OUTPUT_IDEAL_PB4);
  t85APU_setOutputType(t85_synth, audio_type);
  switch (flags.getInt("clockSel",1)) {
    case 2:
      chipClock=16000000;
      break;
    case 1:
      chipClock=8000000;
      break;
    default:
      chipClock=1000000;
      break;
  }
  CHECK_CUSTOM_CLOCK;
  if(audio_type == T85_OUTPUT_IDEAL_PB4)
  {
    rate=chipClock / 512;
  }
  if(audio_type == T85_OUTPUT_EARRAPE_FUCKING_31kHz_PWM)
  {
    rate=chipClock;
  }
  
  for (int i=0; i<T85APU_NUM_CHANS; i++) 
  {
    oscBuf[i]->rate=rate;
  }
}

int DivPlatformT85APU::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;
  
  for (int i=0; i<T85APU_NUM_CHANS; i++) 
  {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }

  t85_synth = t85APU_new(chipClock, rate, audio_type);

  setFlags(flags);

  reset();

  return T85APU_NUM_CHANS;
}

void DivPlatformT85APU::quit() {
  for (int i=0; i<T85APU_NUM_CHANS; i++) 
  {
    delete oscBuf[i];
  }

  t85APU_delete(t85_synth);
}

DivPlatformT85APU::~DivPlatformT85APU() 
{
}
