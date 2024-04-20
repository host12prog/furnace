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

#define CHIP_FREQBASE 441000

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

  te_channel->pitch_note = 0;

  note += (((int16_t)pinst->fzt.base_note - MIDDLE_C) << 8);
  tracker_engine_set_note(chan, note + (int16_t)pinst->fzt.finetune, true);

  if (note + (int)pinst->fzt.finetune > 0 && note + (int)pinst->fzt.finetune <= MAX_NOTE << 8)
  {
      te_channel->last_note = te_channel->target_note = note + (int16_t)pinst->fzt.finetune;
  }

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
  TrackerEngineChannel* te_channel = &fztChan[channel];
  SoundEngineChannel* se_channel = &sound_engine->channel[channel];

  switch(opcode & 0xff00) 
  {
    case 0x0000: {
        if(tick == 0) {
            if(te_channel->fixed_note != 0xffff) {
                te_channel->note = te_channel->last_note;
                te_channel->fixed_note = 0xffff;
            }

            if((opcode & 0xff) == 0xf0)
                te_channel->arpeggio_note = te_channel->extarp1;
            else if((opcode & 0xff) == 0xf1)
                te_channel->arpeggio_note = te_channel->extarp2;
            else
                te_channel->arpeggio_note = (opcode & 0xff);
        }
        break;
    }

    case 0x0100: {
        te_channel->note += ((opcode & 0xff) << 2);
        if(te_channel->note > (MAX_NOTE << 8)) te_channel->note = (MAX_NOTE << 8);

        te_channel->target_note = te_channel->note;
        break;
    }

    case 0x0200: {
        int32_t prev = te_channel->note;

        te_channel->note -= ((opcode & 0xff) << 2);
        if(prev < te_channel->note) te_channel->note = 0;

        te_channel->target_note = te_channel->note;
        break;
    }

    case 0x0400: {
        if(tick == 0) {
            if(opcode & 0xff) {
                te_channel->flags |= TE_ENABLE_VIBRATO;

                te_channel->vibrato_speed = (opcode & 0xf0);
                te_channel->vibrato_depth = ((opcode & 0x0f) << 4);
            }

            else {
                te_channel->flags &= ~(TE_ENABLE_VIBRATO);
            }
        }

        break;
    }

    case 0x1100: {
        if(tick == 0) {
            if(opcode & 0xff) {
                te_channel->flags |= TE_ENABLE_PWM;

                te_channel->pwm_speed = (opcode & 0xf0);
                te_channel->pwm_depth = ((opcode & 0x0f) << 4);
            }

            else {
                te_channel->flags &= ~(TE_ENABLE_PWM);
            }
        }

        break;
    }

    case 0x1200: {
        if(tick == 0) {
            te_channel->pw = ((opcode & 0xff) << 4);
        }

        break;
    }

    case 0x1300: {
        int16_t temp_pw = te_channel->pw + (int16_t)(opcode & 0xff);

        if(temp_pw < 0) temp_pw = 0;
        if(temp_pw > 0xfff) temp_pw = 0xfff;

        te_channel->pw = temp_pw;

        break;
    }

    case 0x1400: {
        int16_t temp_pw = te_channel->pw - (int16_t)(opcode & 0xff);

        if(temp_pw < 0) temp_pw = 0;
        if(temp_pw > 0xfff) temp_pw = 0xfff;

        te_channel->pw = temp_pw;

        break;
    }

    case 0x1500: {
        if(tick == 0) {
            te_channel->filter_cutoff = ((opcode & 0xff) << 3);
            sound_engine_filter_set_coeff(
                &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);
        }

        break;
    }

    case 0x0a00: {
        if(!(te_channel->channel_flags & TEC_DISABLED) && !(isMuted[channel])) {
            te_channel->volume -= (opcode & 0xf);
            if(te_channel->volume > MAX_ADSR_VOLUME) te_channel->volume = 0;
            te_channel->volume += ((opcode >> 4) & 0xf);
            if(te_channel->volume > MAX_ADSR_VOLUME) te_channel->volume = MAX_ADSR_VOLUME;

            se_channel->adsr.volume = (int32_t)te_channel->volume;
        }

        break;
    }

    case 0x1000: {
        if(tick == 0) {
            se_channel->waveform = (opcode & 0x3f);
        }

        break;
    }

    case 0x1600: {
        if(tick == 0) {
            if(!(te_channel->channel_flags & TEC_DISABLED)) {
                te_channel->volume = opcode & 0xff;

                se_channel->adsr.volume = (int32_t)te_channel->volume;
                se_channel->adsr.volume = (int32_t)se_channel->adsr.volume;
            }
        }

        break;
    }

    case 0x1700: {
        if(tick == 0) {
            if(opcode & 0xf) {
                se_channel->flags |= SE_ENABLE_FILTER;
            }

            else {
                se_channel->flags &= ~SE_ENABLE_FILTER;
            }
        }

        break;
    }

    case 0xf100: {
        if(tick == 0) {
            int32_t prev = te_channel->note;

            te_channel->note -= (opcode & 0xf);
            if(prev < te_channel->note) te_channel->note = 0;

            te_channel->target_note = te_channel->note;
        }

        break;
    }

    case 0xf200: {
        if(tick == 0) {
            te_channel->note += (opcode & 0xf);
            if(te_channel->note > (MAX_NOTE << 8)) te_channel->note = (MAX_NOTE << 8);

            te_channel->target_note = te_channel->note;
        }

        break;
    }

    case 0x1800: {
        if(tick == 0) {
            se_channel->filter_mode = (opcode & 0xf);
        }

        break;
    }

    case 0x0c00: {
        if((opcode & 0xf) > 0 && (tick % (opcode & 0xf)) == 0) {
            uint8_t prev_vol_tr = te_channel->volume;
            uint8_t prev_vol_cyd = se_channel->adsr.volume;
            DivInstrument* ins=parent->getIns(chan[channel].ins,DIV_INS_FZT);
            tracker_engine_trigger_instrument_internal(
                channel, ins, te_channel->last_note);
            te_channel->volume = prev_vol_tr;
            se_channel->adsr.volume = prev_vol_cyd;
        }

        break;
    }

    case 0xf900: {
        if(tick == 0) {
            te_channel->volume -= (opcode & 0xf);

            if(te_channel->volume > MAX_ADSR_VOLUME) te_channel->volume = 0;

            se_channel->adsr.volume = (int32_t)te_channel->volume;
            se_channel->adsr.volume = (int32_t)se_channel->adsr.volume;
        }

        break;
    }

    case 0xf800: {
        if(tick == 0) {
            te_channel->volume += (opcode & 0xf);

            if(te_channel->volume > MAX_ADSR_VOLUME) te_channel->volume = MAX_ADSR_VOLUME;

            se_channel->adsr.volume = (int32_t)te_channel->volume;
            se_channel->adsr.volume = (int32_t)se_channel->adsr.volume;
        }

        break;
    }

    case 0xEC00: {
        if((opcode & 0xf) <= tick) {
            se_channel->adsr.volume = 0;
            te_channel->volume = 0;
        }

        break;
    }

    case 0x1900: {
        if(tick == (opcode & 0xf)) {
            se_channel->accumulator = 0;
            se_channel->lfsr = RANDOM_SEED;
        }

        break;
    }

    case 0x0900: {
        if(tick == 0) {
            if(from_program) {
                te_channel->program_period = opcode & 0xff;
            }

            //else {
                //tracker_engine->song->speed = opcode & 0xff;
            //}
        }

        break;
    }

    case 0x1A00: {
        te_channel->filter_cutoff += (opcode & 0xff);

        if(te_channel->filter_cutoff > 0x7ff) {
            te_channel->filter_cutoff = 0x7ff;
        }

        sound_engine_filter_set_coeff(
            &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);

        break;
    }

    case 0x1B00: {
        te_channel->filter_cutoff -= (opcode & 0xff);

        if(te_channel->filter_cutoff > 0x7ff) // unsigned int overflow
        {
            te_channel->filter_cutoff = 0;
        }

        sound_engine_filter_set_coeff(
            &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);

        break;
    }

    case 0x1C00: {
        if(tick == 0) {
            te_channel->filter_resonance = (opcode & 0xff);
            sound_engine_filter_set_coeff(
                &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);
        }

        break;
    }

    case 0x1D00: {
        te_channel->filter_resonance += (opcode & 0xff);

        if(te_channel->filter_resonance > 0xff) {
            te_channel->filter_resonance = 0xff;
        }

        sound_engine_filter_set_coeff(
            &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);
        break;
    }

    case 0x1E00: {
        te_channel->filter_resonance -= (opcode & 0xff);

        if(te_channel->filter_resonance > 0xff) {
            te_channel->filter_resonance = 0;
        }

        sound_engine_filter_set_coeff(
            &se_channel->filter, te_channel->filter_cutoff, te_channel->filter_resonance);
        break;
    }

    case 0x1f00: {
        if(tick == 0) {
            se_channel->ring_mod = (opcode & 0xff);
        }

        break;
    }

    case 0x2000: {
        if(tick == 0) {
            se_channel->hard_sync = (opcode & 0xff);
        }

        break;
    }

    case 0x2100: {
        if(tick == 0) {
            se_channel->adsr.a = (opcode & 0xff);

            if(se_channel->adsr.envelope_state == ATTACK) {
                se_channel->adsr.envelope_speed =
                    envspd(sound_engine, se_channel->adsr.a);
            }
        }

        break;
    }

    case 0x2200: {
        if(tick == 0) {
            se_channel->adsr.d = (opcode & 0xff);

            if(se_channel->adsr.envelope_state == DECAY) {
                se_channel->adsr.envelope_speed =
                    envspd(sound_engine, se_channel->adsr.d);
            }
        }

        break;
    }

    case 0x2300: {
        if(tick == 0) {
            se_channel->adsr.s = (opcode & 0xff);
        }

        break;
    }

    case 0x2400: {
        if(tick == 0) {
            se_channel->adsr.r = (opcode & 0xff);

            if(se_channel->adsr.envelope_state == RELEASE) {
                se_channel->adsr.envelope_speed =
                    envspd(sound_engine, se_channel->adsr.r);
            }
        }

        break;
    }

    case 0x2500: {
        if(tick == 0) {
            te_channel->program_counter = 0;
            te_channel->program_loop = 0;
            te_channel->program_period = 0;
            te_channel->program_tick = 0;
        }

        break;
    }

    /*case 0xC000: {
        if(tick == 0 && (opcode & 0xff) > 0) {
            tracker_engine_set_rate(opcode & 0xff);
        }

        break;
    }*/

    case 0x2600: {
        int prev = te_channel->note;

        te_channel->note += ((opcode & 0xff) << 8);
        if(prev > te_channel->note) te_channel->note = 0xffff;

        te_channel->target_note = te_channel->note;
        break;
    }

    case 0x2700: {
        int32_t prev = te_channel->note;

        te_channel->note -= ((opcode & 0xff) << 8);
        if(prev < te_channel->note) te_channel->note = 0;

        te_channel->target_note = te_channel->note;
        break;
    }

    case 0x2800: {
        te_channel->arpeggio_note = 0;
        te_channel->fixed_note = ((opcode & 0xff) << 8);

        break;
    }

    case 0xE500: {
        te_channel->finetune_note = ((int16_t)(opcode & 0xff) - 0x80) * 2;
        break;
    }

    case 0x2900: {
      if(tick == (opcode & 0xff)) {
        sound_engine_enable_gate(sound_engine, se_channel, 0);
      }

        break;
    }

    default: break;
  }
}

void DivPlatformFZT::tracker_engine_execute_volume(int vol, int chan)
{
  if(!(fztChan[chan].channel_flags & TEC_DISABLED)) 
  {
    sound_engine->channel[chan].adsr.volume = (int32_t)fztChan[chan].volume * (int32_t)vol / (MUS_NOTE_VOLUME_NONE);
    fztChan[chan].fur_volume = vol;
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
    uint32_t inst = (ins->fzt.program[tick].cmd) | (ins->fzt.program[tick].val) | ((ins->fzt.program[tick].unite ? 1 : 0) << 16);

    if(ins->fzt.program[tick].cmd == DivInstrumentFZT::TE_PROGRAM_NOP || ins->fzt.program[tick].cmd == DivInstrumentFZT::TE_PROGRAM_END)
    {
      inst = ins->fzt.program[tick].cmd;
    }

    if((inst & 0xffff) == 0x7fff) 
    {
      te_channel->channel_flags &= ~(TEC_PROGRAM_RUNNING);
      return;
    }

    uint8_t dont_reloop = 0;

    if((inst & 0xffff) != 0x7ffe) 
    {
        switch(inst & 0xff00)
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

              uint32_t next_inst = (ins->fzt.program[tick].cmd) | (ins->fzt.program[tick].val) | ((ins->fzt.program[tick].unite ? 1 : 0) << 16);
              if(ins->fzt.program[tick].cmd == DivInstrumentFZT::TE_PROGRAM_NOP || ins->fzt.program[tick].cmd == DivInstrumentFZT::TE_PROGRAM_END)
              {
                next_inst = ins->fzt.program[tick].cmd;
              }

              while((next_inst & 0xff00) != 0x7d00 && tick > 0) 
              {
                --tick;
                next_inst = (ins->fzt.program[tick].cmd) | (ins->fzt.program[tick].val) | ((ins->fzt.program[tick].unite ? 1 : 0) << 16);
                if(ins->fzt.program[tick].cmd == DivInstrumentFZT::TE_PROGRAM_NOP || ins->fzt.program[tick].cmd == DivInstrumentFZT::TE_PROGRAM_END)
                {
                  next_inst = ins->fzt.program[tick].cmd;
                }
                
                if(!(next_inst & 0x10000)) ++l;
              }

              --tick;

              dont_reloop = l <= 1;
            }

            break;
        }

        default: {
            do_command(inst & 0xffff, chann, te_channel->program_counter, true);
            break;
        }
        }
    }

    if((inst & 0xffff) == 0x7ffe || (inst & 0xff00) != 0x7f00) {
        ++tick;
        if(tick >= FZT_INST_PROG_LEN) {
            tick = 0;
        }
    }

    // skip to next on msb

    if(((inst & 0x10000) || ((inst & 0xff00) == 0x7d00) ||
        ((inst & 0xff00) == 0x7f00)) &&
       (inst & 0xffff) != 0x7ffe && !dont_reloop) {
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
            vib = (int32_t)(sound_engine_triangle(te_channel->vibrato_position >> 6) - WAVE_AMP / 2) * (int32_t)te_channel->vibrato_depth / (256 * 128);
        }
    }

    if(te_channel->flags & TE_ENABLE_PWM) {
        if(te_channel->pwm_delay > 0) {
            te_channel->pwm_delay--;
        }

        else {
            te_channel->pwm_position += ((uint32_t)te_channel->pwm_speed << 20); // so minimum PWM speed is even lower than minimum vibrato speed
            pwm = ((int32_t)sound_engine_triangle((te_channel->pwm_position) >> 6) - WAVE_AMP / 2) * (int32_t)te_channel->pwm_depth / (256 * 16);
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

    int32_t chn_note = (te_channel->fixed_note != 0xffff ? te_channel->fixed_note : te_channel->note) + vib + (te_channel->arpeggio_note * 256) + te_channel->finetune_note + te_channel->pitch_note;

    if(chn_note < 0) {
        chn_note = 0;
    }

    if(chn_note > ((12 * 7 + 11) << 8)) {
        chn_note = ((12 * 7 + 11) << 8); // highest note is B-7
    }

    tracker_engine_set_note(chan, (uint16_t)chn_note, false);
  }

  if((fztChan[chan].channel_flags & TEC_DISABLED) || isMuted[chan]) // so we can't set some non-zero volme from inst program too
  {
    sound_engine->channel[chan].adsr.volume = 0;
  }
}

void DivPlatformFZT::tracker_engine_advance_tick(int chann, int opcode, bool do_retrig)
{
  //SoundEngineChannel* se_channel = &sound_engine->channel[chann];
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
    int notee = (chan[chann].fzt_note + chan[chann].fzt_octave * 12);
    if(chan[chann].fzt_note != -1 && chan[chann].fzt_note < 20)
    {
      //uint8_t prev_adsr_volume = se_channel->adsr.volume;
      //int realnote=(note+(signed char)octave*12)+60;

      if((opcode & 0xff00) == 0x0300)
      {
        if(pinst->fzt.flags & TE_RETRIGGER_ON_SLIDE) 
        {
          uint16_t temp_note = te_channel->note;
          tracker_engine_trigger_instrument_internal(chann, pinst, note << 8);
          te_channel->note = temp_note;
        }

        notee = (chan[chann].fzt_note+chan[chann].fzt_octave*12);
        if(notee >= 0 && notee <= MAX_NOTE)
        {
          //notee <<= 8;
          te_channel->target_note = ((notee + (int)pinst->fzt.base_note - MIDDLE_C) << 8) + (int)pinst->fzt.finetune;
          te_channel->slide_speed = (opcode & 0xff);
        }
      }

      else if((opcode & 0xff00) == 0xea00) 
      {
        te_channel->note = te_channel->target_note = te_channel->last_note = ((notee + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;
      }

      else {
        if(do_retrig)
        {
          tracker_engine_trigger_instrument_internal(chann, pinst, notee << 8);
          te_channel->note =
              ((notee + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;

          te_channel->target_note =
              ((notee + pinst->fzt.base_note - MIDDLE_C) << 8) + pinst->fzt.finetune;
        }
      }
    }
  }

  tracker_engine_execute_track_command(chann, current_tick == note_delay, opcode);

  //tracker_engine_advance_channel(chann);
}

void DivPlatformFZT::tick(bool sysTick) 
{
  for (int i=0; i<FZT_NUM_CHANNELS; i++) 
  {
    chan[i].std.next();

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->had)
    {
      sound_engine->channel[i].adsr.volume = (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->val & 255) * fztChan[i].fur_volume / MUS_NOTE_VOLUME_NONE;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->had) 
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val >= 0)
      {
        if(chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val & (0x40000000))
        {
          fztChan[i].fixed_note = (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val & ~0x40000000) * 256;
          fztChan[i].arpeggio_note = 0;
        }
        else
        {
          fztChan[i].fixed_note = 0xffff;
          fztChan[i].arpeggio_note = (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val & ~0x40000000);
        }
      }
      else
      {
        if((chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val & (0x40000000)))
        {
          fztChan[i].fixed_note = 0xffff;
          fztChan[i].arpeggio_note = (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val | 0x40000000);
        }
        else
        {
          fztChan[i].fixed_note = (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val) * 256;
          fztChan[i].arpeggio_note = 0;
        }
      }

      if(fztChan[i].fixed_note < 0) fztChan[i].fixed_note = 0;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->had) 
    {
      if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->mode) 
      {
        fztChan[i].note += chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
        fztChan[i].pitch_note = 0;
      } 
      else 
      {
        fztChan[i].pitch_note = chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
      }
      chan[i].freqChanged=true;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->had) 
    {
      switch (chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->mode) 
      {
        case 0: // absolute
          {
            fztChan[i].pw = chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val;
          }
          break;
        case 1: // relative
          {
            fztChan[i].pw += chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val;

            if(fztChan[i].pw < 0) fztChan[i].pw = 0;
            if(fztChan[i].pw > 0xfff) fztChan[i].pw = 0;
          }
          break;
        default:
          break;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->had) 
    {
      sound_engine->channel[i].waveform = chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->val & 63;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->had) 
    {
      switch (chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->mode) 
      {
        case 0: // absolute
          {
            fztChan[i].filter_cutoff = chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->val;
          }
          break;
        case 1: // relative
          {
            fztChan[i].filter_cutoff += chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->val;

            if(fztChan[i].filter_cutoff < 0) fztChan[i].filter_cutoff = 0;
            if(fztChan[i].filter_cutoff > 0xfff) fztChan[i].filter_cutoff = 0;
          }
          break;
        default:
          break;
      }

      sound_engine_filter_set_coeff(&sound_engine->channel[i].filter, fztChan[i].filter_cutoff, fztChan[i].filter_resonance);
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->had) 
    {
      fztChan[i].filter_type = chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->val & 7;
      sound_engine->channel[i].filter_mode = chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->val & 7;
      //sound_engine_filter_set_coeff(&sound_engine->channel[i].filter, fztChan[i].filter_cutoff, fztChan[i].filter_resonance);
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX2)->had) 
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_EX2)->val)
      {
        sound_engine->channel[i].flags |= SE_ENABLE_FILTER;
      }
      else
      {
        sound_engine->channel[i].flags &= ~SE_ENABLE_FILTER;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX3)->had)
    {
      fztChan[i].filter_resonance = chan[i].std.get_div_macro_struct(DIV_MACRO_EX3)->val & 0xff;
      sound_engine_filter_set_coeff(&sound_engine->channel[i].filter, fztChan[i].filter_cutoff, fztChan[i].filter_resonance);
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PHASE_RESET)->had)
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_PHASE_RESET)->val)
      {
        sound_engine->channel[i].accumulator = 0;
        sound_engine->channel[i].lfsr = RANDOM_SEED;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->had)
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->val)
      {
        uint8_t prev_vol_tr = fztChan[i].volume;
        uint8_t prev_vol_cyd = sound_engine->channel[i].adsr.volume;
        DivInstrument* ins=parent->getIns(chan[i].ins,DIV_INS_FZT);
        tracker_engine_trigger_instrument_internal(i, ins, fztChan[i].last_note);
        fztChan[i].volume = prev_vol_tr;
        sound_engine->channel[i].adsr.volume = prev_vol_cyd;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX5)->had)
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_EX5)->val)
      {
        sound_engine->channel[i].flags |= SE_ENABLE_RING_MOD;
      }
      else
      {
        sound_engine->channel[i].flags &= ~SE_ENABLE_RING_MOD;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX6)->had)
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_EX6)->val < FZT_NUM_CHANNELS)
      {
        sound_engine->channel[i].ring_mod = chan[i].std.get_div_macro_struct(DIV_MACRO_EX6)->val;
      }
      else
      {
        sound_engine->channel[i].ring_mod = 0xff;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX7)->had)
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_EX7)->val)
      {
        sound_engine->channel[i].flags |= SE_ENABLE_HARD_SYNC;
      }
      else
      {
        sound_engine->channel[i].flags &= ~SE_ENABLE_HARD_SYNC;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX8)->had)
    {
      if(chan[i].std.get_div_macro_struct(DIV_MACRO_EX8)->val < FZT_NUM_CHANNELS)
      {
        sound_engine->channel[i].hard_sync = chan[i].std.get_div_macro_struct(DIV_MACRO_EX8)->val;
      }
      else
      {
        sound_engine->channel[i].hard_sync = 0xff;
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX9)->had)
    {
      sound_engine->channel[i].adsr.a = chan[i].std.get_div_macro_struct(DIV_MACRO_EX9)->val & 0xff;

      if(sound_engine->channel[i].adsr.envelope_state == ATTACK) 
      {
        sound_engine->channel[i].adsr.envelope_speed =
            envspd(sound_engine, sound_engine->channel[i].adsr.a);
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX10)->had)
    {
      sound_engine->channel[i].adsr.d = chan[i].std.get_div_macro_struct(DIV_MACRO_EX10)->val & 0xff;

      if(sound_engine->channel[i].adsr.envelope_state == DECAY)
      {
        sound_engine->channel[i].adsr.envelope_speed =
            envspd(sound_engine, sound_engine->channel[i].adsr.d);
      }
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX11)->had)
    {
      sound_engine->channel[i].adsr.s = chan[i].std.get_div_macro_struct(DIV_MACRO_EX11)->val & 0xff;
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX12)->had)
    {
      sound_engine->channel[i].adsr.r = chan[i].std.get_div_macro_struct(DIV_MACRO_EX12)->val & 0xff;

      if(sound_engine->channel[i].adsr.envelope_state == RELEASE)
      {
        sound_engine->channel[i].adsr.envelope_speed =
            envspd(sound_engine, sound_engine->channel[i].adsr.r);
      }
    }

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

      if(c.value != 0xffff)
      {
        sound_engine->channel[c.chan].adsr.volume = 0;
        fztChan[c.chan].volume = 0;
      }
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
    case DIV_CMD_NOTE_FZT:
      //logV("note fzt");
      chan[c.chan].fzt_note = c.value;
      chan[c.chan].fzt_octave = c.value2 & 0xff;
      current_tick = 0;
      break;
    case DIV_CMD_VOLUME_FZT:
      //logV("vol fzt");
      tracker_engine_execute_volume(c.value, c.chan);
      break;
    case DIV_CMD_EFFECT_FZT:
      //logV("eff fzt");
      current_tick = c.value >> 8;
      if(!(c.value2 & (1 << 24)))
      {
        chan[c.chan].fzt_note = (c.value2 >> 8) & 0xff;
        chan[c.chan].fzt_octave = (c.value2 >> 16) & 0xff;
      }
      
      tracker_engine_advance_tick(c.chan, ((c.value & 0xff) << 8) | (c.value2 & 0xff), false);
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
  if(mute)
  {
    fztChan[ch].channel_flags |= TEC_DISABLED;
  }
  else
  {
    fztChan[ch].channel_flags &= ~TEC_DISABLED;
  }
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
    fztChan[i].fur_volume = MUS_NOTE_VOLUME_NONE;
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
  rate=chipClock / 10;
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