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

#include "5e01.h"
#include "../engine.h"
#include "../../ta-log.h"
#include <stddef.h>
#include <math.h>

#ifdef HAVE_GUI
#include "../../gui/gui.h"
extern FurnaceGUI g;
#endif

#ifdef HAVE_GUI
#define _LE(string) g.locale.getText(string)
#else
#define _LE(string) (string)
#endif

#define CHIP_DIVIDER 16

#define rWrite(a,v) if (!skipRegisterWrites) {doWrite(a,v); regPool[(a)&0x7f]=v; if (dumpWrites) {addWrite(a,v);} }

const char* regCheatSheet5E01[]={
  "S0Volume", "4100",
  "S0Sweep", "4101",
  "S0PeriodL", "4102",
  "S0PeriodH", "4103",
  "S1Volume", "4104",
  "S1Sweep", "4105",
  "S1PeriodL", "4106",
  "S1PeriodH", "4107",
  "TRVolume", "4108",
  "TRWave", "4109",
  "TRPeriodL", "410A",
  "TRPeriodH", "410B",
  "NSVolume", "410C",
  "NSPeriod", "410E",
  "NSLength", "410F",
  "DMCControl", "4110",
  "DMCLoad", "4111",
  "DMCAddr", "4112",
  "DMCLength", "4113",
  "APUControl", "4115",
  "APUFrameCtl", "4117",
  NULL
};

const char** DivPlatform5E01::getRegisterSheet() {
  return regCheatSheet5E01;
}

void DivPlatform5E01::doWrite(unsigned short addr, unsigned char data) {
  nes1_NP->Write(addr,data);
  nes2_NP->Write(addr,data);
}

#define doPCM \
  if (!dpcmMode && dacSample!=-1) { \
    dacPeriod+=dacRate; \
    if (dacPeriod>=rate) { \
      DivSample* s=parent->getSample(dacSample); \
      if (s->samples>0 && s->data8) { \
        if (!isMuted[4]) { \
          unsigned char next=((unsigned char)s->data8[dacPos]+0x80)>>1; \
          if (dacAntiClickOn && dacAntiClick<next) { \
            dacAntiClick+=8; \
            rWrite(0x4111,dacAntiClick); \
          } else { \
            dacAntiClickOn=false; \
            rWrite(0x4111,next); \
          } \
        } \
        dacPos++; \
        if (s->isLoopable() && dacPos>=(unsigned int)s->loopEnd) { \
          dacPos=s->loopStart; \
        } else if (dacPos>=s->samples) { \
          dacSample=-1; \
        } \
        dacPeriod-=rate; \
      } else { \
        dacSample=-1; \
      } \
    } \
  }

void DivPlatform5E01::acquire_NSFPlay(short** buf, size_t len) {
  int out1[2];
  int out2[2];
  for (size_t i=0; i<len; i++) {
    doPCM;
  
    nes1_NP->Tick(8);
    nes2_NP->TickFrameSequence(8);
    nes2_NP->Tick(8);
    nes1_NP->Render(out1);
    nes2_NP->Render(out2);

    int sample=(out1[0]+out1[1]+out2[0]+out2[1])<<1;
    if (sample>32767) sample=32767;
    if (sample<-32768) sample=-32768;
    buf[0][i]=sample;
    if (++writeOscBuf>=4) {
      writeOscBuf=0;
      oscBuf[0]->data[oscBuf[0]->needle++]=nes1_NP->out[0]<<11;
      oscBuf[1]->data[oscBuf[1]->needle++]=nes1_NP->out[1]<<11;
      oscBuf[2]->data[oscBuf[2]->needle++]=nes2_NP->out[0]<<11;
      oscBuf[3]->data[oscBuf[3]->needle++]=nes2_NP->out[1]<<11;
      oscBuf[4]->data[oscBuf[4]->needle++]=nes2_NP->out[2]<<8;
    }
  }
}

void DivPlatform5E01::acquire(short** buf, size_t len) {
  acquire_NSFPlay(buf,len);
}

static unsigned char noiseTable[253]={
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 10,
  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,

  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,
  19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8,
  7, 6, 5, 4, 3, 2, 1, 0,

  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,
  19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8,
  7, 6, 5, 4, 3, 2, 1, 0,
  
  31, 30, 29, 28, 27, 26, 25, 24,
  
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31
};

/*static unsigned char noiseTable[253]={
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4,
  15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,
  15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,
  3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5, 4,
  15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,
  3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5, 4,
  15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,
  3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5, 4,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
  15
};*/

unsigned char DivPlatform5E01::calcDPCMRate(int inRate) {
  if (inRate<4450) return 0;
  if (inRate<5000) return 1;
  if (inRate<5400) return 2;
  if (inRate<5900) return 3;
  if (inRate<6650) return 4;
  if (inRate<7450) return 5;
  if (inRate<8100) return 6;
  if (inRate<8800) return 7;
  if (inRate<10200) return 8;
  if (inRate<11700) return 9;
  if (inRate<13300) return 10;
  if (inRate<15900) return 11;
  if (inRate<18900) return 12;
  if (inRate<23500) return 13;
  if (inRate<29000) return 14;
  return 15;
}

void DivPlatform5E01::tick(bool sysTick) {
  for (int i=0; i<4; i++) {
    chan[i].std.next();
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->had) {
      // ok, why are the volumes like that?
      chan[i].outVol=VOL_SCALE_LINEAR_BROKEN(chan[i].vol&15,MIN(15,chan[i].std.get_div_macro_struct(DIV_MACRO_VOL)->val),15);
      if (chan[i].outVol<0) chan[i].outVol=0;
      if (i==2) { // triangle
        rWrite(0x4100+i*4,(chan[i].outVol==0)?0:linearCount);
        chan[i].freqChanged=true;
      } else {
        rWrite(0x4100+i*4,(chan[i].envMode<<4)|chan[i].outVol|((chan[i].duty&3)<<6));
      }
    }
    if (NEW_ARP_STRAT) {
      chan[i].handleArp();
    } else if (chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->had) {
      if (i==3) { // noise
        chan[i].baseFreq=parent->calcArp(chan[i].note,chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val);
        if (chan[i].baseFreq>255) chan[i].baseFreq=255;
        if (chan[i].baseFreq<0) chan[i].baseFreq=0;
      } else {
        if (!chan[i].inPorta) {
          chan[i].baseFreq=NOTE_PERIODIC(parent->calcArp(chan[i].note,chan[i].std.get_div_macro_struct(DIV_MACRO_ARP)->val));
        }
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->had) {
      chan[i].duty=chan[i].std.get_div_macro_struct(DIV_MACRO_DUTY)->val;
      if (i==3) {
        if (parent->song.properNoiseLayout) {
          chan[i].duty&=1;
        } else if (chan[i].duty>1) {
          chan[i].duty=1;
        }
      }
      if (i!=2) {
        rWrite(0x4100+i*4,(chan[i].envMode<<4)|chan[i].outVol|((chan[i].duty&3)<<6));
      }
      if(i == 2) //triangle/wave channel
      {
        rWrite(0x4109,chan[i].duty&3);
      }
      if (i==3) { // noise
        chan[i].freqChanged=true;
      }
    }
    if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->had) {
      if (chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->mode) {
        chan[i].pitch2+=chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
        CLAMP_VAR(chan[i].pitch2,-32768,32767);
      } else {
        chan[i].pitch2=chan[i].std.get_div_macro_struct(DIV_MACRO_PITCH)->val;
      }
      chan[i].freqChanged=true;
    }
    if (chan[i].sweepChanged) {
      chan[i].sweepChanged=false;
      if (i==0) {
        //rWrite(16+i*5,chan[i].sweep);
      }
    }
    if (i<3) if (chan[i].std.get_div_macro_struct(DIV_MACRO_PHASE_RESET)->had) {
      if (chan[i].std.get_div_macro_struct(DIV_MACRO_PHASE_RESET)->val==1) {
        chan[i].freqChanged=true;
        chan[i].prevFreq=-1;
      }
    }
    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) {
      if (i==3) { // noise
        int ntPos=chan[i].baseFreq;
        if (NEW_ARP_STRAT) {
          if (chan[i].fixedArp) {
            ntPos=chan[i].baseNoteOverride;
          } else {
            ntPos+=chan[i].arpOff;
          }
        }
        ntPos+=chan[i].pitch2;
        if (parent->song.properNoiseLayout) {
          chan[i].freq=31-(ntPos&31);
        } else {
          if (ntPos<0) ntPos=0;
          if (ntPos>252) ntPos=252;
          chan[i].freq=noiseTable[ntPos];
        }
      } else {
        if (chan[i].keyOn) 
        {
          if(i < 2)
          {
            if(parent->song.resetNesSweep && !(chan[i].do_sweep)) //so if sweep effect is on the same row with new note it actually works ig
            {
              chan[i].sweep=0x08;
              rWrite(0x4101+(i*4),chan[i].sweep);
            }
          }
        }
        
        chan[i].freq=parent->calcFreq(chan[i].baseFreq,chan[i].pitch,chan[i].fixedArp?chan[i].baseNoteOverride:chan[i].arpOff,chan[i].fixedArp,true,0,chan[i].pitch2,chipClock,CHIP_DIVIDER)-1;
        if (chan[i].freq>2047) chan[i].freq=2047;
        if (chan[i].freq<0) chan[i].freq=0;
      }
      if (chan[i].keyOn) 
      {}
      if (chan[i].keyOff) {
        //rWrite(16+i*5+2,8);
        if (i==2) { // triangle
          rWrite(0x4100+i*4,0x00);
        } else {
          rWrite(0x4100+i*4,0x30);
        }
      }
      if (i==3) { // noise
        rWrite(0x4102+i*4,(chan[i].duty<<7)|chan[i].freq);
        rWrite(0x4103+i*4,(chan[i].len<<3));
      } else {
        rWrite(0x4102+i*4,chan[i].freq&0xff);
        if ((chan[i].prevFreq>>8)!=(chan[i].freq>>8) || i==2 || (parent->song.resetNesSweep && i < 2 && chan[i].keyOn)) {
          rWrite(0x4103+i*4,(chan[i].len<<3)|(chan[i].freq>>8));
        }
        if (chan[i].freq!=65535 && chan[i].freq!=0) {
          chan[i].prevFreq=chan[i].freq;
        }
      }
      if (chan[i].keyOn) chan[i].keyOn=false;
      if (chan[i].keyOff) chan[i].keyOff=false;
      chan[i].freqChanged=false;
    }

    chan[i].do_sweep = false;
  }

  // PCM
  if (chan[4].freqChanged || chan[4].keyOn) {
    chan[4].freq=parent->calcFreq(chan[4].baseFreq,chan[4].pitch,chan[4].fixedArp?chan[4].baseNoteOverride:chan[4].arpOff,chan[4].fixedArp,false);
    if (chan[4].furnaceDac) {
      double off=1.0;
      if (dacSample>=0 && dacSample<parent->song.sampleLen) {
        DivSample* s=parent->getSample(dacSample);
        off=(double)s->centerRate/8363.0;
      }
      dacRate=MIN(chan[4].freq*off,32000);
      if (chan[4].keyOn) {
        if (dpcmMode && !skipRegisterWrites && dacSample>=0 && dacSample<parent->song.sampleLen) {
          unsigned int dpcmAddr=sampleOffDPCM[dacSample];
          unsigned int dpcmLen=parent->getSample(dacSample)->lengthDPCM>>4;
          if (dpcmLen>255) dpcmLen=255;
          goingToLoop=parent->getSample(dacSample)->isLoopable();

          DivInstrument* ins = parent->getIns(chan[4].ins, DIV_INS_NES);
          if (ins->amiga.useNoteMap)
          {
            if(ins->type==DIV_INS_NES && !parent->song.oldDPCM)
            {
              goingToLoop=ins->amiga.getFreq(chan[4].note) ? true : parent->getSample(dacSample)->isLoopable();
            }
          }
          // write DPCM
          rWrite(0x4115,15);
          if (nextDPCMFreq>=0) {
            rWrite(0x4110,nextDPCMFreq|(goingToLoop?0x41:0));
            nextDPCMFreq=-1;
          } else {
            rWrite(0x4110,calcDPCMRate(dacRate)|(goingToLoop?0x41:0));
          }
          if (nextDPCMDelta>=0) {
            rWrite(0x4111,nextDPCMDelta);
            nextDPCMDelta=-1;
          }
          rWrite(0x4112,(dpcmAddr>>6)&0xff);
          rWrite(0x4113,dpcmLen&0xff);
          rWrite(0x4115,31);
          if (dpcmBank!=(dpcmAddr>>14)) {
            dpcmBank=dpcmAddr>>14;
            logV("switching bank to %d",dpcmBank);
            if (dumpWrites) addWrite(0xffff0004,dpcmBank);
          }
        }
      } else {
        if (nextDPCMFreq>=0) {
          rWrite(0x4110,nextDPCMFreq|(goingToLoop?0x41:0));
          nextDPCMFreq=-1;
        } else {
          rWrite(0x4110,calcDPCMRate(dacRate)|(goingToLoop?0x41:0));
        }
      }
      if (dumpWrites && !dpcmMode) addWrite(0xffff0001,dacRate);
    }
    if (chan[4].keyOn) chan[4].keyOn=false;
    chan[4].freqChanged=false;
  }

  nextDPCMFreq=-1;
}

int DivPlatform5E01::dispatch(DivCommand c) {
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON:
      chan[c.chan].note = c.value;
      if (c.chan==4) { // PCM
        DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_NES);
        if (ins->type==DIV_INS_AMIGA || (ins->type==DIV_INS_NES && !parent->song.oldDPCM)) {
          if (ins->type==DIV_INS_NES) {
            if (!dpcmMode) {
              dpcmMode=true;
              if (dumpWrites) addWrite(0xffff0002,0);
              dacSample=-1;
              rWrite(0x4115,15);
              rWrite(0x4110,0);
              rWrite(0x4112,0);
              rWrite(0x4113,0);
              rWrite(0x4115,31);
            }

            if (ins->amiga.useNoteMap) {
              nextDPCMFreq=ins->amiga.getDPCMFreq(c.value);
              if (nextDPCMFreq<0 || nextDPCMFreq>15) nextDPCMFreq=lastDPCMFreq;
              lastDPCMFreq=nextDPCMFreq;
              nextDPCMDelta=ins->amiga.getDPCMDelta(c.value);

              if(ins->type==DIV_INS_NES && !parent->song.oldDPCM)
              {
                goingToLoop=ins->amiga.getFreq(c.value) ? true : false;
              }
            } else {
              if (c.value==DIV_NOTE_NULL) {
                nextDPCMFreq=lastDPCMFreq;
              } else {
                nextDPCMFreq=c.value&15;
              }
            }
          }
          if (c.value!=DIV_NOTE_NULL) {
            dacSample=ins->amiga.getSample(c.value);
            if (ins->type==DIV_INS_AMIGA) {
              chan[c.chan].sampleNote=c.value;
              c.value=ins->amiga.getFreq(c.value);
              chan[c.chan].sampleNoteDelta=c.value-chan[c.chan].sampleNote;
            }
          } else if (chan[c.chan].sampleNote!=DIV_NOTE_NULL) {
            dacSample=ins->amiga.getSample(chan[c.chan].sampleNote);
            if (ins->type==DIV_INS_AMIGA) {
              c.value=ins->amiga.getFreq(chan[c.chan].sampleNote);
            }
          }
          if (dacSample<0 || dacSample>=parent->song.sampleLen) {
            dacSample=-1;
            if (dumpWrites && !dpcmMode) addWrite(0xffff0002,0);
            break;
          } else {
            if (dumpWrites && !dpcmMode) addWrite(0xffff0000,dacSample);
          }
          dacPos=0;
          dacPeriod=0;
          if (c.value!=DIV_NOTE_NULL) {
            chan[c.chan].baseFreq=parent->calcBaseFreq(1,1,c.value,false);
            chan[c.chan].freqChanged=true;
            chan[c.chan].note=c.value;
          }
          chan[c.chan].active=true;
          chan[c.chan].keyOn=true;
          chan[c.chan].furnaceDac=true;
        } else {
          if (c.value!=DIV_NOTE_NULL) {
            chan[c.chan].note=c.value;
          }
          dacSample=12*sampleBank+chan[c.chan].note%12;
          if (dacSample>=parent->song.sampleLen) {
            dacSample=-1;
            if (dumpWrites && !dpcmMode) addWrite(0xffff0002,0);
            break;
          } else {
            if (dumpWrites && !dpcmMode) addWrite(0xffff0000,dacSample);
          }
          dacPos=0;
          dacPeriod=0;
          dacRate=parent->getSample(dacSample)->rate;
          if (dumpWrites && !dpcmMode) addWrite(0xffff0001,dacRate);
          chan[c.chan].furnaceDac=false;
          if (dpcmMode && !skipRegisterWrites) {
            unsigned int dpcmAddr=sampleOffDPCM[dacSample];
            unsigned int dpcmLen=parent->getSample(dacSample)->lengthDPCM>>4;
            if (dpcmLen>255) dpcmLen=255;
            goingToLoop=parent->getSample(dacSample)->isLoopable();
            // write DPCM
            rWrite(0x4115,15);
            if (nextDPCMFreq>=0) {
              rWrite(0x4110,nextDPCMFreq|(goingToLoop?0x41:0));
              nextDPCMFreq=-1;
            } else {
              rWrite(0x4110,calcDPCMRate(dacRate)|(goingToLoop?0x41:0));
            }
            rWrite(0x4112,(dpcmAddr>>6)&0xff);
            rWrite(0x4113,dpcmLen&0xff);
            rWrite(0x4115,31);
            if (dpcmBank!=(dpcmAddr>>14)) {
              dpcmBank=dpcmAddr>>14;
              logV("switching bank to %d",dpcmBank);
              if (dumpWrites) addWrite(0xffff0004,dpcmBank);
            }
          }
        }
        break;
      } else if (c.chan==3) { // noise
        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].baseFreq=c.value;
        }
      } else {
        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].baseFreq=NOTE_PERIODIC(c.value);
        }
      }
      if (c.value!=DIV_NOTE_NULL) {
        chan[c.chan].freqChanged=true;
        chan[c.chan].note=c.value;
      }
      chan[c.chan].active=true;
      chan[c.chan].keyOn=true;
      chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_NES));
      if (!parent->song.brokenOutVol && !chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->will) {
        chan[c.chan].outVol=chan[c.chan].vol;
      }
      if (c.chan==2) {
        rWrite(0x4100+c.chan*4,linearCount);
      } else if (!parent->song.brokenOutVol2) {
        rWrite(0x4100+c.chan*4,(chan[c.chan].envMode<<4)|chan[c.chan].vol|((chan[c.chan].duty&3)<<6));
      }
      break;
    case DIV_CMD_NOTE_OFF:
      if (c.chan==4) {
        dacSample=-1;
        if (dumpWrites) addWrite(0xffff0002,0);
        if (dpcmMode && !skipRegisterWrites) rWrite(0x4115,15);
      }
      chan[c.chan].active=false;
      chan[c.chan].keyOff=true;
      chan[c.chan].macroInit(NULL);
      break;
    case DIV_CMD_NOTE_OFF_ENV:
    case DIV_CMD_ENV_RELEASE:
      chan[c.chan].std.release();
      break;
    case DIV_CMD_INSTRUMENT:
      if (chan[c.chan].ins!=c.value || c.value2==1) {
        chan[c.chan].ins=c.value;
      }
      break;
    case DIV_CMD_VOLUME:
      if (chan[c.chan].vol!=c.value) {
        chan[c.chan].vol=c.value;
        if (!chan[c.chan].std.get_div_macro_struct(DIV_MACRO_VOL)->has) {
          chan[c.chan].outVol=c.value;
        }
        if (chan[c.chan].active) {
          if (c.chan==2) {
            rWrite(0x4100+c.chan*4,linearCount);
          } else {
            rWrite(0x4100+c.chan*4,(chan[c.chan].envMode<<4)|chan[c.chan].vol|((chan[c.chan].duty&3)<<6));
          }
        }
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
      int destFreq=(c.chan==4)?(parent->calcBaseFreq(1,1,c.value2+chan[c.chan].sampleNoteDelta,false)):(NOTE_PERIODIC(c.value2));
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
      chan[c.chan].duty=c.value;
      if (c.chan==3) { // noise
        chan[c.chan].freqChanged=true;
      }
      if(c.chan == 2) //triangle/wave
      {
        rWrite(0x4109, chan[c.chan].duty&3);
      }
      else if (c.chan<2) {
        rWrite(0x4100+c.chan*4,(chan[c.chan].active?((chan[c.chan].envMode<<4)|chan[c.chan].outVol):0x30)|((chan[c.chan].duty&3)<<6));
      }
      break;
    case DIV_CMD_NES_SWEEP:
      if (c.chan>1) break;
      if (c.value2==0) {
        chan[c.chan].sweep=0x08;
      } else {
        if (!c.value) { // down
          chan[c.chan].sweep=0x88|(c.value2&0x77);
        } else { // up
          chan[c.chan].sweep=0x80|(c.value2&0x77);
        }
        chan[c.chan].do_sweep = true;
      }
      rWrite(0x4101+(c.chan*4),chan[c.chan].sweep);
      break;
    case DIV_CMD_NES_ENV_MODE:
      chan[c.chan].envMode=c.value&3;
      if (c.chan==3) { // noise
        chan[c.chan].freqChanged=true;
      } else if (c.chan<2) {
        rWrite(0x4100+c.chan*4,(chan[c.chan].active?((chan[c.chan].envMode<<4)|chan[c.chan].outVol):0x30)|((chan[c.chan].duty&3)<<6));
      }
      break;
    case DIV_CMD_NES_LENGTH:
      if (c.chan>=4) break;
      chan[c.chan].len=c.value&0x1f;
      chan[c.chan].freqChanged=true;
      chan[c.chan].prevFreq=-1;
      break;
    case DIV_CMD_NES_COUNT_MODE:
      countMode=c.value;
      rWrite(0x4117,countMode?0x80:0);
      break;
    case DIV_CMD_NES_LINEAR_LENGTH:
      if (c.chan==2) {
        linearCount=c.value;
        if (chan[c.chan].active) {
          rWrite(0x4100+c.chan*4,(chan[c.chan].outVol==0)?0:linearCount);
          chan[c.chan].freqChanged=true;
          chan[c.chan].prevFreq=-1;
        }
      }
      break;
    case DIV_CMD_NES_DMC:
      rWrite(0x4111,c.value&0x7f);
      break;
    case DIV_CMD_SAMPLE_MODE:
      dpcmMode=c.value;
      if (dumpWrites && dpcmMode) addWrite(0xffff0002,0);
      dacSample=-1;
      rWrite(0x4115,15);
      rWrite(0x4110,0);
      rWrite(0x4112,0);
      rWrite(0x4113,0);
      rWrite(0x4115,31);
      break;
    case DIV_CMD_SAMPLE_FREQ: {
      bool goingToLoop=parent->getSample(dacSample)->isLoopable();
      DivInstrument* ins = parent->getIns(chan[4].ins, DIV_INS_NES);
      if (ins->amiga.useNoteMap)
      {
        if(ins->type==DIV_INS_NES && !parent->song.oldDPCM)
        {
          goingToLoop=ins->amiga.getFreq(chan[4].note) ? true : false;
        }
      }
      if (dpcmMode) {
        nextDPCMFreq=c.value&15;
        rWrite(0x4110,(c.value&15)|(goingToLoop?0x41:0));
      }
      break;
    }
    case DIV_CMD_SAMPLE_BANK:
      sampleBank=c.value;
      if (sampleBank>(parent->song.sample.size()/12)) {
        sampleBank=parent->song.sample.size()/12;
      }
      break;
    case DIV_CMD_LEGATO:
      if (c.chan==3) break;
      if (c.chan==4) {
        chan[c.chan].baseFreq=parent->calcBaseFreq(1,1,c.value+chan[c.chan].sampleNoteDelta+((HACKY_LEGATO_MESS)?(chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->val):(0)),false);
      } else {
        chan[c.chan].baseFreq=NOTE_PERIODIC(c.value+((HACKY_LEGATO_MESS)?(chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->val):(0)));
      }
      chan[c.chan].freqChanged=true;
      chan[c.chan].note=c.value;
      break;
    case DIV_CMD_PRE_PORTA:
      if (chan[c.chan].active && c.value2) {
        if (parent->song.resetMacroOnPorta) chan[c.chan].macroInit(parent->getIns(chan[c.chan].ins,DIV_INS_NES));
      }
      if (!chan[c.chan].inPorta && c.value && !parent->song.brokenPortaArp && chan[c.chan].std.get_div_macro_struct(DIV_MACRO_ARP)->will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=NOTE_PERIODIC(chan[c.chan].note);
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_GET_VOLMAX:
      return 15;
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

void DivPlatform5E01::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
  nes1_NP->SetMask(((int)isMuted[0])|(isMuted[1]<<1));
  nes2_NP->SetMask(((int)isMuted[2])|(isMuted[3]<<1)|(isMuted[4]<<2));
}

void DivPlatform5E01::forceIns() {
  for (int i=0; i<5; i++) {
    chan[i].insChanged=true;
    chan[i].prevFreq=65535;
  }
  rWrite(0x4101,chan[0].sweep);
  rWrite(0x4105,chan[1].sweep);
  rWrite(0x4117,countMode?0x80:0);
}

void* DivPlatform5E01::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatform5E01::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivDispatchOscBuffer* DivPlatform5E01::getOscBuffer(int ch) {
  return oscBuf[ch];
}

unsigned char* DivPlatform5E01::getRegisterPool() {
  return regPool;
}

int DivPlatform5E01::getRegisterPoolSize() {
  return 32;
}

float DivPlatform5E01::getPostAmp() {
  return 2.0f;
}

void DivPlatform5E01::reset() {
  for (int i=0; i<5; i++) {
    chan[i]=DivPlatform5E01::Channel();
    chan[i].std.setEngine(parent);

    chan[i].do_sweep = false;
  }
  if (dumpWrites) {
    addWrite(0xffffffff,0);
  }

  dacPeriod=0;
  dacPos=0;
  dacRate=0;
  dacSample=-1;
  sampleBank=0;
  dpcmBank=0;
  dpcmMode=dpcmModeDefault;
  goingToLoop=false;
  countMode=false;
  nextDPCMFreq=-1;
  nextDPCMDelta=-1;
  lastDPCMFreq=15;
  linearCount=255;

  nes1_NP->Reset();
  nes2_NP->Reset();
  nes1_NP->SetMask(((int)isMuted[0])|(isMuted[1]<<1));
  nes2_NP->SetMask(((int)isMuted[2])|(isMuted[3]<<1)|(isMuted[4]<<2));

  memset(regPool,0,128);

  rWrite(0x4115,0x1f);
  rWrite(0x4101,chan[0].sweep);
  rWrite(0x4105,chan[1].sweep);

  dacAntiClickOn=true;
  dacAntiClick=0;
}

bool DivPlatform5E01::keyOffAffectsArp(int ch) {
  return true;
}

void DivPlatform5E01::setFlags(const DivConfig& flags) {
  int clockSel=flags.getInt("clockSel",0);
  if (clockSel==2) { // Dendy
    chipClock=COLOR_PAL*2.0/5.0;
    apuType=2;
  } else if (clockSel==1) { // PAL
    chipClock=COLOR_PAL*3.0/8.0;
    apuType=1;
  } else { // NTSC
    chipClock=COLOR_NTSC/2.0;
    apuType=0;
  }
  nes1_NP->SetClock(rate);
  nes1_NP->SetRate(rate);
  nes2_NP->SetClock(rate);
  nes2_NP->SetRate(rate);
  nes2_NP->SetPal(apuType==1);

  CHECK_CUSTOM_CLOCK;
  rate=chipClock;
  rate/=8;
  for (int i=0; i<5; i++) {
    oscBuf[i]->rate=rate/(4);
  }
  
  dpcmModeDefault=flags.getBool("dpcmMode",true);
}

void DivPlatform5E01::notifyInsDeletion(void* ins) {
  for (int i=0; i<5; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void DivPlatform5E01::poke(unsigned int addr, unsigned short val) {
  rWrite(addr,val);
}

void DivPlatform5E01::poke(std::vector<DivRegWrite>& wlist) {
  for (DivRegWrite& i: wlist) rWrite(i.addr,i.val);
}

unsigned char DivPlatform5E01::readDMC(unsigned short addr) {
  return dpcmMem[(addr&0x3fff)|((dpcmBank&15)<<14)];
}

const void* DivPlatform5E01::getSampleMem(int index) {
  return index==0?dpcmMem:NULL;
}

size_t DivPlatform5E01::getSampleMemCapacity(int index) {
  return index==0?262144:0;
}

size_t DivPlatform5E01::getSampleMemUsage(int index) {
  return index==0?dpcmMemLen:0;
}

bool DivPlatform5E01::isSampleLoaded(int index, int sample) {
  if (index!=0) return false;
  if (sample<0 || sample>255) return false;
  return sampleLoaded[sample];
}

const DivMemoryComposition* DivPlatform5E01::getMemCompo(int index) {
  if (index!=0) return NULL;
  return &memCompo;
}

void DivPlatform5E01::renderSamples(int sysID) {
  memset(dpcmMem,0,getSampleMemCapacity(0));
  memset(sampleLoaded,0,256*sizeof(bool));

  memCompo=DivMemoryComposition();
  memCompo.name=_LE("DPCM");

  size_t memPos=0;
  for (int i=0; i<parent->song.sampleLen; i++) {
    DivSample* s=parent->song.sample[i];
    if (!s->renderOn[0][sysID]) {
      sampleOffDPCM[i]=0;
      continue;
    }

    unsigned int paddedLen=(s->lengthDPCM+63)&(~0x3f);
    logV("%d padded length: %d",i,paddedLen);
    if ((memPos&(~0x3fff))!=((memPos+paddedLen)&(~0x3fff))) {
      memPos=(memPos+0x3fff)&(~0x3fff);
    }
    if (paddedLen>4081) {
      paddedLen=4096;
    }
    if (memPos>=getSampleMemCapacity(0)) {
      logW("out of DPCM memory for sample %d!",i);
      break;
    }
    if (memPos+paddedLen>=getSampleMemCapacity(0)) {
      memcpy(dpcmMem+memPos,s->dataDPCM,getSampleMemCapacity(0)-memPos);
      logW("out of DPCM memory for sample %d!",i);
    } else {
      memcpy(dpcmMem+memPos,s->dataDPCM,MIN(s->lengthDPCM,paddedLen));
      sampleLoaded[i]=true;
    }
    sampleOffDPCM[i]=memPos;
    memCompo.entries.push_back(DivMemoryEntry(DIV_MEMORY_SAMPLE,_LE("Sample"),i,memPos,memPos+paddedLen));
    memPos+=paddedLen;
  }
  dpcmMemLen=memPos;

  memCompo.capacity=262144;
  memCompo.used=dpcmMemLen;
}

int DivPlatform5E01::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;

  nes1_NP=new xgm::I5E01_APU;
  nes1_NP->SetOption(xgm::I5E01_APU::OPT_NONLINEAR_MIXER,1);
  nes2_NP=new xgm::I5E01_DMC;
  nes2_NP->SetOption(xgm::I5E01_DMC::OPT_NONLINEAR_MIXER,1);
  nes2_NP->SetMemory([this](unsigned short addr, unsigned int& data) {
    data=readDMC(addr);
  });
  nes2_NP->SetAPU(nes1_NP);

  writeOscBuf=0;
  for (int i=0; i<5; i++) {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }
  setFlags(flags);

  dpcmMem=new unsigned char[262144];
  dpcmMemLen=0;
  dpcmBank=0;
  if (dumpWrites) addWrite(0xffff0004,dpcmBank);

  reset();
  return 5;
}

void DivPlatform5E01::quit() {
  for (int i=0; i<5; i++) {
    delete oscBuf[i];
  }
  delete nes1_NP;
  delete nes2_NP;
}

DivPlatform5E01::~DivPlatform5E01() {
}
