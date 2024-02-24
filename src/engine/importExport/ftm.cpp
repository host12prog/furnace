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

#include "importExport.h"

class DivEngine;

#define CHECK_BLOCK_VERSION(x) \
  if (blockVersion>x) { \
    logW("incompatible block version %d for %s!",blockVersion,blockName); \
  }

enum
{
  FT_EF_NONE = 0,
  FT_EF_SPEED,           	// Speed
  FT_EF_JUMP,            	// Jump
  FT_EF_SKIP,            	// Skip
  FT_EF_HALT,            	// Halt
  FT_EF_VOLUME,          	// Volume
  FT_EF_PORTAMENTO,      	// Porta on
  FT_EF_PORTAOFF,        	// Porta off		// unused
  FT_EF_SWEEPUP,         	// Sweep up
  FT_EF_SWEEPDOWN,       	// Sweep down
  FT_EF_ARPEGGIO,        	// Arpeggio
  FT_EF_VIBRATO,         	// Vibrato
  FT_EF_TREMOLO,         	// Tremolo
  FT_EF_PITCH,           	// Pitch
  FT_EF_DELAY,           	// Note delay
  FT_EF_DAC,             	// DAC setting
  FT_EF_PORTA_UP,        	// Portamento up
  FT_EF_PORTA_DOWN,      	// Portamento down
  FT_EF_DUTY_CYCLE,      	// Duty cycle
  FT_EF_SAMPLE_OFFSET,   	// Sample offset
  FT_EF_SLIDE_UP,        	// Slide up
  FT_EF_SLIDE_DOWN,      	// Slide down
  FT_EF_VOLUME_SLIDE,    	// Volume slide
  FT_EF_NOTE_CUT,        	// Note cut
  FT_EF_RETRIGGER,       	// DPCM retrigger
  FT_EF_DELAYED_VOLUME,  	// // // Delayed channel volume
  FT_EF_FDS_MOD_DEPTH,   	// FDS modulation depth
  FT_EF_FDS_MOD_SPEED_HI,	// FDS modulation speed hi
  FT_EF_FDS_MOD_SPEED_LO,	// FDS modulation speed lo
  FT_EF_DPCM_PITCH,      	// DPCM Pitch
  FT_EF_SUNSOFT_ENV_TYPE,	// Sunsoft envelope type
  FT_EF_SUNSOFT_ENV_HI,  	// Sunsoft envelope high
  FT_EF_SUNSOFT_ENV_LO,  	// Sunsoft envelope low
  FT_EF_SUNSOFT_NOISE,   	// // // 050B Sunsoft noise period
  FT_EF_VRC7_PORT,       	// // // 050B VRC7 custom patch port
  FT_EF_VRC7_WRITE,      	// // // 050B VRC7 custom patch write
  FT_EF_NOTE_RELEASE,    	// // // Delayed release
  FT_EF_GROOVE,          	// // // Groove
  FT_EF_TRANSPOSE,       	// // // Delayed transpose
  FT_EF_N163_WAVE_BUFFER,	// // // N163 wave buffer
  FT_EF_FDS_VOLUME,      	// // // FDS volume envelope
  FT_EF_FDS_MOD_BIAS,    	// // // FDS auto-FM bias
  FT_EF_PHASE_RESET,  // Reset waveform phase without retriggering note (VRC6-only so far)
  FT_EF_HARMONIC,  // Multiply the note pitch by an integer
  FT_EF_TARGET_VOLUME_SLIDE,	// // !! Target volume slide

  FT_EF_COUNT
};

const int ftEffectMap[]={
  -1, // none
  0x0f,
  0x0b,
  0x0d,
  0xff,
  -1, // volume? not supported in Furnace yet
  0x03,
  0x03, // unused?
  0x13,
  0x14,
  0x00,
  0x04,
  0x07,
  0xe5,
  0xed,
  0x11,
  0x01, // porta up
  0x02, // porta down
  0x12,
  0x90, // sample offset - not supported yet
  0xe1, // Slide up
  0xe2,	// Slide down
  0x0a,
  0xec,
  0x0c,
  -1, // delayed volume - not supported yet
  0x11, // FDS modulation depth
  0x12, // FDS modulation speed hi
  0x13, // FDS modulation speed lo
  0x20, // DPCM pitch
  0x22, // Sunsoft envelope type
  0x24, // Sunsoft envelope high
  0x23, // Sunsoft envelope low
  0x21, // 050B Sunsoft noise period
  -1, // VRC7 "custom patch port" - not supported?
  -1, // VRC7 "custom patch write"
  -1, // delayed release - not supported yet
  0x09, // select groove
  -1, // transpose - not supported
  0x10, // Namco 163
  -1, // FDS vol env - not supported
  -1, // FDS auto FM - not supported yet
  -1, // phase reset - not supported
  -1, // harmonic - not supported
  -1, // target volume slide - not supported
};

const int eff_conversion_050[][2] = 
{
	{FT_EF_SUNSOFT_NOISE,		FT_EF_NOTE_RELEASE},
	{FT_EF_VRC7_PORT,			FT_EF_GROOVE},
	{FT_EF_VRC7_WRITE,			FT_EF_TRANSPOSE},
	{FT_EF_NOTE_RELEASE,		FT_EF_N163_WAVE_BUFFER},
	{FT_EF_GROOVE,				FT_EF_FDS_VOLUME},
	{FT_EF_TRANSPOSE,			FT_EF_FDS_MOD_BIAS},
	{FT_EF_N163_WAVE_BUFFER,	FT_EF_SUNSOFT_NOISE},
	{FT_EF_FDS_VOLUME,			FT_EF_VRC7_PORT},
	{FT_EF_FDS_MOD_BIAS,		FT_EF_VRC7_WRITE},
	{0xFF,	0xFF}, //end mark
};

constexpr int ftEffectMapSize=sizeof(ftEffectMap)/sizeof(int);

int convert_macros_2a03[5] = { (int)DIV_MACRO_VOL, (int)DIV_MACRO_ARP, (int)DIV_MACRO_PITCH, -1, (int)DIV_MACRO_DUTY };
int convert_macros_vrc6[5] = { (int)DIV_MACRO_VOL, (int)DIV_MACRO_ARP, (int)DIV_MACRO_PITCH, -1, (int)DIV_MACRO_DUTY };
int convert_macros_n163[5] = { (int)DIV_MACRO_VOL, (int)DIV_MACRO_ARP, (int)DIV_MACRO_PITCH, -1, (int)DIV_MACRO_WAVE };
int convert_macros_s5b[5] = { (int)DIV_MACRO_VOL, (int)DIV_MACRO_ARP, (int)DIV_MACRO_PITCH, -1, (int)DIV_MACRO_DUTY };

void copy_macro(DivInstrument* ins, DivInstrumentMacro* from, int macro_type, int setting)
{
  DivInstrumentMacro* to = NULL;

  switch(ins->type)
  {
    case DIV_INS_NES:
    {
      if(convert_macros_2a03[macro_type] == -1) return;
      to = ins->std.get_macro(convert_macros_2a03[macro_type], true);
      break;
    }
    case DIV_INS_VRC6:
    {
      if(convert_macros_vrc6[macro_type] == -1) return;
      to = ins->std.get_macro(convert_macros_2a03[macro_type], true);
      break;
    }
    case DIV_INS_N163:
    {
      if(convert_macros_vrc6[macro_type] == -1) return;
      to = ins->std.get_macro(convert_macros_n163[macro_type], true);
      break;
    }
    case DIV_INS_AY:
    {
      if(convert_macros_vrc6[macro_type] == -1) return;
      to = ins->std.get_macro(convert_macros_s5b[macro_type], true);
      break;
    }
    default: break;
  }

  if(to == NULL) return;

  for (int i=0; i<256; i++) 
  {
    to->val[i]=from->val[i];

    if((DivMacroType)convert_macros_2a03[macro_type] == DIV_MACRO_ARP)
    {
      if(setting == 0) //absolute
      {
        if(to->val[i] > 0x60)
        {
          int temp = to->val[i];
          to->val[i] = -1 * (0xff - temp + 1); //2s complement integer my beloved
        }
      }

      if(setting == 1) //fixed
      {
        to->val[i] |= (1 << 30); //30th bit in Furnace arp macro marks fixed mode
      }
    }

    if((DivMacroType)convert_macros_2a03[macro_type] == DIV_MACRO_PITCH)
    {
      if(setting == 0 || setting == 1) //relative/absolute
      {
        int temp = to->val[i];

        if(temp < 0x80)
        {
          to->val[i] = -1 * temp;
        }
        else
        {
          to->val[i] = (0x100 - temp);
        }
      }
    }

    if((DivMacroType)convert_macros_n163[macro_type] == DIV_MACRO_WAVE && ins->type == DIV_INS_N163)
    {
      to->val[i] |= (1 << 30); //referencing local wavetables!
    }
  }

  to->len = from->len;
  to->delay = from->delay;
  to->lenMemory = from->lenMemory;
  to->mode = from->mode;
  to->rel = from->rel;
  to->speed = from->speed;
  to->loop = from->loop;
  to->open = from->open;

  if((DivMacroType)convert_macros_2a03[macro_type] == DIV_MACRO_PITCH)
  {
    if(setting == 0) //relative
    {
      to->mode = 1;//setting relative mode
    }
  }

  if(ins->type == DIV_INS_AY && macro_type == 4) //S5B noise/mode macro combines noise freq and tone/env/noise settings, so we need to separate them into two macros
  {
    DivInstrumentMacro* wave = ins->std.get_macro(DIV_MACRO_WAVE, true);
    to = ins->std.get_macro(DIV_MACRO_DUTY, true);
    wave = ins->std.get_macro(DIV_MACRO_WAVE, true);
    to = ins->std.get_macro(DIV_MACRO_DUTY, true);

    wave->len = to->len;
    wave->delay = to->delay;
    wave->lenMemory = to->lenMemory;
    wave->mode = to->mode;
    wave->rel = to->rel;
    wave->speed = to->speed;
    wave->loop = to->loop;
    wave->open = to->open;

    for (int i=0; i<to->len; i++) 
    {
      wave = ins->std.get_macro(DIV_MACRO_WAVE, true);
      to = ins->std.get_macro(DIV_MACRO_DUTY, true);
      wave = ins->std.get_macro(DIV_MACRO_WAVE, true);
      to = ins->std.get_macro(DIV_MACRO_DUTY, true);

      logI("%02X", to->val[i]);
      wave->val[i] = 0;

      int temp = 0;

      if(to->val[i] & 0b10000000) //noise
      {
        temp |= 2;
      }
      if(to->val[i] & 0b01000000) //tone
      {
        temp |= 1;
      }
      if(to->val[i] & 0b00100000) //envelope
      {
        temp |= 4;
      }

      wave->val[i] = temp;

      //#define S5B_ENVL 0b10000000
      //#define S5B_TONE 0b01000000
      //#define S5B_NOIS 0b00100000

      to->val[i] = to->val[i] & 31;
    }
  }
}

bool DivEngine::loadFTM(unsigned char* file, size_t len, bool dnft) {
  SafeReader reader=SafeReader(file,len);
  warnings="";
  try {
    DivSong ds;
    String blockName;
    unsigned char expansions=0;
    unsigned int tchans=0;
    unsigned int n163Chans=0;
    bool hasSequence[256][8];
    unsigned char sequenceIndex[256][8];
    unsigned char macro_types[256][8];
    std::vector<std::vector<DivInstrumentMacro>> macros;
    unsigned char map_channels[DIV_MAX_CHANS];
    unsigned int hilightA=4;
    unsigned int hilightB=16;
    double customHz=60;

    unsigned char fds_chan = 0xff;
    unsigned char vrc6_saw_chan = 0xff;

    int total_chans = 0;
    
    memset(hasSequence,0,256*8*sizeof(bool));
    memset(sequenceIndex,0,256*8);
    memset(macro_types,0,256*8);
    memset(map_channels,0xfe,DIV_MAX_CHANS*sizeof(unsigned char));

    for(int i = 0; i < 256; i++)
    {
      std::vector<DivInstrumentMacro> mac;

      for(int j = 0; j < 8; j++)
      {
        mac.push_back(DivInstrumentMacro(DIV_MACRO_VOL));
      }

      macros.push_back(mac);
    }

    if (!reader.seek(dnft ? 21 : 18,SEEK_SET)) {
      logE("premature end of file!");
      lastError="incomplete file";
      delete[] file;
      return false;
    }
    ds.version=(unsigned short)reader.readI();
    logI("module version %d (0x%.4x)",ds.version,ds.version);

    if (ds.version>0x0450) {
      logE("incompatible version %x!",ds.version);
      lastError="incompatible version";
      delete[] file;
      return false;
    }

    for (DivSubSong* i: ds.subsong) {
      i->clearData();
      delete i;
    }
    ds.subsong.clear();

    ds.linearPitch=0;

    while (true) {
      blockName=reader.readString(3);
      if (blockName=="END") {
        // end of module
        logD("end of data");
        break;
      }

      // not the end
      reader.seek(-3,SEEK_CUR);
      blockName=reader.readString(16);
      unsigned int blockVersion=(unsigned int)reader.readI();
      unsigned int blockSize=(unsigned int)reader.readI();
      size_t blockStart=reader.tell();
      
      logD("reading block %s (version %d, %d bytes, position %x)",blockName,blockVersion,blockSize,reader.tell());
      if (blockName=="PARAMS") {
        // versions 7-9 don't change anything?
        CHECK_BLOCK_VERSION(9);
        unsigned int oldSpeedTempo=0;
        if (blockVersion<=1)
        {
          oldSpeedTempo=reader.readI();
        }
        if (blockVersion>=2) {
          expansions=reader.readC();
        }
        tchans=reader.readI();
        unsigned int pal=reader.readI();
        if (blockVersion>=7) {
          // advanced Hz control
          int controlType=reader.readI();
          switch (controlType) {
            case 1:
              customHz=1000000.0/(double)reader.readI();
              break;
            default:
              reader.readI();
              break;
          }
        } else {
          customHz=reader.readI();
        }
        unsigned int newVibrato=0;
        bool sweepReset=false;
        unsigned int speedSplitPoint=0;
        if (blockVersion>=3) {
          newVibrato=reader.readI();
        }
        if (blockVersion>=9) {
          sweepReset=reader.readI();
        }
        if (blockVersion>=4 && blockVersion<7) {
          hilightA=reader.readI();
          hilightB=reader.readI();
        }
        if ((expansions&16) && blockVersion>=5) { // N163 channels
          n163Chans=reader.readI();
        }
        if (blockVersion>=6) {
          speedSplitPoint=reader.readI();
        }

        if (blockVersion==8) {
          int fineTuneCents=reader.readC()*100;
          fineTuneCents+=reader.readC();

          ds.tuning=440.0*pow(2.0,(double)fineTuneCents/1200.0);
        }

        logV("old speed/tempo: %d",oldSpeedTempo);
        logV("expansions: %x",expansions);
        logV("channels: %d",tchans);
        logV("PAL: %d",pal);
        logV("custom Hz: %f",customHz);
        logV("new vibrato: %d",newVibrato);
        logV("N163 channels: %d",n163Chans);
        logV("highlight 1: %d",hilightA);
        logV("highlight 2: %d",hilightB);
        logV("split point: %d",speedSplitPoint);
        logV("sweep reset: %d",sweepReset);

        // initialize channels
        int systemID=0;

        int curr_chan = 0;
        int map_ch = 0;

        ds.system[systemID++]=DIV_SYSTEM_NES;

        for(int ch = 0; ch < 5; ch++)
        {
          map_channels[curr_chan] = map_ch;
          curr_chan++;
          map_ch++;
        }

        if (expansions&1) 
        {
          ds.system[systemID++]=DIV_SYSTEM_VRC6;

          for(int ch = 0; ch < 3; ch++)
          {
            map_channels[curr_chan] = map_ch;
            curr_chan++;
            map_ch++;
          }

          vrc6_saw_chan = map_ch - 1;
        }
        if (expansions&8) {
          ds.system[systemID++]=DIV_SYSTEM_MMC5;

          for(int ch = 0; ch < 2; ch++)
          {
            map_channels[curr_chan] = map_ch;
            curr_chan++;
            map_ch++;
          }
          
          map_channels[curr_chan] = map_ch; //do not populate and skip MMC5 PCM channel!
          map_ch++;
        }
        if (expansions&16) {
          ds.system[systemID]=DIV_SYSTEM_N163;
          ds.systemFlags[systemID].set("channels",(int)n163Chans);
          systemID++;

          for(int ch = 0; ch < (int)n163Chans; ch++)
          {
            map_channels[curr_chan] = map_ch;
            curr_chan++;
            map_ch++;
          }

          for(int ch = 0; ch < (8 - (int)n163Chans); ch++)
          {
            map_channels[curr_chan] = map_ch; //do not populate and skip the missing N163 channels!
            map_ch++;
          }
        }
        if (expansions&4) {
          ds.system[systemID++]=DIV_SYSTEM_FDS;

          map_channels[curr_chan] = map_ch;
          fds_chan = map_ch;
          curr_chan++;
          map_ch++;
        }
        if (expansions&2) {
          ds.system[systemID++]=DIV_SYSTEM_VRC7;

          for(int ch = 0; ch < 6; ch++)
          {
            map_channels[curr_chan] = map_ch;
            curr_chan++;
            map_ch++;
          }
        }
        if (expansions&32) {
          ds.system[systemID]=DIV_SYSTEM_AY8910;
          ds.systemFlags[systemID++].set("chipType",2); // Sunsoft 5B

          for(int ch = 0; ch < 3; ch++)
          {
            map_channels[curr_chan] = map_ch;
            curr_chan++;
            map_ch++;
          }
        }
        ds.systemLen=systemID;

        for(int i = 0; i < curr_chan; i++)
        {
          logV("map ch: fami ch %d mapped to furnace ch %d", i, map_channels[i]);
        }

        unsigned int calcChans=0;
        for (int i=0; i<ds.systemLen; i++) {
          if(ds.system[i] == DIV_SYSTEM_MMC5)
          {
            calcChans--; //no PCM channel for MMC5 in famitracker
          }

          calcChans+=getChannelCount(ds.system[i]);
          total_chans += getChannelCount(ds.system[i]);

          if(ds.system[i] == DIV_SYSTEM_N163)
          {
            calcChans -= getChannelCount(ds.system[i]);
            calcChans += (int)n163Chans;
          }
        }
        if (calcChans!=tchans) {
          logE("channel counts do not match! %d != %d",tchans,calcChans);
          lastError="channel counts do not match";
          delete[] file;
          return false;
        }
        if (tchans>DIV_MAX_CHANS) {
          tchans=DIV_MAX_CHANS;
          logW("too many channels!");
        }
      } else if (blockName=="INFO") {
        CHECK_BLOCK_VERSION(1);
        ds.name=reader.readString(32);
        ds.author=reader.readString(32);
        ds.category=reader.readString(32);
        ds.systemName="NES";
      } else if (blockName=="HEADER") {
        CHECK_BLOCK_VERSION(4);
        unsigned char totalSongs=reader.readC();
        logV("%d songs:",totalSongs+1);
        ds.subsong.reserve(totalSongs);
        for (int i=0; i<=totalSongs; i++) {
          String subSongName=reader.readString();
          ds.subsong.push_back(new DivSubSong);
          ds.subsong[i]->name=subSongName;
          ds.subsong[i]->hilightA=hilightA;
          ds.subsong[i]->hilightB=hilightB;
          if (customHz!=0) {
            ds.subsong[i]->hz=customHz;
          }
          logV("- %s",subSongName);
        }
        for (unsigned int i=0; i<tchans; i++) {
          // TODO: obey channel ID
          unsigned char chID=reader.readC();
          logV("for channel ID %d",chID);
          for (int j=0; j<=totalSongs; j++) {
            unsigned char effectCols=reader.readC();

            if(map_channels[i] == 0xfe)
            {
              ds.subsong[j]->pat[i].effectCols=1;
              logV("- song %d has %d effect columns",j,effectCols);
            }
            else
            {
              ds.subsong[j]->pat[map_channels[i]].effectCols=effectCols+1;
              logV("- song %d has %d effect columns",j,effectCols);
            }
          }
        }

        if (blockVersion>=4) {
          for (int i=0; i<=totalSongs; i++) {
            ds.subsong[i]->hilightA=(unsigned char)reader.readC();
            ds.subsong[i]->hilightB=(unsigned char)reader.readC();
          }
        }
      } else if (blockName=="INSTRUMENTS") {
        CHECK_BLOCK_VERSION(6);

        //reader.seek(blockSize,SEEK_CUR);

        ds.insLen=reader.readI();
        if (ds.insLen<0 || ds.insLen>256) {
          logE("too many instruments/out of range!");
          lastError="too many instruments/out of range";
          delete[] file;
          return false;
        }

        for (int i=0; i<128; i++) {
          DivInstrument* ins=new DivInstrument;
          ds.ins.push_back(ins);
          ds.ins[i]->type = DIV_INS_FM;
        }

        logV("instruments:");
        for (int i=0; i<ds.insLen; i++) {
          unsigned int insIndex=reader.readI();
          if (insIndex>=ds.ins.size()) {
            //logE("instrument index %d is out of range!",insIndex);
            //lastError="instrument index out of range";
            //delete[] file;
            //return false;
          }

          DivInstrument* ins=ds.ins[insIndex];
          unsigned char insType=reader.readC();
          switch (insType) {
            case 1:
              ins->type=DIV_INS_NES;
              break;
            case 2: // TODO: tell VRC6 and VRC6 saw instruments apart
              ins->type=DIV_INS_VRC6;
              break;
            case 3:
              ins->type=DIV_INS_OPLL;
              break;
            case 4:
              ins->type=DIV_INS_FDS;
              break;
            case 5:
              ins->type=DIV_INS_N163;
              break;
            case 6: // 5B?
              ins->type=DIV_INS_AY;
              break;
            default: {
              logE("%d: invalid instrument type %d",insIndex,insType);
              lastError="invalid instrument type";
              delete[] file;
              return false;
            }
          }

          // instrument data
          switch (ins->type) {
            case DIV_INS_NES: {
              unsigned int totalSeqs=reader.readI();
              if (totalSeqs>5) {
                logE("%d: too many sequences!",insIndex);
                lastError="too many sequences";
                delete[] file;
                return false;
              }

              for (unsigned int j=0; j<totalSeqs; j++) {
                hasSequence[insIndex][j]=reader.readC();
                sequenceIndex[insIndex][j]=reader.readC();
              }

              const int dpcmNotes=(blockVersion>=2)?96:72;
              for (int j=0; j<dpcmNotes; j++) {
                ins->amiga.get_amiga_sample_map(j, true)->map=(short)((unsigned char)reader.readC())-1;
                unsigned char freq = reader.readC();
                ins->amiga.get_amiga_sample_map(j, true)->dpcmFreq=(freq & 15); //0-15 = 0-15 unlooped, 128-143 = 0-15 looped
                ins->amiga.get_amiga_sample_map(j, true)->freq = (freq & 0x80) ? 1 : 0; //loop
                if (blockVersion>=6) {
                  ins->amiga.get_amiga_sample_map(j, true)->dpcmDelta=(unsigned char)reader.readC(); // DMC value
                }
              }

              ins->amiga.useSample = true;
              ins->amiga.useNoteMap = true;
              break;
            }
            case DIV_INS_VRC6: {
              unsigned int totalSeqs=reader.readI();
              if (totalSeqs>5) {
                logE("%d: too many sequences!",insIndex);
                lastError="too many sequences";
                delete[] file;
                return false;
              }

              for (unsigned int j=0; j<totalSeqs; j++) {
                hasSequence[insIndex][j]=reader.readC();
                sequenceIndex[insIndex][j]=reader.readC();
              }
              break;
            }
            case DIV_INS_OPLL: {
              ins->fm.opllPreset=(unsigned int)reader.readI();
              
              for(int i = 0; i < 8; i++)
              {
                unsigned char custom_patch = reader.readC();
                (void)custom_patch;
              }
              break;
            }
            case DIV_INS_FDS: {
              DivWavetable* wave=new DivWavetable;
              wave->len=64;
              wave->max=64;
              for (int j=0; j<64; j++) {
                wave->data[j]=reader.readC();
              }
              ins->std.get_macro(DIV_MACRO_WAVE, true)->len=1;
              ins->std.get_macro(DIV_MACRO_WAVE, true)->val[0]=ds.wave.size();
              for (int j=0; j<32; j++) {
                ins->fds.modTable[j]=reader.readC() - 3;
              }
              ins->fds.modSpeed=reader.readI();
              ins->fds.modDepth=reader.readI();
              reader.readI(); // this is delay. currently ignored. TODO.
              ds.wave.push_back(wave);
              ds.waveLen++;

              unsigned int a = reader.readI();
              unsigned int b = reader.readI();

              reader.seek(-8, SEEK_CUR);

              if(a < 256 && (b & 0xFF) != 0x00)
              {
                //don't look at me like this. I don't know why this should be like this either!
              }
              else
              {
                ins->std.get_macro(DIV_MACRO_VOL, true)->len=reader.readC();
                ins->std.get_macro(DIV_MACRO_VOL, true)->loop=reader.readI();
                ins->std.get_macro(DIV_MACRO_VOL, true)->rel=reader.readI();
                reader.readI(); // arp mode does not apply here
                for (int j=0; j<ins->std.get_macro(DIV_MACRO_VOL, true)->len; j++) {
                  ins->std.get_macro(DIV_MACRO_VOL, true)->val[j]=reader.readC();

                  if(blockVersion <= 3)
                  {
                    ins->std.get_macro(DIV_MACRO_VOL, true)->val[j] *= 2;
                  }
                }

                ins->std.get_macro(DIV_MACRO_ARP, true)->len=reader.readC();
                ins->std.get_macro(DIV_MACRO_ARP, true)->loop=reader.readI();
                ins->std.get_macro(DIV_MACRO_ARP, true)->rel=reader.readI();
                unsigned int mode=reader.readI();
                for (int j=0; j<ins->std.get_macro(DIV_MACRO_ARP, true)->len; j++) {
                  ins->std.get_macro(DIV_MACRO_ARP, true)->val[j]=reader.readC();

                  if(mode == 1) //fixed arp
                  {
                    ins->std.get_macro(DIV_MACRO_ARP, true)->val[j] |= (1 << 30);
                  }
                }

                if(blockVersion >= 3)
                {
                  ins->std.get_macro(DIV_MACRO_PITCH, true)->len=reader.readC();
                  ins->std.get_macro(DIV_MACRO_PITCH, true)->loop=reader.readI();
                  ins->std.get_macro(DIV_MACRO_PITCH, true)->rel=reader.readI();
                  reader.readI(); // arp mode does not apply here
                  for (int j=0; j<ins->std.get_macro(DIV_MACRO_PITCH, true)->len; j++) {
                    ins->std.get_macro(DIV_MACRO_PITCH, true)->val[j]=reader.readC();

                    int temp_val = ins->std.get_macro(DIV_MACRO_PITCH, true)->val[j];
                    int temp = temp_val;

                    if(temp_val < 0x80)
                    {
                      ins->std.get_macro(DIV_MACRO_PITCH, true)->val[j] = temp;
                    }
                    else
                    {
                      ins->std.get_macro(DIV_MACRO_PITCH, true)->val[j] = -1 * (0x100 - temp);
                    }
                  }

                  if(mode == 0) //relative
                  {
                    ins->std.get_macro(DIV_MACRO_PITCH, true)->mode = 1;//setting relative mode
                  }
                }
              }

              break;
            }
            case DIV_INS_N163: { //TODO: add local wavetables and finish this!
              unsigned int totalSeqs=reader.readI();
              if (totalSeqs>5) {
                logE("%d: too many sequences!",insIndex);
                lastError="too many sequences";
                delete[] file;
                return false;
              }

              for (unsigned int j=0; j<totalSeqs; j++) {
                hasSequence[insIndex][j]=reader.readC();
                sequenceIndex[insIndex][j]=reader.readC();
              }

              unsigned int wave_size = reader.readI();
              unsigned int wave_pos = reader.readI();
              ins->n163.waveLen = wave_size;
              ins->n163.wavePos = wave_pos;

              if(blockVersion >= 8)
              {
                unsigned int autopos = reader.readI();
                (void)autopos;
              }

              unsigned int wave_count = reader.readI();

              for(unsigned int ii = 0; ii < wave_count; ii++)
              {
                DivWavetable* wave = new DivWavetable();
                wave->len = wave_size;
                wave->max = 15;

                for(unsigned int jj = 0; jj < wave_size; jj++)
                {
                  unsigned char val = reader.readC();
                  wave->data[jj] = val;
                }

                ins->std.local_waves.push_back(wave);
              }

              if(ins->std.get_macro(DIV_MACRO_WAVE, true)->len == 0) //empty wave macro
              {
                ins->std.get_macro(DIV_MACRO_WAVE, true)->len = 1;
                ins->std.get_macro(DIV_MACRO_WAVE, true)->val[0] = 0 | (1 << 30); //force local wave number 0
              }

              break;
            }
            
            case DIV_INS_AY:
            {
              unsigned int totalSeqs=reader.readI();
              if (totalSeqs>5) {
                logE("%d: too many sequences!",insIndex);
                lastError="too many sequences";
                delete[] file;
                return false;
              }

              for (unsigned int j=0; j<totalSeqs; j++) {
                hasSequence[insIndex][j]=reader.readC();
                sequenceIndex[insIndex][j]=reader.readC();
              }

              break;
            }

            default: {
              logE("%d: what's going on here?",insIndex);
              lastError="invalid instrument type";
              delete[] file;
              return false;
            }
          }

          // name
          ins->name=reader.readString((unsigned int)reader.readI());
          logV("- %d: %s",insIndex,ins->name);
        }

        ds.insLen = 128;
        
      } else if (blockName=="SEQUENCES") {
        CHECK_BLOCK_VERSION(6);
        //reader.seek(blockSize,SEEK_CUR);

        if(blockVersion < 3)
        {
          lastError="sequences block version is too old";
          delete[] file;
          return false;
        }

        unsigned char* Indices = new unsigned char[128 * 5];
		    unsigned char* Types = new unsigned char[128 * 5];

        unsigned int seq_count = reader.readI();

        for(unsigned int i = 0; i < seq_count; i++)
        {
          unsigned int index = reader.readI();
          Indices[i] = index;
          unsigned int type = reader.readI();
          Types[i] = type;

          unsigned char size = reader.readC();
          unsigned int setting = 0;

          macros[index][type].len = size;

          unsigned int loop = reader.readI();

          macros[index][type].loop = loop;

          if(blockVersion == 4)
          {
            unsigned int release = reader.readI();
            setting = reader.readI();

            macros[index][type].rel = release;
            macro_types[index][type] = setting;
          }

          for(int j = 0; j < size; j++)
          {
            unsigned char seq = reader.readC();
            macros[index][type].val[j] = seq;
          }

          for(int k = 0; k < (int)ds.ins.size(); k++)
          {
            DivInstrument* ins=ds.ins[k];
            if(sequenceIndex[k][Types[i]] == Indices[i] && ins->type == DIV_INS_NES && hasSequence[k][Types[i]])
            {
              copy_macro(ins, &macros[sequenceIndex[index][type]][type], Types[i], setting);
              //memcpy(ins->std.get_macro(DIV_MACRO_VOL + (DivMacroType)Types[i], true), &macros[sequenceIndex[index][type]][type], sizeof(DivInstrumentMacro));
            }
          }
        }

        if(blockVersion == 5)  // Version 5 saved the release points incorrectly, this is fixed in ver 6
        {
          for(int i = 0; i < 128; i++)
          {
            for(int j = 0; j < 5; j++)
            {
              unsigned int release = reader.readI();
              unsigned int setting = reader.readI();

              for(int k = 0; k < (int)ds.ins.size(); k++)
              {
                DivInstrument* ins=ds.ins[k];
                if(sequenceIndex[k][j] == i && ins->type == DIV_INS_NES && hasSequence[k][j])
                {
                  macros[k][j].rel = release;
                  macro_types[k][j] = setting;

                  copy_macro(ins, &macros[sequenceIndex[k][j]][j], j, setting);
                  //memcpy(ins->std.get_macro(DIV_MACRO_VOL + (DivMacroType)j, true), &macros[sequenceIndex[k][j]][j], sizeof(DivInstrumentMacro));
                }
              }
            }
          }
        }

        if(blockVersion >= 6) // Read release points correctly stored
        {
          for(unsigned int i = 0; i < seq_count; i++)
          {
            unsigned int release = reader.readI();
            unsigned int setting = reader.readI();

            //macros[index][type].rel = release;
            //macro_types[index][type] = setting;

            for(int k = 0; k < (int)ds.ins.size(); k++)
            {
              DivInstrument* ins=ds.ins[k];
              if(sequenceIndex[k][Types[i]] == Indices[i] && ins->type == DIV_INS_NES && hasSequence[k][Types[i]])
              {
                macros[sequenceIndex[k][Types[i]]][Types[i]].rel = release;
                macro_types[k][Types[i]] = setting;
                
                copy_macro(ins, &macros[sequenceIndex[k][Types[i]]][Types[i]], Types[i], setting);
                //memcpy(ins->std.get_macro(DIV_MACRO_VOL + (DivMacroType)Types[i], true), &macros[sequenceIndex[k][Types[i]]][Types[i]], sizeof(DivInstrumentMacro));
              }
            }
          }
        }

        delete[] Indices;
        delete[] Types;
      } 
      else if (blockName=="GROOVES") {
        CHECK_BLOCK_VERSION(6);
        //reader.seek(blockSize,SEEK_CUR);

        unsigned char num_grooves = reader.readC();
        int max_groove = 0;

        for(int i = 0; i < 0xff; i++)
        {
          ds.grooves.push_back(DivGroovePattern());
        }

        for(int gr = 0; gr < num_grooves; gr++)
        {
          unsigned char index = reader.readC();
          unsigned char size = reader.readC();

          if(index > max_groove) max_groove = index + 1;
          
          DivGroovePattern gp;
          gp.len = size;

          for(int sz = 0; sz < size; sz++)
          {
            unsigned char value = reader.readC();
            gp.val[sz] = value;
          }

          ds.grooves[index] = gp;
        }

        ds.grooves.resize(max_groove == 0 ? 1 : max_groove);

        unsigned char subsongs = reader.readC();

        for(int sub = 0; sub < subsongs; sub++)
        {
          unsigned char used = reader.readC();

          if(used)
          {
            ds.subsong[sub]->speeds = ds.grooves[0];
          }
        }

        if((reader.tell()-blockStart)!=blockSize)
        {
          logE("block %s size does not match! block size %d curr pos %d",blockName,blockSize,reader.tell()-blockStart);
        }

      } else if (blockName=="FRAMES") {
        CHECK_BLOCK_VERSION(3);

        for (size_t i=0; i<ds.subsong.size(); i++) {
          DivSubSong* s=ds.subsong[i];

          s->ordersLen=reader.readI();
          if (blockVersion>=3) {
            s->speeds.val[0]=reader.readI();
          }
          if (blockVersion>=2) {
            s->virtualTempoN=reader.readI();
            
            if(s->virtualTempoN == 0)
            {
              s->virtualTempoN = 150; //TODO: make it properly
            }

            s->patLen=reader.readI();
          }
          int why=tchans;
          if (blockVersion==1) {
            why=reader.readI();
          }
          logV("reading %d and %d orders",tchans,s->ordersLen);

          for (int j=0; j<s->ordersLen; j++) {
            for (int k=0; k<why; k++) {
              unsigned char o=reader.readC();
              //logV("%.2x",o);
              s->orders.ord[map_channels[k]][j]=o;
            }
          }
        }
      } else if (blockName=="PATTERNS") {
        CHECK_BLOCK_VERSION(6);

        size_t blockEnd=reader.tell()+blockSize;

        if (blockVersion==1) {
          int patLenOld=reader.readI();
          for (DivSubSong* i: ds.subsong) {
            i->patLen=patLenOld;
          }
        }

        // so it appears .ftm doesn't keep track of how many patterns are stored in the file....
        while (reader.tell()<blockEnd) {
          int subs=0;
          if (blockVersion>=2) subs=reader.readI();
          int ch=reader.readI();
          int patNum=reader.readI();
          int numRows=reader.readI();

          DivPattern* pat=ds.subsong[subs]->pat[map_channels[ch]].getPattern(patNum,true);
          for (int i=0; i<numRows; i++) {
            unsigned int row=0;
            if (blockVersion>=2 && blockVersion<6) { // row index
              row=reader.readI();
            } else {
              row=reader.readC();
            }

            unsigned char nextNote=reader.readC();
            unsigned char nextOctave=reader.readC();

            if(blockVersion < 5 && map_channels[ch] == fds_chan) //FDS transpose
            {
              nextOctave += 2;
              nextOctave -= 2;
            }
            if(blockVersion >= 5 && map_channels[ch] == fds_chan) //FDS transpose
            {
              nextOctave -= 2;
            }

            if(map_channels[ch] != 0xff)
            {
              if (nextNote==0x0d) {
                pat->data[row][0]=101;
              } else if (nextNote==0x0e) {
                pat->data[row][0]=100;
              } else if (nextNote==0x01) {
                pat->data[row][0]=12;
                pat->data[row][1]=nextOctave-1;
              } else if (nextNote==0) {
                pat->data[row][0]=0;
              } else if (nextNote<0x0d) {
                pat->data[row][0]=nextNote-1;
                pat->data[row][1]=nextOctave;
              }
            }
            
            unsigned char nextIns=reader.readC();
            if(map_channels[ch] != 0xff)
            {
              if (nextIns<0x40 && nextNote != 0x0d && nextNote != 0x0e) {
                pat->data[row][2]=nextIns;
              } else {
                pat->data[row][2]=-1;
              }
            }

            unsigned char nextVol=reader.readC();
            if(map_channels[ch] != 0xff)
            {
              if (nextVol<0x10) {
                pat->data[row][3]=nextVol;
                if(map_channels[ch] == vrc6_saw_chan)
                {
                  pat->data[row][3] = pat->data[row][3] * 42 / 15;
                }
              } 
              else 
              {
                pat->data[row][3]=-1;
              }
            }

            int effectCols=ds.subsong[subs]->pat[map_channels[ch]].effectCols;
            if (blockVersion>=6) effectCols=4;

            for (int j=0; j<effectCols; j++) {
              unsigned char nextEffect=reader.readC();

              if(ds.version < 0x0450 || dnft)
              {
                unsigned char idx = 0;

                while(eff_conversion_050[idx][0] != 0xFF) //until the end of the array
                {
                  if(nextEffect == eff_conversion_050[idx][0]) //remap the effects (0CC vs FT effects type order) bruh idk why but it should be done to correctly read some modules
                  {
                    nextEffect = eff_conversion_050[idx][1];

                    goto stop;
                  }

                  idx++;
                }

                stop:;
              }

              unsigned char nextEffectVal=0;
              if (nextEffect!=0 || blockVersion<6) nextEffectVal=reader.readC();
              if(map_channels[ch] != 0xff)
              {
                if (nextEffect==0 && nextEffectVal==0) {
                  pat->data[row][4+(j*2)]=-1;
                  pat->data[row][5+(j*2)]=-1;
                } else {
                  if (nextEffect<ftEffectMapSize) {
                    pat->data[row][4+(j*2)]=ftEffectMap[nextEffect];
                    pat->data[row][5+(j*2)]=ftEffectMap[nextEffect] == -1 ? -1 : nextEffectVal;

                    if(ftEffectMap[nextEffect] == 0x0f && nextEffectVal > 0x1f)
                    {
                      pat->data[row][4+(j*2)] = 0xf0; //BPM speed change!
                    }
                  } else {
                    pat->data[row][4+(j*2)]=-1;
                    pat->data[row][5+(j*2)]=-1;
                  }
                }
              }
            }
          }
        }
      } else if (blockName=="DPCM SAMPLES") {
        CHECK_BLOCK_VERSION(1);
        //reader.seek(blockSize,SEEK_CUR);
        unsigned char num_samples = reader.readC();

        for(int i = 0; i < 256; i++)
        {
          DivSample* s = new DivSample();
          ds.sample.push_back(s);
        }

        ds.sampleLen = ds.sample.size();

        unsigned int true_size = 0;
        unsigned char index = 0;

        for(unsigned char i = 0; i < num_samples; i++)
        {
          index = reader.readC();

          DivSample* sample = ds.sample[index];

          sample->rate=33144;
          sample->centerRate=33144;
          sample->depth=DIV_SAMPLE_DEPTH_1BIT_DPCM;

          sample->name=reader.readString((unsigned int)reader.readI());

          unsigned int sample_len = reader.readI();

          true_size = sample_len + ((1 - (int)sample_len) & 0x0f);
          sample->lengthDPCM = true_size;
          sample->samples = true_size * 8;

          sample->dataDPCM = new unsigned char[true_size];

          memset(sample->dataDPCM, 0xAA, true_size);

          reader.read(sample->dataDPCM,true_size);
        }

        int last_non_empty_sample = 0xff;

        for(int i = 255; i > 0; i--)
        {
          DivSample* s = ds.sample[i];

          if(s->dataDPCM)
          {
            last_non_empty_sample = i;
            break;
          }
        }

        for(int i = 255; i > last_non_empty_sample; i--)
        {
          ds.sample.erase(ds.sample.begin()+i);
        }

        ds.sampleLen = ds.sample.size();

      } else if (blockName=="SEQUENCES_VRC6") {
        CHECK_BLOCK_VERSION(6);
        //reader.seek(blockSize,SEEK_CUR);

        if(blockVersion < 3)
        {
          lastError="sequences block version is too old";
          delete[] file;
          return false;
        }

        unsigned char* Indices = new unsigned char[128 * 5];
		    unsigned char* Types = new unsigned char[128 * 5];

        unsigned int seq_count = reader.readI();

        for(unsigned int i = 0; i < seq_count; i++)
        {
          unsigned int index = reader.readI();
          Indices[i] = index;
          unsigned int type = reader.readI();
          Types[i] = type;

          unsigned char size = reader.readC();
          unsigned int setting = 0;

          macros[index][type].len = size;

          unsigned int loop = reader.readI();

          macros[index][type].loop = loop;

          if(blockVersion == 4)
          {
            unsigned int release = reader.readI();
            setting = reader.readI();

            macros[index][type].rel = release;
            macro_types[index][type] = setting;
          }

          for(int j = 0; j < size; j++)
          {
            unsigned char seq = reader.readC();
            macros[index][type].val[j] = seq;
          }

          for(int k = 0; k < (int)ds.ins.size(); k++)
          {
            DivInstrument* ins=ds.ins[k];
            if(sequenceIndex[k][Types[i]] == Indices[i] && ins->type == DIV_INS_VRC6 && hasSequence[k][Types[i]])
            {
              copy_macro(ins, &macros[sequenceIndex[index][type]][type], type, setting);

              if(type == 0 && setting == 1)
              {
                ins->type = DIV_INS_VRC6_SAW;
              }
            }
          }
        }

        if(blockVersion == 5)  // Version 5 saved the release points incorrectly, this is fixed in ver 6
        {
          for(int i = 0; i < 128; i++)
          {
            for(int j = 0; j < 5; j++)
            {
              unsigned int release = reader.readI();
              unsigned int setting = reader.readI();

              for(int k = 0; k < (int)ds.ins.size(); k++)
              {
                DivInstrument* ins=ds.ins[k];
                if(sequenceIndex[k][j] == i && ins->type == DIV_INS_VRC6 && hasSequence[k][j])
                {
                  macros[k][j].rel = release;
                  macro_types[k][j] = setting;

                  copy_macro(ins, &macros[sequenceIndex[k][j]][j], j, setting);
                  
                  if(j == 0 && setting == 1)
                  {
                    ins->type = DIV_INS_VRC6_SAW;
                  }
                }
              }
            }
          }
        }

        if(blockVersion >= 6) // Read release points correctly stored
        {
          for(unsigned int i = 0; i < seq_count; i++)
          {
            unsigned int release = reader.readI();
            unsigned int setting = reader.readI();

            //macros[index][type].rel = release;
            //macro_types[index][type] = setting;

            for(int k = 0; k < (int)ds.ins.size(); k++)
            {
              DivInstrument* ins=ds.ins[k];
              if(sequenceIndex[k][Types[i]] == Indices[i] && ins->type == DIV_INS_VRC6 && hasSequence[k][Types[i]])
              {
                macros[sequenceIndex[k][Types[i]]][Types[i]].rel = release;
                macro_types[k][Types[i]] = setting;
                
                copy_macro(ins, &macros[sequenceIndex[k][Types[i]]][Types[i]], Types[i], setting);

                if(Types[i] == 0 && setting == 1)
                {
                  ins->type = DIV_INS_VRC6_SAW;
                }
              }
            }
          }
        }

        delete[] Indices;
        delete[] Types;
      } else if (blockName=="SEQUENCES_N163" || blockName=="SEQUENCES_N106") {
        CHECK_BLOCK_VERSION(1);
        //reader.seek(blockSize,SEEK_CUR);

        unsigned char* Indices = new unsigned char[128 * 5];
		    unsigned char* Types = new unsigned char[128 * 5];

        unsigned int seq_count = reader.readI();

        for(unsigned int i = 0; i < seq_count; i++)
        {
          unsigned int index = reader.readI();
          Indices[i] = index;
          unsigned int type = reader.readI();
          Types[i] = type;

          unsigned char size = reader.readC();
          unsigned int setting = 0;

          macros[index][type].len = size;

          unsigned int loop = reader.readI();

          macros[index][type].loop = loop;

          unsigned int release = reader.readI();
          setting = reader.readI();

          macros[index][type].rel = release;
          macro_types[index][type] = setting;

          for(int j = 0; j < size; j++)
          {
            unsigned char seq = reader.readC();
            macros[index][type].val[j] = seq;
          }

          for(int k = 0; k < (int)ds.ins.size(); k++)
          {
            DivInstrument* ins=ds.ins[k];
            if(sequenceIndex[k][Types[i]] == Indices[i] && ins->type == DIV_INS_N163 && hasSequence[k][Types[i]])
            {
              copy_macro(ins, &macros[sequenceIndex[index][type]][type], type, setting);
              //memcpy(ins->std.get_macro(DIV_MACRO_VOL + (DivMacroType)Types[i], true), &macros[sequenceIndex[index][type]][type], sizeof(DivInstrumentMacro));
            }
          }
        }

        delete[] Indices;
        delete[] Types;

      } else if (blockName=="SEQUENCES_S5B") {
        CHECK_BLOCK_VERSION(1);
        //reader.seek(blockSize,SEEK_CUR);

        unsigned char* Indices = new unsigned char[128 * 5];
		    unsigned char* Types = new unsigned char[128 * 5];

        unsigned int seq_count = reader.readI();

        for(unsigned int i = 0; i < seq_count; i++)
        {
          unsigned int index = reader.readI();
          Indices[i] = index;
          unsigned int type = reader.readI();
          Types[i] = type;

          unsigned char size = reader.readC();
          unsigned int setting = 0;

          macros[index][type].len = size;

          unsigned int loop = reader.readI();

          macros[index][type].loop = loop;

          unsigned int release = reader.readI();
          setting = reader.readI();

          macros[index][type].rel = release;
          macro_types[index][type] = setting;

          for(int j = 0; j < size; j++)
          {
            unsigned char seq = reader.readC();
            macros[index][type].val[j] = seq;
          }

          for(int k = 0; k < (int)ds.ins.size(); k++)
          {
            DivInstrument* ins=ds.ins[k];
            if(sequenceIndex[k][type] == Indices[i] && ins->type == DIV_INS_AY && hasSequence[k][type])
            {
              copy_macro(ins, &macros[index][type], type, setting);
              //memcpy(ins->std.get_macro(DIV_MACRO_VOL + (DivMacroType)Types[i], true), &macros[sequenceIndex[index][type]][type], sizeof(DivInstrumentMacro));
            }
          }
        }

        delete[] Indices;
        delete[] Types;
      } else if (blockName=="JSON") {
        CHECK_BLOCK_VERSION(1);
        reader.seek(blockSize,SEEK_CUR);
      } else if (blockName=="PARAMS_EMU") {
        CHECK_BLOCK_VERSION(1);
        reader.seek(blockSize,SEEK_CUR);
      } else if (blockName=="DETUNETABLES") {
        CHECK_BLOCK_VERSION(1);
        reader.seek(blockSize,SEEK_CUR);
      } else if (blockName=="COMMENTS") {
        CHECK_BLOCK_VERSION(1);
        //reader.seek(blockSize,SEEK_CUR);
        unsigned int display_comment = reader.readI();
        (void)display_comment;

        char ch = 1;

        do
        {
          ch = reader.readC();
          String sss = String() + ch;
          ds.subsong[0]->notes += sss;
        } while (ch != 0);

        //ds.subsong[0]->notes = reader.readS();
      } else if (blockName=="PARAMS_EXTRA") {
        CHECK_BLOCK_VERSION(1);
        //reader.seek(blockSize,SEEK_CUR);
        unsigned int linear_pitch = reader.readI();

        ds.linearPitch = linear_pitch == 0 ? 0 : 2;

        if(blockVersion >= 2)
        {
          int fineTuneCents=reader.readC()*100;
          fineTuneCents+=reader.readC();

          ds.tuning=440.0*pow(2.0,(double)fineTuneCents/1200.0);
        }
      } else if (blockName=="TUNING") {
        CHECK_BLOCK_VERSION(1);
        //reader.seek(blockSize,SEEK_CUR);
        if (blockVersion==1) {
          int fineTuneCents=reader.readC()*100;
          fineTuneCents+=reader.readC();

          ds.tuning=440.0*pow(2.0,(double)fineTuneCents/1200.0);
        }
      } else if (blockName=="BOOKMARKS") {
        CHECK_BLOCK_VERSION(1);
        reader.seek(blockSize,SEEK_CUR);
      } else {
        logE("block %s is unknown!",blockName);
        lastError="unknown block "+blockName;
        delete[] file;
        return false;
      }

      if ((reader.tell()-blockStart)!=blockSize) {
        logE("block %s is incomplete!",blockName);
        lastError="incomplete block "+blockName;
        delete[] file;
        return false;
      }
    }

    //addWarning("FamiTracker import is experimental!");

    for(int tries = 0; tries < 5; tries++)
    {
      for(int i = 0; i < 128; i++)
      {
        int index = i >= (int)ds.insLen ? ((int)ds.insLen - 1) : i;
        DivInstrument* ins = ds.ins[index];

        if(ins->type == DIV_INS_FM)
        {
          delete ds.ins[index];
          ds.ins.erase(ds.ins.begin()+index);
          ds.insLen=ds.ins.size();
          for (int ii=0; ii<total_chans; ii++) 
          {
            for (size_t j=0; j<ds.subsong.size(); j++) 
            {
              for (int k=0; k<DIV_MAX_PATTERNS; k++) 
              {
                if (ds.subsong[j]->pat[ii].data[k]==NULL) continue;
                for (int l=0; l<ds.subsong[j]->patLen; l++) 
                {
                  if (ds.subsong[j]->pat[ii].data[k]->data[l][2]>index) 
                  {
                    ds.subsong[j]->pat[ii].data[k]->data[l][2]--;
                  }
                }
              }
            }
          }
        }
      }
    }

    //ds.version=DIV_VERSION_FTM;
    ds.version=DIV_ENGINE_VERSION;
    ds.insLen=ds.ins.size();
    ds.sampleLen = ds.sample.size();
    ds.waveLen = ds.wave.size();

    if (active) quitDispatch();
    BUSY_BEGIN_SOFT;
    saveLock.lock();
    song.unload();
    song=ds;
    changeSong(0);
    recalcChans();
    saveLock.unlock();
    BUSY_END;
    if (active) {
      initDispatch();
      BUSY_BEGIN;
      renderSamples();
      reset();
      BUSY_END;
    }
  } catch (EndOfFileException& e) {
    logE("premature end of file!");
    lastError="incomplete file";
    delete[] file;
    return false;
  }
  delete[] file;
  return true;
}