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

#define CHIP_FREQBASE 8000000

#define T85_OUTPUT_IDEAL 0
#define T85_OUTPUT_EARRAPE_FUCKING_15kHZ_PWM 1

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }

void DivPlatformT85APU::acquire(short** buf, size_t len) 
{
  for (size_t h=0; h<len; h++) 
  {
    if (!writes.empty()) 
    {
      QueuedWrite w=writes.front();
      t85APU_writeReg(t85_synth, w.addr, w.val);
      regPool[w.addr&0x1f]=w.val;
      writes.pop();
    }

    for(int i = 0; i < chipClock / rate; i++)
    {
      t85APU_tick(t85_synth);
    }

    for (int j=0; j<T85APU_NUM_CHANS - 3; j++) //without noise and env channels...
    {
      oscBuf[j]->data[oscBuf[j]->needle++]=(t85_synth->channelOutput[j])<<5;
    }

    buf[0][h]=t85_synth->currentOutput << 8;
    buf[1][h]=t85_synth->currentOutput << 8;
  }
}

void DivPlatformT85APU::tick(bool sysTick) 
{
  for (int i=0; i<T85APU_NUM_CHANS; i++) 
  {
    chan[i].std.next();

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->had) \
    {
      if(i < 5)
      {
        chan[i].outVol=VOL_SCALE_LINEAR(chan[i].vol&255,MIN(255,chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->val),255);
        rWrite(0x10 + i, chan[i].outVol);
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
      if(i < 5)
      {
        chan[i].duty=chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val & 255;
        rWrite(0x9 + i, chan[i].duty);
      }
    }

    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) 
    {
      if(chan[i].freqChanged)
      {
        if(i < 5 || i == 7)
        {
          chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,8,chan[i].pitch2,chipClock,CHIP_FREQBASE);
          if (chan[i].freq<0) chan[i].freq=0;
          if (chan[i].freq>0xfffff) chan[i].freq=0xfffff;

          chan[i].freq = (int)((double)chan[i].freq * std::pow(2, 1.0 / 12.0)); //why the fuck it's one semitone lower?
          chan[i].freq /= 16;

          chan[i].octave = (int)std::fmax(floor(std::log2(chan[i].freq) - 8 + 1), 0);
          chan[i].increment = round(chan[i].freq / std::pow(2, chan[i].octave));
          if (chan[i].increment > UINT8_MAX)
          {
            chan[i].increment /= 2; chan[i].octave++;
          }

          if(chan[i].octave > 7) chan[i].octave = 7;
          if(chan[i].increment > 0xff) chan[i].increment = 0xff;

          chan[i].freq = chan[i].increment | (chan[i].octave << 8);

          if(i < 5)
          {
            rWrite(i, chan[i].freq & 0xff);
          }
          if(i == 7)
          {
            rWrite(5, chan[i].freq & 0xff);
          }

          if(i == 0 || i == 1)
          {
            rWrite(0x6, (chan[0].freq >> 8) | ((chan[1].freq >> 8) << 4));
          }
          if(i == 2 || i == 3)
          {
            rWrite(0x7, (chan[2].freq >> 8) | ((chan[3].freq >> 8) << 4));
          }
          if(i == 7 || i == 4)
          {
            rWrite(0x8, (chan[4].freq >> 8) | ((chan[7].freq >> 8) << 4));
          }
        }

        if(i == 5 || i == 6)
        {
          chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,8,chan[i].pitch2,chipClock,CHIP_FREQBASE);
          if (chan[i].freq<0) chan[i].freq=0;
          if (chan[i].freq>0xfffff) chan[i].freq=0xfffff;

          chan[i].freq = (int)((double)chan[i].freq * std::pow(2, 1.0 / 12.0)); //why the fuck it's one semitone lower?
          
          chan[i].octave = (int)std::fmax(floor(std::log2(chan[i].freq) - 16 + 1), 0);
          chan[i].increment = round(chan[i].freq / std::pow(2, chan[i].octave));
          if (chan[i].increment > UINT8_MAX)
          {
            chan[i].increment /= 2; chan[i].octave++;
          }

          if(chan[i].octave > 15) chan[i].octave = 15;
          if(chan[i].increment > 0xff) chan[i].increment = 0xff;

          chan[i].freq = chan[i].increment | (chan[i].octave << 8);

          if(i == 5)
          {
            rWrite(0x1d, chan[5].freq & 0xff);
          }
          if(i == 6)
          {
            rWrite(0x1f, chan[6].freq & 0xff);
          }

          rWrite(0x1e, ((chan[6].freq >> 8) << 4) | (chan[5].freq >> 8));
        }
      }

      if(chan[i].keyOn && i < 5)
      {
        rWrite(0x09 + i, chan[i].duty);
        rWrite(0x10 + i, chan[i].outVol);
      }

      if (chan[i].keyOn) chan[i].keyOn=false;
      if (chan[i].keyOff) chan[i].keyOff=false;
      chan[i].freqChanged=false;
    }
  }
}

int DivPlatformT85APU::dispatch(DivCommand c) {
  if (c.chan > T85APU_NUM_CHANS - 1) return 0;
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
      chan[c.chan].macroInit(ins);

      //rWrite(0, 0xff);
      //rWrite(0x06, 0x1);
      //rWrite(0x15, 0xf);
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].macroInit(NULL);

      if(c.chan < 5)
      {
        rWrite(0x10 + c.chan, 0);
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
      chan[c.chan].vol=c.value;
      if (!chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->has) {
        chan[c.chan].outVol=c.value;
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
    chan[i].duty = 0x80;
  }

  memset(regPool,0,0x20);

  t85APU_reset(t85_synth);
}

int DivPlatformT85APU::getOutputCount() {
  return 2;
}

void DivPlatformT85APU::setFlags(const DivConfig& flags) {
  chipClock = CHIP_FREQBASE;
  CHECK_CUSTOM_CLOCK;
  rate=chipClock / 512;
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

  t85_synth = t85APU_new(chipClock, rate, T85_OUTPUT_IDEAL);

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