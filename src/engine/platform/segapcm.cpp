/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2023 tildearrow and contributors
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

#include "segapcm.h"
#include "../engine.h"
#include "../../ta-log.h"
#include <string.h>
#include <math.h>

#define rWrite(a,v) if (!skipRegisterWrites) {writes.emplace(a,v); if (dumpWrites) {addWrite(a,v);} }
#define chWrite(c,a,v) rWrite(((c)<<3)+(a),v)

void DivPlatformSegaPCM::acquire(short** buf, size_t len) {
  static int os[2];

  for (size_t h=0; h<len; h++) {
    while (!writes.empty()) {
      QueuedWrite w=writes.front();
      pcm.write(w.addr,w.val);
      regPool[w.addr&0xff]=w.val;
      writes.pop();
    }

    pcm.sound_stream_update(os);

    if (os[0]<-32768) os[0]=-32768;
    if (os[0]>32767) os[0]=32767;

    if (os[1]<-32768) os[1]=-32768;
    if (os[1]>32767) os[1]=32767;
  
    buf[0][h]=os[0];
    buf[1][h]=os[1];
  }
}

void DivPlatformSegaPCM::tick(bool sysTick) {
  for (int i=0; i<16; i++) {
    chan[i].std.next();

    if (parent->song.newSegaPCM) {
      if (chan[i].std.vol.had) {
        chan[i].outVol=(chan[i].vol*MIN(chan[i].macroVolMul,chan[i].std.vol.val))/chan[i].macroVolMul;
        chan[i].chVolL=(chan[i].outVol*chan[i].chPanL)/127;
        chan[i].chVolR=(chan[i].outVol*chan[i].chPanR)/127;
        rWrite(2+(i<<3),chan[i].chVolL);
        rWrite(3+(i<<3),chan[i].chVolR);
      }
    }

    if (NEW_ARP_STRAT) {
      chan[i].handleArp();
    } else if (chan[i].std.arp.had) {
      if (!chan[i].inPorta) {
        chan[i].baseFreq=(parent->calcArp(chan[i].note,chan[i].std.arp.val)<<6);
      }
      chan[i].freqChanged=true;
    }

    if (parent->song.newSegaPCM) if (chan[i].std.panL.had) {
      chan[i].chPanL=chan[i].std.panL.val&127;
      chan[i].chVolL=(chan[i].outVol*chan[i].chPanL)/127;
      rWrite(2+(i<<3),chan[i].chVolL);
    }

    if (parent->song.newSegaPCM) if (chan[i].std.panR.had) {
      chan[i].chPanR=chan[i].std.panR.val&127;
      chan[i].chVolR=(chan[i].outVol*chan[i].chPanR)/127;
      rWrite(3+(i<<3),chan[i].chVolR);
    }
    
    if (chan[i].std.pitch.had) {
      if (chan[i].std.pitch.mode) {
        chan[i].pitch2+=chan[i].std.pitch.val;
        CLAMP_VAR(chan[i].pitch2,-32768,32767);
      } else {
        chan[i].pitch2=chan[i].std.pitch.val;
      }
      chan[i].freqChanged=true;
    }

    if (chan[i].std.phaseReset.had) {
      if (chan[i].std.phaseReset.val==1 && chan[i].active) {
        chan[i].keyOn=true;
      }
    }

    if (chan[i].freqChanged || chan[i].keyOn || chan[i].keyOff) {
      chan[i].freq=chan[i].baseFreq+(chan[i].pitch>>1)-64;
      if (!parent->song.oldArpStrategy) {
        if (chan[i].fixedArp) {
          chan[i].freq=(chan[i].baseNoteOverride<<6)+(chan[i].pitch>>1)-64+chan[i].pitch2;
        } else {
          chan[i].freq+=chan[i].arpOff<<6;
        }
      }
      if (chan[i].furnacePCM) {
        double off=1.0;
        if (chan[i].pcm.sample>=0 && chan[i].pcm.sample<parent->song.sampleLen) {
          DivSample* s=parent->getSample(chan[i].pcm.sample);
          off=(double)s->centerRate/8363.0;
        }
        chan[i].pcm.freq=MIN(255,(15625+(off*parent->song.tuning*pow(2.0,double(chan[i].freq+256)/(64.0*12.0)))*255)/31250)+chan[i].pitch2;
        rWrite(7+(i<<3),chan[i].pcm.freq);
      }
      chan[i].freqChanged=false;
      if (chan[i].keyOn || chan[i].keyOff) {
        if (chan[i].keyOn && !chan[i].keyOff) {
          rWrite(0x86+(i<<3),3);
          chan[i].pcm.pos=0;
          if (chan[i].furnacePCM) {
            DivSample* s=parent->getSample(chan[i].pcm.sample);
            int loopStart=s->getLoopStartPosition(DIV_SAMPLE_DEPTH_8BIT);
            int actualLength=(s->getLoopEndPosition(DIV_SAMPLE_DEPTH_8BIT));
            if (actualLength>0xfeff) actualLength=0xfeff;
            rWrite(0x86+(i<<3),3+((sampleOffSegaPCM[chan[i].pcm.sample]>>16)<<3));
            rWrite(0x84+(i<<3),(sampleOffSegaPCM[chan[i].pcm.sample])&0xff);
            rWrite(0x85+(i<<3),(sampleOffSegaPCM[chan[i].pcm.sample]>>8)&0xff);
            rWrite(6+(i<<3),MIN(255,((sampleOffSegaPCM[chan[i].pcm.sample]&0xffff)+actualLength-1)>>8));
            if (loopStart<0 || loopStart>=actualLength) {
              rWrite(0x86+(i<<3),2+((sampleOffSegaPCM[chan[i].pcm.sample]>>16)<<3));
            } else {
              int loopPos=(sampleOffSegaPCM[chan[i].pcm.sample]&0xffff)+loopStart+sampleLoopOff[chan[i].pcm.sample];
              rWrite(4+(i<<3),loopPos&0xff);
              rWrite(5+(i<<3),(loopPos>>8)&0xff);
              rWrite(0x86+(i<<3),((sampleOffSegaPCM[chan[i].pcm.sample]>>16)<<3));
            }
          } else {
            DivSample* s=parent->getSample(chan[i].pcm.sample);
            int loopStart=s->getLoopStartPosition(DIV_SAMPLE_DEPTH_8BIT);
            int actualLength=(s->getLoopEndPosition(DIV_SAMPLE_DEPTH_8BIT));
            if (actualLength>0xfeff) actualLength=0xfeff;
            rWrite(0x86+(i<<3),3+((sampleOffSegaPCM[chan[i].pcm.sample]>>16)<<3));
            rWrite(0x84+(i<<3),(sampleOffSegaPCM[chan[i].pcm.sample])&0xff);
            rWrite(0x85+(i<<3),(sampleOffSegaPCM[chan[i].pcm.sample]>>8)&0xff);
            rWrite(6+(i<<3),MIN(255,((sampleOffSegaPCM[chan[i].pcm.sample]&0xffff)+actualLength-1)>>8));
            if (loopStart<0 || loopStart>=actualLength) {
              rWrite(0x86+(i<<3),2+((sampleOffSegaPCM[chan[i].pcm.sample]>>16)<<3));
            } else {
              int loopPos=(sampleOffSegaPCM[chan[i].pcm.sample]&0xffff)+loopStart+sampleLoopOff[chan[i].pcm.sample];
              rWrite(4+(i<<3),loopPos&0xff);
              rWrite(5+(i<<3),(loopPos>>8)&0xff);
              rWrite(0x86+(i<<3),((sampleOffSegaPCM[chan[i].pcm.sample]>>16)<<3));
            }
            rWrite(7+(i<<3),chan[i].pcm.freq);
          }
        }
        chan[i].keyOn=false;
        chan[i].keyOff=false;
      }
    }
  }
}

void DivPlatformSegaPCM::muteChannel(int ch, bool mute) {
  isMuted[ch]=mute;
  pcm.mute(ch,mute);
}

int DivPlatformSegaPCM::dispatch(DivCommand c) {
  switch (c.cmd) {
    case DIV_CMD_NOTE_ON: {
      DivInstrument* ins=parent->getIns(chan[c.chan].ins,DIV_INS_AMIGA);
      if (skipRegisterWrites) break;
      if (ins->type==DIV_INS_AMIGA || ins->type==DIV_INS_SEGAPCM) {
        chan[c.chan].macroVolMul=(ins->type==DIV_INS_AMIGA)?64:127;
        chan[c.chan].isNewSegaPCM=(ins->type==DIV_INS_SEGAPCM);
        if (c.value!=DIV_NOTE_NULL) chan[c.chan].pcm.sample=ins->amiga.getSample(c.value);
        if (chan[c.chan].pcm.sample<0 || chan[c.chan].pcm.sample>=parent->song.sampleLen) {
          chan[c.chan].pcm.sample=-1;
          rWrite(0x86+(c.chan<<3),3);
          chan[c.chan].macroInit(NULL);
          if (!parent->song.brokenOutVol && !chan[c.chan].std.vol.will) {
            chan[c.chan].outVol=chan[c.chan].vol;
          }
          break;
        }
        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].note=c.value;
          chan[c.chan].baseFreq=(c.value<<6);
          chan[c.chan].freqChanged=true;
        }
        chan[c.chan].furnacePCM=true;
        chan[c.chan].macroInit(ins);
        chan[c.chan].active=true;
        chan[c.chan].keyOn=true;
      } else {
        chan[c.chan].macroInit(NULL);
        if (c.value!=DIV_NOTE_NULL) {
          chan[c.chan].note=c.value;
        }
        chan[c.chan].pcm.sample=12*sampleBank+chan[c.chan].note%12;
        if (chan[c.chan].pcm.sample>=parent->song.sampleLen) {
          chan[c.chan].pcm.sample=-1;
          rWrite(0x86+(c.chan<<3),3);
          break;
        }
        chan[c.chan].pcm.freq=MIN(255,(parent->getSample(chan[c.chan].pcm.sample)->rate*255)/31250);
        chan[c.chan].furnacePCM=false;
        chan[c.chan].active=true;
        chan[c.chan].keyOn=true;
      }
      break;
    }
    case DIV_CMD_NOTE_OFF:
      chan[c.chan].pcm.sample=-1;
      rWrite(0x86+(c.chan<<3),3);
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].active=false;
      chan[c.chan].macroInit(NULL);
      break;
    case DIV_CMD_NOTE_OFF_ENV:
      chan[c.chan].keyOff=true;
      chan[c.chan].keyOn=false;
      chan[c.chan].active=false;
      chan[c.chan].std.release();
      break;
    case DIV_CMD_ENV_RELEASE:
      chan[c.chan].std.release();
      break;
    case DIV_CMD_VOLUME: {
      chan[c.chan].vol=c.value;
      if (!chan[c.chan].std.vol.has) {
        chan[c.chan].outVol=c.value;
      }
      if (parent->song.newSegaPCM) {
        chan[c.chan].chVolL=(c.value*chan[c.chan].chPanL)/127;
        chan[c.chan].chVolR=(c.value*chan[c.chan].chPanR)/127;
      } else {
        chan[c.chan].chVolL=c.value;
        chan[c.chan].chVolR=c.value;
      }
      rWrite(2+(c.chan<<3),chan[c.chan].chVolL);
      rWrite(3+(c.chan<<3),chan[c.chan].chVolR);
      break;
    }
    case DIV_CMD_GET_VOLUME: {
      return chan[c.chan].vol;
      break;
    }
    case DIV_CMD_INSTRUMENT:
      if (chan[c.chan].ins!=c.value || c.value2==1) {
        chan[c.chan].insChanged=true;
      }
      chan[c.chan].ins=c.value;
      break;
    case DIV_CMD_PANNING: {
      if (parent->song.newSegaPCM) {
        chan[c.chan].chPanL=c.value>>1;
        chan[c.chan].chPanR=c.value2>>1;
        chan[c.chan].chVolL=(chan[c.chan].outVol*chan[c.chan].chPanL)/127;
        chan[c.chan].chVolR=(chan[c.chan].outVol*chan[c.chan].chPanR)/127;
      } else {
        chan[c.chan].chVolL=c.value>>1;
        chan[c.chan].chVolR=c.value2>>1;
      }
      rWrite(2+(c.chan<<3),chan[c.chan].chVolL);
      rWrite(3+(c.chan<<3),chan[c.chan].chVolR);
      break;
    }
    case DIV_CMD_PITCH: {
      chan[c.chan].pitch=c.value;
      chan[c.chan].freqChanged=true;
      break;
    }
    case DIV_CMD_NOTE_PORTA: {
      int destFreq=(c.value2<<6);
      int newFreq;
      bool return2=false;
      if (destFreq>chan[c.chan].baseFreq) {
        newFreq=chan[c.chan].baseFreq+c.value*4;
        if (newFreq>=destFreq) {
          newFreq=destFreq;
          return2=true;
        }
      } else {
        newFreq=chan[c.chan].baseFreq-c.value*4;
        if (newFreq<=destFreq) {
          newFreq=destFreq;
          return2=true;
        }
      }
      chan[c.chan].baseFreq=newFreq;
      chan[c.chan].freqChanged=true;
      if (return2) {
        chan[c.chan].inPorta=false;
        return 2;
      }
      break;
    }
    case DIV_CMD_LEGATO: {
      chan[c.chan].baseFreq=(c.value<<6);
      chan[c.chan].freqChanged=true;
      break;
    }
    case DIV_CMD_SAMPLE_BANK:
      sampleBank=c.value;
      if (sampleBank>(parent->song.sample.size()/12)) {
        sampleBank=parent->song.sample.size()/12;
      }
      break;
    case DIV_CMD_MACRO_OFF:
      chan[c.chan].std.mask(c.value,true);
      break;
    case DIV_CMD_MACRO_ON:
      chan[c.chan].std.mask(c.value,false);
      break;
    case DIV_ALWAYS_SET_VOLUME:
      return 0;
      break;
    case DIV_CMD_GET_VOLMAX:
      return 127;
      break;
    case DIV_CMD_PRE_PORTA:
      if (!chan[c.chan].inPorta && c.value && !parent->song.brokenPortaArp && chan[c.chan].std.arp.will && !NEW_ARP_STRAT) chan[c.chan].baseFreq=(chan[c.chan].note<<6);
      chan[c.chan].inPorta=c.value;
      break;
    case DIV_CMD_PRE_NOTE:
      break;
    case DIV_CMD_SAMPLE_FREQ:
      chan[c.chan].pcm.freq=c.value;
      rWrite(7+(c.chan<<3),chan[c.chan].pcm.freq);
      break;
    default:
      //printf("WARNING: unimplemented command %d\n",c.cmd);
      break;
  }
  return 1;
}

void DivPlatformSegaPCM::forceIns() {
  for (int i=0; i<16; i++) {
    chan[i].insChanged=true;

    rWrite(2+(i<<3),chan[i].chVolL);
    rWrite(3+(i<<3),chan[i].chVolR);
    rWrite(7+(i<<3),chan[i].pcm.freq);
  }
}

void DivPlatformSegaPCM::notifyInsChange(int ins) {
  for (int i=0; i<16; i++) {
    if (chan[i].ins==ins) {
      chan[i].insChanged=true;
    }
  }
}

void DivPlatformSegaPCM::notifyInsDeletion(void* ins) {
  for (int i=0; i<16; i++) {
    chan[i].std.notifyInsDeletion((DivInstrument*)ins);
  }
}

void* DivPlatformSegaPCM::getChanState(int ch) {
  return &chan[ch];
}

DivMacroInt* DivPlatformSegaPCM::getChanMacroInt(int ch) {
  return &chan[ch].std;
}

DivDispatchOscBuffer* DivPlatformSegaPCM::getOscBuffer(int ch) {
  return oscBuf[ch];
}

unsigned char* DivPlatformSegaPCM::getRegisterPool() {
  return pcm.get_ram();
}

int DivPlatformSegaPCM::getRegisterPoolSize() {
  return 256;
}

void DivPlatformSegaPCM::poke(unsigned int addr, unsigned short val) {
  rWrite(addr,val);
}

void DivPlatformSegaPCM::poke(std::vector<DivRegWrite>& wlist) {
  for (DivRegWrite& i: wlist) rWrite(i.addr,i.val);
}

const void* DivPlatformSegaPCM::getSampleMem(int index) {
  return index == 0 ? sampleMem : NULL;
}

size_t DivPlatformSegaPCM::getSampleMemCapacity(int index) {
  return index == 0 ? 16777216 : 0;
}

size_t DivPlatformSegaPCM::getSampleMemUsage(int index) {
  return index == 0 ? sampleMemLen : 0;
}

bool DivPlatformSegaPCM::isSampleLoaded(int index, int sample) {
  if (index!=0) return false;
  if (sample<0 || sample>255) return false;
  return sampleLoaded[sample];
}

void DivPlatformSegaPCM::reset() {
  while (!writes.empty()) writes.pop();
  memset(regPool,0,256);
  for (int i=0; i<16; i++) {
    chan[i]=DivPlatformSegaPCM::Channel();
    chan[i].std.setEngine(parent);
    chan[i].vol=0x7f;
    chan[i].outVol=0x7f;
  }

  lastBusy=60;
  pcmCycles=0;
  pcmL=0;
  pcmR=0;
  sampleBank=0;
  delay=0;

  pcm.device_start();

  for (int i=0; i<16; i++) {
    rWrite(0x86+(i<<3),3);
    rWrite(2+(i<<3),0x7f);
    rWrite(3+(i<<3),0x7f);
  }
}

 void DivPlatformSegaPCM::renderSamples(int sysID) {
  size_t memPos=0;

  memset(sampleMem,0,16777216);
  memset(sampleLoaded,0,256*sizeof(bool));
  
  for (int i=0; i<parent->song.sampleLen; i++) {
    DivSample* sample=parent->getSample(i);
    unsigned int alignedSize=(sample->getLoopEndPosition(DIV_SAMPLE_DEPTH_8BIT)+0xff)&(~0xff);
    if (alignedSize>65536) alignedSize=65536;
    if ((memPos&0xff0000)!=((memPos+alignedSize)&0xff0000)) {
      memPos=(memPos+0xffff)&0xff0000;
    }
    logV("- sample %d will be at %x with length %x",i,memPos,alignedSize);
    sampleLoaded[i]=true;
    if (memPos>=16777216) break;
    sampleOffSegaPCM[i]=memPos;
    unsigned int readPos=0;
    for (unsigned int j=0; j<alignedSize; j++) {
      if (readPos>=(unsigned int)sample->getLoopEndPosition(DIV_SAMPLE_DEPTH_8BIT)) {
        if (sample->isLoopable()) {
          readPos=sample->getLoopStartPosition(DIV_SAMPLE_DEPTH_8BIT);
          sampleMem[memPos++]=((unsigned char)sample->data8[readPos]+0x80);
        } else {
          sampleMem[memPos++]=0x80;
        }
      } else {
        sampleMem[memPos++]=((unsigned char)sample->data8[readPos]+0x80);
      }
      readPos++;
      if (memPos>=16777216) break;
    }
    sampleLoopOff[i]=readPos-sample->getLoopStartPosition(DIV_SAMPLE_DEPTH_8BIT);
    if (memPos>=16777216) break;
  }
  sampleMemLen=memPos;
}

void DivPlatformSegaPCM::setFlags(const DivConfig& flags) {
  chipClock=8000000.0;
  CHECK_CUSTOM_CLOCK;
  rate=chipClock/256;
  for (int i=0; i<16; i++) {
    oscBuf[i]->rate=rate;
  }
}

int DivPlatformSegaPCM::getOutputCount() {
  return 2;
}

int DivPlatformSegaPCM::init(DivEngine* p, int channels, int sugRate, const DivConfig& flags) {
  parent=p;
  dumpWrites=false;
  skipRegisterWrites=false;
  for (int i=0; i<16; i++) {
    isMuted[i]=false;
    oscBuf[i]=new DivDispatchOscBuffer;
  }
  sampleMem=new unsigned char[16777216];
  pcm.set_bank(segapcm_device::BANK_12M|segapcm_device::BANK_MASKF8);
  pcm.set_read([this](unsigned int addr) -> unsigned char {
    return sampleMem[addr&0xffffff];
  });
  setFlags(flags);
  reset();

  return 16;
}

void DivPlatformSegaPCM::quit() {
  for (int i=0; i<16; i++) {
    delete oscBuf[i];
  }
  delete sampleMem;
}

DivPlatformSegaPCM::~DivPlatformSegaPCM() {
}
