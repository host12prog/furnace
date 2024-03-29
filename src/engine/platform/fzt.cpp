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

#include "fzt.h"
#include "../engine.h"
#include "IconsFontAwesome4.h"
#include <math.h>
#include "../../ta-log.h"

#define my_min(a, b) (((a) < (b)) ? (a) : (b))
#define my_max(a, b) (((a) > (b)) ? (a) : (b))

#define CHIP_FREQBASE 4410000

void DivPlatformFZT::acquire(short** buf, size_t len) 
{
  sound_engine_fill_buffer(sound_engine, buf, len);

  for(int i = 0; i < FZT_NUM_CHANNELS; i++)
  {
    for(int j = 0; j < (int)len; j++)
    {
      oscBuf[i]->data[oscBuf[i]->needle++]=sound_engine->osc_buf[i][j];
    }
  }
}

void DivPlatformFZT::tracker_engine_set_note(int chan, int note, bool update_note) 
{
  if(update_note) fztChan[chan].note = note;

  sound_engine_set_channel_frequency(sound_engine, &sound_engine->channel[chan], note);
}

void DivPlatformFZT::tracker_engine_trigger_instrument_internal(int chan, DivInstrument* pinst, int note)
{
  SoundEngineChannel* se_channel = &sound_engine->channel[chan];
  TrackerEngineChannel* te_channel = &fztChan[chan];

  te_channel->channel_flags = TEC_PLAYING | (te_channel->channel_flags & TEC_DISABLED);

  te_channel->program_period = pinst->fzt.program_period;

  if(!(pinst->fzt.flags & TE_PROG_NO_RESTART) && pinst->fzt.program_period > 0) {
      te_channel->channel_flags |= TEC_PROGRAM_RUNNING;

      te_channel->program_counter = 0;
      te_channel->program_loop = 1;
      te_channel->program_tick = 0;
  }

  se_channel->waveform = pinst->fzt.waveform;
  se_channel->flags = pinst->fzt.sound_engine_flags;

  te_channel->flags = pinst->fzt.flags;

  te_channel->arpeggio_note = 0;
  te_channel->fixed_note = 0xffff;

  note += (uint16_t)(((int16_t)pinst->fzt.base_note - MIDDLE_C) << 8);
  tracker_engine_set_note(chan, note + (int16_t)pinst->fzt.finetune, true);

  te_channel->last_note = te_channel->target_note = note + (int16_t)pinst->fzt.finetune;

  te_channel->extarp1 = te_channel->extarp2 = 0;

  if(pinst->fzt.flags & TE_ENABLE_VIBRATO) {
      te_channel->vibrato_speed = pinst->fzt.vibrato_speed;
      te_channel->vibrato_depth = pinst->fzt.vibrato_depth;
      te_channel->vibrato_delay = pinst->fzt.vibrato_delay;
  }

  if(pinst->fzt.flags & TE_ENABLE_PWM) {
      te_channel->pwm_speed = pinst->fzt.pwm_speed;
      te_channel->pwm_depth = pinst->fzt.pwm_depth;
      te_channel->pwm_delay = pinst->fzt.pwm_delay;
  }

  if(pinst->fzt.sound_engine_flags & SE_ENABLE_KEYDOWN_SYNC) {
      te_channel->vibrato_position = ((ACC_LENGTH / 2 / 2) << 9);
      te_channel->pwm_position = ((ACC_LENGTH / 2 / 2) << 9);

      se_channel->accumulator = 0;
      se_channel->lfsr = RANDOM_SEED;
  }

  if(pinst->fzt.flags & TE_SET_CUTOFF) {
      te_channel->filter_cutoff = ((uint16_t)pinst->fzt.filter_cutoff << 3);
      te_channel->filter_resonance = (uint16_t)pinst->fzt.filter_resonance;

      se_channel->filter.low = 0;
      se_channel->filter.high = 0;
      se_channel->filter.band = 0;

      sound_engine_filter_set_coeff(
          &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);
  }

  if(pinst->fzt.sound_engine_flags & SE_ENABLE_FILTER) {
      te_channel->filter_type = pinst->fzt.filter_type;
      se_channel->filter_mode = te_channel->filter_type;
  }

  if(pinst->fzt.flags & TE_SET_PW) {
      te_channel->pw = (pinst->fzt.pw << 4);
      se_channel->pw = (pinst->fzt.pw << 4);
  }

  se_channel->ring_mod = pinst->fzt.ring_mod;
  se_channel->hard_sync = pinst->fzt.hard_sync;

  te_channel->slide_speed = pinst->fzt.slide_speed;

  se_channel->adsr.a = pinst->fzt.adsr.a;
  se_channel->adsr.d = pinst->fzt.adsr.d;
  se_channel->adsr.s = pinst->fzt.adsr.s;
  se_channel->adsr.r = pinst->fzt.adsr.r;
  se_channel->adsr.volume = pinst->fzt.adsr.volume;

  te_channel->volume = pinst->fzt.adsr.volume;

  sound_engine_enable_gate(sound_engine, &sound_engine->channel[chan], true);
}

void DivPlatformFZT::do_command(int opcode, int channel, int tick, bool from_program) 
{

}

void DivPlatformFZT::tracker_engine_execute_volume(int vol, int chan)
{
  if(!(fztChan[chan].channel_flags & TEC_DISABLED)) 
  {
    sound_engine->channel[chan].adsr.volume = (int32_t)fztChan[chan].volume * (int32_t)vol / (MUS_NOTE_VOLUME_NONE);
  }
}

void DivPlatformFZT::tracker_engine_execute_track_command(int chan, bool first_tick, int opcode)
{
  if(opcode != 0)
  {
    if((opcode & 0xff00) == 0x00) 
    {
      fztChan[chan].extarp1 = ((opcode & 0xf0) >> 4);
      fztChan[chan].extarp2 = (opcode & 0xf);
    }
    else 
    {
      do_command(opcode, chan, current_tick, false);
    }
  }

  if(fztChan[chan].channel_flags & TEC_DISABLED)
  {
    sound_engine->channel[chan].adsr.volume = 0;
  }
}

void DivPlatformFZT::tracker_engine_execute_program_tick(int chann, int advance) {
    TrackerEngineChannel* te_channel = &fztChan[chann];
    uint8_t tick = te_channel->program_tick;
    uint8_t visited[FZT_INST_PROG_LEN] = {0};

do_it_again:;
    
    DivInstrument* ins=parent->getIns(chan[chann].ins,DIV_INS_FZT);
    const uint16_t inst = (ins->fzt.program[tick].cmd << 8) | (ins->fzt.program[tick].val) | (ins->fzt.program[tick].unite << 15);

    if((inst & 0x7fff) == 0x7fff) 
    {
      te_channel->channel_flags &= ~(TEC_PROGRAM_RUNNING);
      return;
    }

    uint8_t dont_reloop = 0;

    if((inst & 0x7fff) != 0x7ffe) 
    {
        switch(inst & 0x7f00) 
        {
        case 0x7f00: 
        {
            if(!visited[tick]) {
                visited[tick] = 1;
                tick = inst & (FZT_INST_PROG_LEN - 1);
            }

            else
                return;

            break;
        }

        case 0x7d00:
            break;

        case 0x7e00: 
        {
            if(te_channel->program_loop == (inst & 0xff)) 
            {
              if(advance) te_channel->program_loop = 1;
            }

            else 
            {
              if(advance) ++te_channel->program_loop;

              uint8_t l = 0;

              while((((ins->fzt.program[tick].cmd << 8) | (ins->fzt.program[tick].val) | (ins->fzt.program[tick].unite << 15)) & 0x7f00) != 0x7d00 && tick > 0) 
              {
                --tick;
                if(!(((ins->fzt.program[tick].cmd << 8) | (ins->fzt.program[tick].val) | (ins->fzt.program[tick].unite << 15)) & 0x8000)) ++l;
              }

              --tick;

              dont_reloop = l <= 1;
            }

            break;
        }

        default: {
            do_command(inst, chann, te_channel->program_counter, true);
            break;
        }
        }
    }

    if((inst & 0x7fff) == 0x7ffe || (inst & 0x7f00) != 0x7f00) {
        ++tick;
        if(tick >= FZT_INST_PROG_LEN) {
            tick = 0;
        }
    }

    // skip to next on msb

    if(((inst & 0x8000) || ((inst & 0x7f00) == 0x7d00) ||
        ((inst & 0x7f00) == 0x7f00)) &&
       (inst & 0x7fff) != 0x7ffe && !dont_reloop) {
        goto do_it_again;
    }

    if(advance) {
        te_channel->program_tick = tick;
    }
}

void DivPlatformFZT::tracker_engine_advance_channel(int chan) 
{
  SoundEngineChannel* se_channel = &sound_engine->channel[chan];
  TrackerEngineChannel* te_channel = &fztChan[chan];

  if(te_channel->channel_flags & TEC_PLAYING) 
  {
    if(!(se_channel->flags & SE_ENABLE_GATE)) 
    {
      te_channel->flags &= ~(TEC_PLAYING);
    }

    if(te_channel->slide_speed != 0) 
    {
        if(te_channel->target_note > te_channel->note) 
        {
            te_channel->note += my_min(
                te_channel->slide_speed * 4, te_channel->target_note - te_channel->note);
        }

        else if(te_channel->target_note < te_channel->note) 
        {
            te_channel->note -= my_min(
                te_channel->slide_speed * 4, te_channel->note - te_channel->target_note);
        }
    }

    if(te_channel->channel_flags & TEC_PROGRAM_RUNNING) 
    {
      uint8_t u = (te_channel->program_counter + 1) >= te_channel->program_period;
      tracker_engine_execute_program_tick(chan, u);
      ++te_channel->program_counter;

      if(u) te_channel->program_counter = 0;
    }

    int16_t vib = 0;
    int32_t pwm = 0;

    if(te_channel->flags & TE_ENABLE_VIBRATO) {
        if(te_channel->vibrato_delay > 0) {
            te_channel->vibrato_delay--;
        }

        else {
            te_channel->vibrato_position += ((uint32_t)te_channel->vibrato_speed << 21);
            vib = (int32_t)(sound_engine_triangle(te_channel->vibrato_position >> 9) -
                            WAVE_AMP / 2) *
                  (int32_t)te_channel->vibrato_depth / (256 * 128);
        }
    }

    if(te_channel->flags & TE_ENABLE_PWM) {
        if(te_channel->pwm_delay > 0) {
            te_channel->pwm_delay--;
        }

        else {
            te_channel->pwm_position +=
                ((uint32_t)te_channel->pwm_speed
                  << 20); // so minimum PWM speed is even lower than minimum vibrato speed
            pwm = ((int32_t)sound_engine_triangle((te_channel->pwm_position) >> 9) -
                    WAVE_AMP / 2) *
                  (int32_t)te_channel->pwm_depth / (256 * 16);
        }

        int16_t final_pwm = (int16_t)fztChan[chan].pw + pwm;

        if(final_pwm < 0) {
            final_pwm = 0;
        }

        if(final_pwm > 0xfff) {
            final_pwm = 0xfff;
        }

        sound_engine->channel[chan].pw = final_pwm;
    }

    else {
        sound_engine->channel[chan].pw = fztChan[chan].pw;
    }

    int32_t chn_note = (int16_t)(te_channel->fixed_note != 0xffff ? te_channel->fixed_note : te_channel->note) + vib + ((int16_t)te_channel->arpeggio_note << 8);

    if(chn_note < 0) {
        chn_note = 0;
    }

    if(chn_note > ((12 * 7 + 11) << 8)) {
        chn_note = ((12 * 7 + 11) << 8); // highest note is B-7
    }

    tracker_engine_set_note(chan, (uint16_t)chn_note, false);
  }

  if(fztChan[chan].channel_flags & TEC_DISABLED) // so we can't set some non-zero volme from inst program too
  {
    sound_engine->channel[chan].adsr.volume = 0;
  }
}

void DivPlatformFZT::tracker_engine_advance_tick(int chann, int opcode)
{
  SoundEngineChannel* se_channel = &sound_engine->channel[chann];
  TrackerEngineChannel* te_channel = &fztChan[chann];
  DivInstrument* pinst = parent->getIns(chan[chann].ins,DIV_INS_FZT);

  uint8_t note_delay = 0;

  if((opcode & 0xfff0) == 0xED00) {
    note_delay = (opcode & 0xf);
  }

  if(current_tick == note_delay)
  {
    int note = chan[chann].note;
    //uint8_t inst = tracker_engine_get_instrument(&pattern->step[pattern_step]);

    if(note != 100 && note != 101 && note != -1)
    {
      //uint8_t prev_adsr_volume = se_channel->adsr.volume;

      if((opcode & 0xff00) == 0x0300)
      {
        if(pinst->fzt.flags & TE_RETRIGGER_ON_SLIDE) 
        {
          uint16_t temp_note = te_channel->note;
          tracker_engine_trigger_instrument_internal(chann, pinst, note << 8);
          te_channel->note = temp_note;
        }

        te_channel->target_note = ((note + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;
        te_channel->slide_speed = (opcode & 0xff);
      }

      else if((opcode & 0xff00) == 0xea00) 
      {
        te_channel->note = te_channel->target_note = te_channel->last_note = ((note + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;
      }

      /*else {
          tracker_engine_trigger_instrument_internal(chann, pinst, note << 8);
          te_channel->note =
              ((note + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;

          te_channel->target_note =
              ((note + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;
      }*/
    }
  }

  tracker_engine_execute_track_command(chann, current_tick == note_delay, opcode);

  //tracker_engine_advance_channel(chann);
}

void DivPlatformFZT::tick(bool sysTick) {
  for (int i=0; i<FZT_NUM_CHANNELS; i++) {
    chan[i].std.next();
    tracker_engine_advance_channel(i);
  }
}

int DivPlatformFZT::dispatch(DivCommand c) {
  if (c.chan>FZT_NUM_CHANNELS - 1) return 0;
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_FZT);
      if (c.value!=DIV_NOTE_NULL) {
        chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value);
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;
      chan[c.chan].macroInit(ins);

      tracker_engine_trigger_instrument_internal(c.chan, ins, c.value << 8);
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].macroInit(NULL);

      sound_engine_enable_gate(sound_engine, &sound_engine->channel[c.chan], 0);
      sound_engine->channel[c.chan].adsr.volume = 0;
      fztChan[c.chan].volume = 0;
      break;
    case DIV_CMD_NOTE_OFF_ENV:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].std.release();

      sound_engine_enable_gate(sound_engine, &sound_engine->channel[c.chan], 0);
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
    case DIV_CMD_VOLUME_FZT:
      logV("vol fzt");
      break;
    case DIV_CMD_EFFECT_FZT:
      logV("eff fzt");
      current_tick = c.value >> 8;
      tracker_engine_advance_tick(c.chan, ((c.value & 0xff) << 8) | c.value2);
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

void DivPlatformFZT::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
}

void DivPlatformFZT::forceIns() {
  for (int i=0; i<3; i++) {
    chan[i].insChanged=true;
    if (chan[i].active) {
      chan[i].keyOn=true;
      chan[i].freqChanged=true;
    }
  }
}

void DivPlatformFZT::notifyInsChange(int ins) {
  for (int i=0; i<FZT_NUM_CHANNELS; i++) {
    if (chan[i].ins==ins) {
      chan[i].insChanged=true;
    }
  }
}

void DivPlatformFZT::notifyInsDeletion(void* ins) {
  for (int i=0; i<3; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void* DivPlatformFZT::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformFZT::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivChannelModeHints DivPlatformFZT::getModeHints(int ch) {
  DivChannelModeHints ret;
  return ret;
}

DivDispatchOscBuffer* DivPlatformFZT::getOscBuffer(int ch) {
  return oscBuf[ch];
}

bool DivPlatformFZT::getWantPreNote() {
  return true;
}

float DivPlatformFZT::getPostAmp() {
  return 1.0f;
}

void DivPlatformFZT::reset() {
  while (!writes.empty()) writes.pop();
  for (int i=0; i<FZT_NUM_CHANNELS; i++) {
    chan[i]=DivPlatformFZT::Channel();
    chan[i].std.setEngine(parent);
    memset((void*)&fztChan[i], 0, sizeof(TrackerEngineChannel));
  }

  sound_engine_init(sound_engine, rate);
}

void DivPlatformFZT::setFlags(const DivConfig& flags) {
  chipClock = CHIP_FREQBASE;
  /*switch (flags.getInt("clockSel",0)) {
    case 0x0: // NTSC C64
      chipClock=COLOR_NTSC*2.0/7.0;
      break;
    case 0x1: // PAL C64
      chipClock=COLOR_PAL*2.0/9.0;
      break;
    case 0x2: // SSI 2001
    default:
      chipClock=14318180.0/16.0;
      break;
  }*/
  CHECK_CUSTOM_CLOCK;
  rate=chipClock / 100; //TODO: custom rate
  for (int i=0; i<FZT_NUM_CHANNELS; i++) {
    oscBuf[i]->rate=rate;
  }
}

int DivPlatformFZT::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;
  
  for (int i=0; i<FZT_NUM_CHANNELS; i++) 
  {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }

  sound_engine = (SoundEngine*)malloc(sizeof(SoundEngine));

  setFlags(flags);

  reset();

  return FZT_NUM_CHANNELS;
}

void DivPlatformFZT::quit() {
  for (int i=0; i<FZT_NUM_CHANNELS; i++) 
  {
    delete oscBuf[i];
  }
  if (sound_engine!=NULL) free(sound_engine);
}

DivPlatformFZT::~DivPlatformFZT() {
}