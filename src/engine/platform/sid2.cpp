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

#include "sid2.h"
#include "../engine.h"
#include "IconsFontAwesome4.h"
#include <math.h>
#include "../../ta-log.h"

#define rWrite(a,v) if (!skipRegisterWrites) {writes.push(QueuedWrite(a,v)); if (dumpWrites) {addWrite(a,v);} }

#define CHIP_FREQBASE 524288

const char* regCheatSheetSID2[]={

  NULL
};

const char** DivPlatformSID2::getRegisterSheet() {
  return regCheatSheetSID2;
}

short DivPlatformSID2::runFakeFilter(unsigned char ch, int in) {
  if (!(regPool[0x17]&(1<<ch))) {
    if (regPool[0x18]&0x80 && ch==2) return 0;
    float fin=in;
    fin*=(float)(regPool[0x18]&15)/20.0f;
    return CLAMP(fin,-32768,32767);
  }

  // taken from dSID
  float fin=in;
  float fout=0;
  float ctf=fakeCutTable[((regPool[0x15]&7)|(regPool[0x16]<<3))&0x7ff];
  float reso=(sidIs6581?
    ((regPool[0x17]>0x5F)?8.0/(float)(regPool[0x17]>>4):1.41):
    (pow(2,((float)(4-(float)(regPool[0x17]>>4))/8)))
  );
  float tmp=fin+fakeBand[ch]*reso+fakeLow[ch];
  if (regPool[0x18]&0x40) {
    fout-=tmp;
  }
  tmp=fakeBand[ch]-tmp*ctf;
  fakeBand[ch]=tmp;
  if (regPool[0x18]&0x20) {
    fout-=tmp;
  }
  tmp=fakeLow[ch]+tmp*ctf;
  fakeLow[ch]=tmp;
  if (regPool[0x18]&0x10) {
    fout+=tmp;
  }

  fout*=(float)(regPool[0x18]&15)/20.0f;
  return CLAMP(fout,-32768,32767);
}

void DivPlatformSID2::acquire(short** buf, size_t len) 
{
  int dcOff=sid2->get_dc(0);

  for (size_t i=0; i<len; i++) 
  {
    if (!writes.empty()) 
    {
      QueuedWrite w=writes.front();
      sid2->write(w.addr,w.val);
      regPool[w.addr&0x1f]=w.val;
      writes.pop();
    }
    
    sid2->clock();
    buf[0][i]=sid2->output();
    if (++writeOscBuf>=16) 
    {
      writeOscBuf=0;
      oscBuf[0]->data[oscBuf[0]->needle++]=runFakeFilter(0,(sid2->last_chan_out[0]-dcOff)>>5);
      oscBuf[1]->data[oscBuf[1]->needle++]=runFakeFilter(1,(sid2->last_chan_out[1]-dcOff)>>5);
      oscBuf[2]->data[oscBuf[2]->needle++]=runFakeFilter(2,(sid2->last_chan_out[2]-dcOff)>>5);
    }
  }
}

void DivPlatformSID2::updateFilter() {
  rWrite(0x15,filtCut&7);
  rWrite(0x16,filtCut>>3);
  rWrite(0x17,(filtRes<<4)|(chan[2].filter<<2)|(chan[1].filter<<1)|(int)(chan[0].filter));
  rWrite(0x18,(filtControl<<4)|vol);
}

void DivPlatformSID2::tick(bool sysTick) {
  bool willUpdateFilter=false;
  for (int _i=0; _i<3; _i++) {
    int i=chanOrder[_i];

    chan[i].std.next();
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->had) {
      vol=MIN(15,chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->val);
      willUpdateFilter=true;
    }

    if (NEW_ARP_STRAT) {
      chan[i].handleArp();
    } else if (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->had) {
      if (!chan[i].inPorta) {
        chan[i].baseFreq=NOTE_FREQUENCY(parent->calcArp(chan[i].note,chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val));
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->had) {
      DivInstrument* ins=parent->getIns(chan[i].ins,DIV_INS_C64);
      if (ins->c64.dutyIsAbs) {
        chan[i].duty=chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val;
      } else {
        if (multiplyRel) {
          chan[i].duty-=((signed char)chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val)*4;
        } else {
          chan[i].duty-=chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val;
        }
      }
      rWrite(i*7+2,chan[i].duty&0xff);
      rWrite(i*7+3,chan[i].duty>>8);
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->had) {
      chan[i].wave=chan[i].std.get_div_macro_struct(DIV_MACRO_WAVE)->val;
      rWrite(i*7+4,(chan[i].wave<<4)|(chan[i].test<<3)|(chan[i].ring<<2)|(chan[i].sync<<1)|(int)(chan[i].active && chan[i].gate));
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
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->had) { // new cutoff macro
      DivInstrument* ins=parent->getIns(chan[i].ins,DIV_INS_C64);
      if (ins->c64.filterIsAbs) {
        filtCut=MIN(2047,chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->val);
      } else {
        if (multiplyRel) {
          filtCut+=((signed char)chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->val)*7;
        } else {
          filtCut+=chan[i].std.get_div_macro_struct(DIV_MACRO_ALG)->val;
        }
        if (filtCut>2047) filtCut=2047;
        if (filtCut<0) filtCut=0;
      }
      willUpdateFilter=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->had) {
      filtControl=chan[i].std.get_div_macro_struct(DIV_MACRO_EX1)->val&15;
      willUpdateFilter=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX2)->had) {
      filtRes=chan[i].std.get_div_macro_struct(DIV_MACRO_EX2)->val&15;
      willUpdateFilter=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX3)->had) {
      chan[i].filter=chan[i].std.get_div_macro_struct(DIV_MACRO_EX3)->val&1;
      willUpdateFilter=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->had) {
      chan[i].gate=chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->val&1;
      chan[i].sync=chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->val&2;
      chan[i].ring=chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->val&4;
      chan[i].test=chan[i].std.get_div_macro_struct(DIV_MACRO_EX4)->val&8;
      chan[i].freqChanged=true;
      rWrite(i*7+4,(chan[i].wave<<4)|(chan[i].test<<3)|(chan[i].ring<<2)|(chan[i].sync<<1)|(int)(chan[i].active && chan[i].gate));
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX5)->had) {
      chan[i].attack=chan[i].std.get_div_macro_struct(DIV_MACRO_EX5)->val&15;
      rWrite(i*7+5,(chan[i].attack<<4)|(chan[i].decay));
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX6)->had) {
      chan[i].decay=chan[i].std.get_div_macro_struct(DIV_MACRO_EX6)->val&15;
      rWrite(i*7+5,(chan[i].attack<<4)|(chan[i].decay));
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX7)->had) {
      chan[i].sustain=chan[i].std.get_div_macro_struct(DIV_MACRO_EX7)->val&15;
      rWrite(i*7+6,(chan[i].sustain<<4)|(chan[i].release));
    }

    if (chan[i].std.get_div_macro_struct(DIV_MACRO_EX8)->had) {
      chan[i].release=chan[i].std.get_div_macro_struct(DIV_MACRO_EX8)->val&15;
      rWrite(i*7+6,(chan[i].sustain<<4)|(chan[i].release));
    }

    if (sysTick) {
      if (chan[i].testWhen>0) {
        if (--chan[i].testWhen<1) {
          if (!chan[i].resetMask && !chan[i].inPorta) {
            DivInstrument* ins=parent->getIns(chan[i].ins,DIV_INS_C64);
            rWrite(i*7+5,testAD);
            rWrite(i*7+6,testSR);
            rWrite(i*7+4,(chan[i].wave<<4)|(ins->c64.noTest?0:8)|(chan[i].test<<3)|(chan[i].ring<<2)|(chan[i].sync<<1));
          }
        }
      }
    }

    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) {
      chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,false,8,chan[i].pitch2,chipClock,CHIP_FREQBASE);
      if (chan[i].freq<0) chan[i].freq=0;
      if (chan[i].freq>0xffff) chan[i].freq=0xffff;
      if (chan[i].keyOn) {
        rWrite(i*7+5,(chan[i].attack<<4)|(chan[i].decay));
        rWrite(i*7+6,(chan[i].sustain<<4)|(chan[i].release));
        rWrite(i*7+4,(chan[i].wave<<4)|(chan[i].test<<3)|(chan[i].ring<<2)|(chan[i].sync<<1)|(chan[i].gate?1:0));
      }
      if (chan[i].keyOff) {
        rWrite(i*7+5,(chan[i].attack<<4)|(chan[i].decay));
        rWrite(i*7+6,(chan[i].sustain<<4)|(chan[i].release));
        rWrite(i*7+4,(chan[i].wave<<4)|(chan[i].test<<3)|(chan[i].ring<<2)|(chan[i].sync<<1)|0);
      }
      rWrite(i*7,chan[i].freq&0xff);
      rWrite(i*7+1,chan[i].freq>>8);
      if (chan[i].keyOn) chan[i].keyOn=false;
      if (chan[i].keyOff) chan[i].keyOff=false;
      chan[i].freqChanged=false;
    }
  }
  if (willUpdateFilter) updateFilter();
}

int DivPlatformSID2::dispatch(DivCommand c) {
  if (c.chan>2) return 0;
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_C64);
      if (c.value!=DIV_NOTE_NULL) {
        chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value);
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;
      chan[c.chan].test=false;
      if (chan[c.chan].insChanged || chan[c.chan].resetDuty || ins->std.get_macro(DIV_MACRO_WAVE, true)->len>0) {
        chan[c.chan].duty=ins->c64.duty;
        rWrite(c.chan*7+2,chan[c.chan].duty&0xff);
        rWrite(c.chan*7+3,chan[c.chan].duty>>8);
      }
      if (chan[c.chan].insChanged) {
        chan[c.chan].wave=(ins->c64.noiseOn<<3)|(ins->c64.pulseOn<<2)|(ins->c64.sawOn<<1)|(int)(ins->c64.triOn);
        chan[c.chan].attack=ins->c64.a;
        chan[c.chan].decay=(ins->c64.s==15)?0:ins->c64.d;
        chan[c.chan].sustain=ins->c64.s;
        chan[c.chan].release=ins->c64.r;
        chan[c.chan].ring=ins->c64.ringMod;
        chan[c.chan].sync=ins->c64.oscSync;
      }
      if (chan[c.chan].insChanged || chan[c.chan].resetFilter) {
        chan[c.chan].filter=ins->c64.toFilter;
        if (ins->c64.initFilter) {
          filtCut=ins->c64.cut;
          filtRes=ins->c64.res;
          filtControl=(int)(ins->c64.lp)|(ins->c64.bp<<1)|(ins->c64.hp<<2)|(ins->c64.ch3off<<3);
        }
        updateFilter();
      }
      if (chan[c.chan].insChanged) {
        chan[c.chan].insChanged=false;
      }
      if (keyPriority) {
        if (chanOrder[1]==c.chan) {
          chanOrder[1]=chanOrder[2];
          chanOrder[2]=c.chan;
        } else if (chanOrder[0]==c.chan) {
          chanOrder[0]=chanOrder[1];
          chanOrder[1]=chanOrder[2];
          chanOrder[2]=c.chan;
        }
      }
      chan[c.chan].macroInit(ins);
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
          vol=chan[c.chan].outVol;
        } else {
          vol=chan[c.chan].vol;
        }
        updateFilter();
      }
      break;
    case DIV_CMD_GET_VOLUME:
      return chan[c.chan].vol;
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
    case DIV_CMD_STD_NOISE_MODE:
      chan[c.chan].duty=(c.value*4095)/100;
      rWrite(c.chan*7+2,chan[c.chan].duty&0xff);
      rWrite(c.chan*7+3,chan[c.chan].duty>>8);
      break;
    case DIV_CMD_C64_FINE_DUTY:
      chan[c.chan].duty=c.value;
      rWrite(c.chan*7+2,chan[c.chan].duty&0xff);
      rWrite(c.chan*7+3,chan[c.chan].duty>>8);
      break;
    case DIV_CMD_WAVE:
      chan[c.chan].wave=c.value;
      rWrite(c.chan*7+4,(chan[c.chan].wave<<4)|(chan[c.chan].test<<3)|(chan[c.chan].ring<<2)|(chan[c.chan].sync<<1)|(int)(chan[c.chan].active && chan[c.chan].gate));
      break;
    case DIV_CMD_LEGATO:
      chan[c.chan].baseFreq=NOTE_FREQUENCY(c.value+((HACKY_LEGATO_MESS)?(chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->val):(0)));
      chan[c.chan].freqChanged=true;
      chan[c.chan].note=c.value;
      break;
    case DIV_CMD_PRE_PORTA:
      if (chan[c.chan].active && c.value2) {
        if (parent->song.resetMacroOnPorta || parent->song.preNoteNoEffect) {
          chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_C64));
          chan[c.chan].keyOn=true;
        }
      }
      if (!chan[c.chan].inPorta && c.value && !parent->song.brokenPortaArp && chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=NOTE_FREQUENCY(chan[c.chan].note);
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_PRE_NOTE:
      if (resetTime) chan[c.chan].testWhen=c.value-resetTime+1;
      break;
    case DIV_CMD_GET_VOLMAX:
      return 15;
      break;
    case DIV_CMD_C64_CUTOFF:
      if (c.value>100) c.value=100;
      filtCut=(c.value+2)*2047/102;
      updateFilter();
      break;
    case DIV_CMD_C64_FINE_CUTOFF:
      filtCut=c.value;
      updateFilter();
      break;
    case DIV_CMD_C64_RESONANCE:
      if (c.value>15) c.value=15;
      filtRes=c.value;
      updateFilter();
      break;
    case DIV_CMD_C64_FILTER_MODE:
      filtControl=c.value&7;
      updateFilter();
      break;
    case DIV_CMD_C64_RESET_TIME:
      resetTime=c.value;
      break;
    case DIV_CMD_C64_RESET_MASK:
      chan[c.chan].resetMask=c.value;
      break;
    case DIV_CMD_C64_FILTER_RESET:
      if (c.value&15) {
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_C64);
        if (ins->c64.initFilter) {
          filtCut=ins->c64.cut;
          updateFilter();
        }
      }
      chan[c.chan].resetFilter=c.value>>4;
      break;
    case DIV_CMD_C64_DUTY_RESET:
      if (c.value&15) {
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_C64);
        chan[c.chan].duty=ins->c64.duty;
        rWrite(c.chan*7+2,chan[c.chan].duty&0xff);
        rWrite(c.chan*7+3,chan[c.chan].duty>>8);
      }
      chan[c.chan].resetDuty=c.value>>4;
      break;
    case DIV_CMD_C64_EXTENDED:
      switch (c.value>>4) {
        case 0:
          chan[c.chan].attack=c.value&15;
          if (!no1EUpdate) {
            rWrite(c.chan*7+5,(chan[c.chan].attack<<4)|(chan[c.chan].decay));
          }
          break;
        case 1:
          chan[c.chan].decay=c.value&15;
          if (!no1EUpdate) {
            rWrite(c.chan*7+5,(chan[c.chan].attack<<4)|(chan[c.chan].decay));
          }
          break;
        case 2:
          chan[c.chan].sustain=c.value&15;
          if (!no1EUpdate) {
            rWrite(c.chan*7+6,(chan[c.chan].sustain<<4)|(chan[c.chan].release));
          }
          break;
        case 3:
          chan[c.chan].release=c.value&15;
          if (!no1EUpdate) {
            rWrite(c.chan*7+6,(chan[c.chan].sustain<<4)|(chan[c.chan].release));
          }
          break;
        case 4:
          chan[c.chan].ring=c.value;
          rWrite(c.chan*7+4,(chan[c.chan].wave<<4)|(chan[c.chan].test<<3)|(chan[c.chan].ring<<2)|(chan[c.chan].sync<<1)|(int)(chan[c.chan].active && chan[c.chan].gate));
          break;
        case 5:
          chan[c.chan].sync=c.value;
          rWrite(c.chan*7+4,(chan[c.chan].wave<<4)|(chan[c.chan].test<<3)|(chan[c.chan].ring<<2)|(chan[c.chan].sync<<1)|(int)(chan[c.chan].active && chan[c.chan].gate));
          break;
        case 6:
          filtControl&=7;
          filtControl|=(!!c.value)<<3;
          break;
      }
      break;
    case DIV_CMD_C64_AD:
      chan[c.chan].attack=c.value>>4;
      chan[c.chan].decay=c.value&15;
      rWrite(c.chan*7+5,(chan[c.chan].attack<<4)|(chan[c.chan].decay));
      break;
    case DIV_CMD_C64_SR:
      chan[c.chan].sustain=c.value>>4;
      chan[c.chan].release=c.value&15;
      rWrite(c.chan*7+6,(chan[c.chan].sustain<<4)|(chan[c.chan].release));
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

void DivPlatformSID2::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
  sid2->set_is_muted(ch,mute);
}

void DivPlatformSID2::forceIns() {
  for (int i=0; i<3; i++) {
    chan[i].insChanged=true;
    chan[i].testWhen=0;
    if (chan[i].active) {
      chan[i].keyOn=true;
      chan[i].freqChanged=true;
    }
  }
  updateFilter();
}

void DivPlatformSID2::notifyInsChange(int ins) {
  for (int i=0; i<3; i++) {
    if (chan[i].ins==ins) {
      chan[i].insChanged=true;
    }
  }
}

void DivPlatformSID2::notifyInsDeletion(void* ins) {
  for (int i=0; i<3; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void* DivPlatformSID2::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformSID2::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivChannelModeHints DivPlatformSID2::getModeHints(int ch) {
  DivChannelModeHints ret;
  ret.count=1;
  ret.hint[0]=ICON_FA_BELL_SLASH_O;
  ret.type[0]=0;
  if (ch==2 && (filtControl&8)) {
    ret.type[0]=7;
  } else if (chan[ch].test && !chan[ch].gate) {
    ret.type[0]=5;
  } else if (chan[ch].test) {
    ret.type[0]=6;
  } else if (!chan[ch].gate) {
    ret.type[0]=4;
  }

  return ret;
}

DivDispatchOscBuffer* DivPlatformSID2::getOscBuffer(int ch) {
  return oscBuf[ch];
}

unsigned char* DivPlatformSID2::getRegisterPool() {
  return regPool;
}

int DivPlatformSID2::getRegisterPoolSize() {
  return 32;
}

bool DivPlatformSID2::getDCOffRequired() {
  return true;
}

bool DivPlatformSID2::getWantPreNote() {
  return true;
}

bool DivPlatformSID2::isVolGlobal() {
  return true;
}

float DivPlatformSID2::getPostAmp() {
  return 1.0f;
}

void DivPlatformSID2::reset() {
  while (!writes.empty()) writes.pop();
  for (int i=0; i<3; i++) {
    chan[i]=DivPlatformSID2::Channel();
    chan[i].std.setEngine(parent);
    fakeLow[i]=0;
    fakeBand[i]=0;
  }

  sid2->reset();
  memset(regPool,0,32);

  rWrite(0x18,0x0f);

  filtControl=7;
  filtRes=0;
  filtCut=2047;
  resetTime=initResetTime;
  vol=15;

  chanOrder[0]=0;
  chanOrder[1]=1;
  chanOrder[2]=2;
}

void DivPlatformSID2::poke(unsigned int addr, unsigned short val) {
  rWrite(addr,val);
}

void DivPlatformSID2::poke(std::vector<DivRegWrite>& wlist) {
  for (DivRegWrite& i: wlist) rWrite(i.addr,i.val);
}

void DivPlatformSID2::setChipModel(bool is6581) {
  sidIs6581=is6581;
}

void DivPlatformSID2::setFlags(const DivConfig& flags) {
  switch (flags.getInt("clockSel",0)) {
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
  }
  CHECK_CUSTOM_CLOCK;
  rate=chipClock;
  for (int i=0; i<3; i++) {
    oscBuf[i]->rate=rate/16;
  }
  keyPriority=flags.getBool("keyPriority",true);
  no1EUpdate=flags.getBool("no1EUpdate",false);
  multiplyRel=flags.getBool("multiplyRel",false);
  testAD=((flags.getInt("testAttack",0)&15)<<4)|(flags.getInt("testDecay",0)&15);
  testSR=((flags.getInt("testSustain",0)&15)<<4)|(flags.getInt("testRelease",0)&15);
  initResetTime=flags.getInt("initResetTime",2);
  if (initResetTime<0) initResetTime=1;

  // init fake filter table
  // taken from dSID
  double cutRatio=-2.0*3.14*(sidIs6581?(((double)oscBuf[0]->rate/44100.0)*(20000.0/256.0)):(12500.0/256.0))/(double)oscBuf[0]->rate;

  for (int i=0; i<2048; i++) 
  {
    double c=(double)i/8.0+0.2;
    c=1-exp(c*cutRatio);
    fakeCutTable[i]=c;
  }
}

int DivPlatformSID2::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;
  needInitTables=true;
  writeOscBuf=0;
  
  for (int i=0; i<3; i++) 
  {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }

  sid2=new SID2;

  sid2->set_chip_model(MOS8580);

  setFlags(flags);

  reset();

  return 3;
}

void DivPlatformSID2::quit() {
  for (int i=0; i<3; i++) 
  {
    delete oscBuf[i];
  }
  if (sid2!=NULL) delete sid2;
}

DivPlatformSID2::~DivPlatformSID2() {
}
