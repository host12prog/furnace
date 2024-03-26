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

void DivPlatformFZT::tick(bool sysTick) {
  for (int i=0; i<FZT_NUM_CHANNELS; i++) {
    chan[i].std.next();
  }
}

int DivPlatformFZT::dispatch(DivCommand c) {
  if (c.chan>FZT_NUM_CHANNELS - 1) return 0;
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_SID2);
      if (c.value!=DIV_NOTE_NULL) {
        chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value);
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;
      chan[c.chan].macroInit(ins);


      sound_engine_set_channel_frequency(sound_engine, &sound_engine->channel[c.chan], MIDDLE_C << 8);
      sound_engine->channel[c.chan].waveform = SE_WAVEFORM_TRIANGLE;
      sound_engine->channel[c.chan].adsr.a = 0x20;
      sound_engine->channel[c.chan].adsr.volume = 0x80;
      sound_engine_enable_gate(sound_engine, &sound_engine->channel[c.chan], true);
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      //chan[c.chan].macroInit(NULL);
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
  for (int i=0; i<3; i++) {
    chan[i]=DivPlatformFZT::Channel();
    chan[i].std.setEngine(parent);
    
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