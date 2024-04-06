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

#include "../platform/fzt.h"

#ifdef HAVE_GUI
#include "../gui/gui.h"
extern FurnaceGUI g;
#endif

#ifdef HAVE_GUI
#define _LE(string) g.locale.getText(string)
#else
#define _LE(string) (string)
#endif

#define TRACKER_ENGINE_VERSION 1

#define MAX_INSTRUMENTS 31

#define MUS_NOTE_NONE_FZT 127
#define MUS_NOTE_RELEASE_FZT 126
#define MUS_NOTE_CUT_FZT 125

#define MUS_NOTE_INSTRUMENT_NONE_FZT 31
#define MUS_NOTE_VOLUME_NONE_FZT 31

class DivEngine;

typedef enum {
    TEE_EFFECT_ARPEGGIO = 0x0000,
    TEE_EFFECT_PORTAMENTO_UP = 0x0100,
    TEE_EFFECT_PORTAMENTO_DOWN = 0x0200,
    TEE_EFFECT_SLIDE = 0x0300,
    TEE_EFFECT_VIBRATO = 0x0400,
    TEE_EFFECT_PWM = 0x0500,
    TEE_EFFECT_SET_PW = 0x0600,
    TEE_EFFECT_PW_DOWN = 0x0700,
    TEE_EFFECT_PW_UP = 0x0800,
    TEE_EFFECT_SET_CUTOFF = 0x0900,
    TEE_EFFECT_VOLUME_FADE = 0x0a00,
    TEE_EFFECT_SET_WAVEFORM = 0x0b00,
    TEE_EFFECT_SET_VOLUME = 0x0c00,
    TEE_EFFECT_SKIP_PATTERN = 0x0d00,

    TEE_EFFECT_EXT = 0x0e00,
    TEE_EFFECT_EXT_TOGGLE_FILTER = 0x0e00,
    TEE_EFFECT_EXT_PORTA_UP = 0x0e10,
    TEE_EFFECT_EXT_PORTA_DN = 0x0e20,
    TEE_EFFECT_EXT_FILTER_MODE = 0x0e30,
    TEE_EFFECT_EXT_PATTERN_LOOP = 0x0e60, // e60 = start, e61-e6f = end and indication how many loops you want
    TEE_EFFECT_EXT_RETRIGGER = 0x0e90,
    TEE_EFFECT_EXT_FINE_VOLUME_DOWN = 0x0ea0,
    TEE_EFFECT_EXT_FINE_VOLUME_UP = 0x0eb0,
    TEE_EFFECT_EXT_NOTE_CUT = 0x0ec0,
    TEE_EFFECT_EXT_NOTE_DELAY = 0x0ed0,
    TEE_EFFECT_EXT_PHASE_RESET = 0x0ef0,

    TEE_EFFECT_SET_SPEED_PROG_PERIOD = 0x0f00,
    TEE_EFFECT_CUTOFF_UP = 0x1000, // Gxx
    TEE_EFFECT_CUTOFF_DOWN = 0x1100, // Hxx
    TEE_EFFECT_SET_RESONANCE = 0x1200, // Ixx
    TEE_EFFECT_RESONANCE_UP = 0x1300, // Jxx
    TEE_EFFECT_RESONANCE_DOWN = 0x1400, // Kxx

    TEE_EFFECT_SET_ATTACK = 0x1500, // Lxx
    TEE_EFFECT_SET_DECAY = 0x1600, // Mxx
    TEE_EFFECT_SET_SUSTAIN = 0x1700, // Nxx
    TEE_EFFECT_SET_RELEASE = 0x1800, // Oxx
    TEE_EFFECT_PROGRAM_RESTART = 0x1900, // Pxx
    
    TEE_EFFECT_SET_RATE = 0x1a00, //Qxx

    TEE_EFFECT_SET_RING_MOD_SRC = 0x1b00, // Rxx
    TEE_EFFECT_SET_HARD_SYNC_SRC = 0x1c00, // Sxx

    TEE_EFFECT_PORTA_UP_SEMITONE = 0x1d00, // Txx
    TEE_EFFECT_PORTA_DOWN_SEMITONE = 0x1e00, // Uxx
    TEE_EFFECT_PITCH = 0x1f00, //Vxx
    /*
    TEE_EFFECT_ = 0x2000, //Wxx
    */

    TEE_EFFECT_LEGATO = 0x2100, // Xxx
    TEE_EFFECT_ARPEGGIO_ABS = 0x2200, // Yxx
    TEE_EFFECT_TRIGGER_RELEASE = 0x2300, // Zxx

    /* These effects work only in instrument program */
    TEE_PROGRAM_LOOP_BEGIN = 0x7d00,
    TEE_PROGRAM_LOOP_END = 0x7e00,
    TEE_PROGRAM_JUMP = 0x7f00,
    TEE_PROGRAM_NOP = 0x7ffe,
    TEE_PROGRAM_END = 0x7fff,                                                
} EffectCommandsOpcodes;

const int fzt_commands_map_real[][2] = 
{
  { DivInstrumentFZT::TE_EFFECT_ARPEGGIO, TEE_EFFECT_ARPEGGIO},    
  { DivInstrumentFZT::TE_EFFECT_PORTAMENTO_UP, TEE_EFFECT_PORTAMENTO_UP},
  { DivInstrumentFZT::TE_EFFECT_PORTAMENTO_DOWN, TEE_EFFECT_PORTAMENTO_DOWN},
  { DivInstrumentFZT::TE_EFFECT_VIBRATO, TEE_EFFECT_VIBRATO},
  { DivInstrumentFZT::TE_EFFECT_PWM, TEE_EFFECT_PWM},
  { DivInstrumentFZT::TE_EFFECT_SET_PW, TEE_EFFECT_SET_PW},
  { DivInstrumentFZT::TE_EFFECT_PW_DOWN, TEE_EFFECT_PW_DOWN},
  { DivInstrumentFZT::TE_EFFECT_PW_UP, TEE_EFFECT_PW_UP},
  { DivInstrumentFZT::TE_EFFECT_SET_CUTOFF, TEE_EFFECT_SET_CUTOFF},
  { DivInstrumentFZT::TE_EFFECT_VOLUME_FADE, TEE_EFFECT_VOLUME_FADE},
  { DivInstrumentFZT::TE_EFFECT_SET_WAVEFORM, TEE_EFFECT_SET_WAVEFORM},
  { DivInstrumentFZT::TE_EFFECT_SET_VOLUME, TEE_EFFECT_SET_VOLUME},
  { DivInstrumentFZT::TE_EFFECT_EXT_TOGGLE_FILTER, TEE_EFFECT_EXT_TOGGLE_FILTER},
  { DivInstrumentFZT::TE_EFFECT_EXT_PORTA_UP, TEE_EFFECT_EXT_PORTA_UP},
  { DivInstrumentFZT::TE_EFFECT_EXT_PORTA_DN, TEE_EFFECT_EXT_PORTA_DN},
  { DivInstrumentFZT::TE_EFFECT_EXT_FILTER_MODE, TEE_EFFECT_EXT_FILTER_MODE},
  { -1, TEE_EFFECT_EXT_PATTERN_LOOP }, //does not exist in Furnace-B (yet?)
  { DivInstrumentFZT::TE_EFFECT_EXT_RETRIGGER, TEE_EFFECT_EXT_RETRIGGER},
  { DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_DOWN, TEE_EFFECT_EXT_FINE_VOLUME_DOWN},
  { DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_UP, TEE_EFFECT_EXT_FINE_VOLUME_UP},
  { DivInstrumentFZT::TE_EFFECT_EXT_NOTE_CUT, TEE_EFFECT_EXT_NOTE_CUT},
  { DivInstrumentFZT::TE_EFFECT_EXT_PHASE_RESET, TEE_EFFECT_EXT_PHASE_RESET},
  { DivInstrumentFZT::TE_EFFECT_SET_SPEED_PROG_PERIOD, TEE_EFFECT_SET_SPEED_PROG_PERIOD},
  { DivInstrumentFZT::TE_EFFECT_CUTOFF_UP, TEE_EFFECT_CUTOFF_UP},
  { DivInstrumentFZT::TE_EFFECT_CUTOFF_DOWN, TEE_EFFECT_CUTOFF_DOWN},
  { DivInstrumentFZT::TE_EFFECT_SET_RESONANCE, TEE_EFFECT_SET_RESONANCE},
  { DivInstrumentFZT::TE_EFFECT_RESONANCE_UP, TEE_EFFECT_RESONANCE_UP},
  { DivInstrumentFZT::TE_EFFECT_RESONANCE_DOWN, TEE_EFFECT_RESONANCE_DOWN},
  { DivInstrumentFZT::TE_EFFECT_SET_ATTACK, TEE_EFFECT_SET_ATTACK},
  { DivInstrumentFZT::TE_EFFECT_SET_DECAY, TEE_EFFECT_SET_DECAY},
  { DivInstrumentFZT::TE_EFFECT_SET_SUSTAIN, TEE_EFFECT_SET_SUSTAIN},
  { DivInstrumentFZT::TE_EFFECT_SET_RELEASE, TEE_EFFECT_SET_RELEASE},
  { DivInstrumentFZT::TE_EFFECT_SET_RING_MOD_SRC, TEE_EFFECT_SET_RING_MOD_SRC},
  { DivInstrumentFZT::TE_EFFECT_SET_HARD_SYNC_SRC, TEE_EFFECT_SET_HARD_SYNC_SRC},
  { DivInstrumentFZT::TE_EFFECT_PORTA_UP_SEMITONE, TEE_EFFECT_PORTA_UP_SEMITONE},
  { DivInstrumentFZT::TE_EFFECT_PORTA_DOWN_SEMITONE, TEE_EFFECT_PORTA_DOWN_SEMITONE},
  { DivInstrumentFZT::TE_EFFECT_PITCH, TEE_EFFECT_PITCH},
  { DivInstrumentFZT::TE_EFFECT_ARPEGGIO_ABS, TEE_EFFECT_ARPEGGIO_ABS},
  { DivInstrumentFZT::TE_EFFECT_TRIGGER_RELEASE, TEE_EFFECT_TRIGGER_RELEASE},
  { DivInstrumentFZT::TE_PROGRAM_LOOP_BEGIN, TEE_PROGRAM_LOOP_BEGIN},
  { DivInstrumentFZT::TE_PROGRAM_LOOP_END, TEE_PROGRAM_LOOP_END},
  { DivInstrumentFZT::TE_PROGRAM_JUMP, TEE_PROGRAM_JUMP},
  { DivInstrumentFZT::TE_PROGRAM_NOP, TEE_PROGRAM_NOP},
  { DivInstrumentFZT::TE_PROGRAM_END, TEE_PROGRAM_END},
  {-1, -1},
};

typedef struct 
{
    uint8_t note; // MSB is used for instrument number MSB
    uint8_t inst_vol; // high nibble + MSB from note = instrument, low nibble = 4 volume LSBs
    uint16_t command; // MSB used as volume MSB
} TrackerSongPatternStep;

typedef struct
{
    TrackerSongPatternStep step[256];
} TrackerSongPattern;

int search_pattern(int** array, int cur_index)
{
    for(int i = cur_index - 1; i >= 0; i--)
    {
        if(array[cur_index][0] == array[i][0])
        {
            return array[i][1];
        }
    }

    return -1;
}

uint8_t tracker_engine_get_note(TrackerSongPatternStep* step) {
    return (step->note & 0x7f);
}

uint8_t tracker_engine_get_instrument(TrackerSongPatternStep* step) {
    return ((step->note & 0x80) >> 3) | ((step->inst_vol & 0xf0) >> 4);
}

uint8_t tracker_engine_get_volume(TrackerSongPatternStep* step) {
    return (step->inst_vol & 0xf) | ((step->command & 0x8000) >> 11);
}

uint16_t tracker_engine_get_command(TrackerSongPatternStep* step) {
    return (step->command & 0x7fff);
}

void set_note(TrackerSongPatternStep* step, uint8_t note) {
    step->note &= 0x80;
    step->note |= (note & 0x7f);
}

void set_instrument(TrackerSongPatternStep* step, uint8_t inst) {
    step->note &= 0x7f;
    step->inst_vol &= 0x0f;

    step->note |= ((inst & 0x10) << 3);
    step->inst_vol |= ((inst & 0xf) << 4);
}

void set_volume(TrackerSongPatternStep* step, uint8_t vol) {
    step->command &= 0x7fff;
    step->inst_vol &= 0xf0;

    step->command |= ((vol & 0x10) << 11);
    step->inst_vol |= (vol & 0xf);
}

void set_command(TrackerSongPatternStep* step, uint16_t command) {
    step->command &= 0x8000;
    step->command |= command & (0x7fff);
}

#define DELETE_ORDERS \
for(int i = 0; i < FZT_NUM_CHANNELS; i++) \
{ \
    for(int j = 0; j < 256; j++) \
    { \
        delete orders[i][j]; \
    } \
 \
    delete orders[i]; \
}

bool DivEngine::loadFZT(unsigned char* file, size_t len)
{
    SafeReader reader=SafeReader(file,len);
    warnings="";

    logV("loading FZT module...");

    int** orders[FZT_NUM_CHANNELS];

    for(int i = 0; i < FZT_NUM_CHANNELS; i++)
    {
        orders[i] = new int*[256];

        for(int j = 0; j < 256; j++)
        {
            orders[i][j] = new int[2];

            orders[i][j][0] = -1;
            orders[i][j][1] = -1;
        }
    }

    try 
    {
        DivSong ds;

        ds.systemLen = 1;
        ds.system[0] = DIV_SYSTEM_FZT;

        reader.seek(8,SEEK_SET);

        unsigned char version = reader.readC();
        
        if(version > TRACKER_ENGINE_VERSION)
        {
            lastError=_LE("incompatible version");
            DELETE_ORDERS
            delete[] file;
            return false;
        }

        ds.name = reader.readString(17);

        unsigned char loop_start = reader.readC();
        unsigned char loop_end = reader.readC();
        unsigned short pattern_length = reader.readS();

        if(pattern_length > 0xff)
        {
            lastError=_LE("invalid pattern length!");
            DELETE_ORDERS
            delete[] file;
            return false;
        }

        DivSubSong* sub_song = ds.subsong[0];
        sub_song->patLen = pattern_length;

        if(loop_start >= loop_end)
        {
            lastError=_LE("invalid loop start and loop end!");
            DELETE_ORDERS
            delete[] file;
            return false;
        }

        sub_song->speeds.val[0] = reader.readC();
        sub_song->hz = reader.readC();

        unsigned short num_sequence_steps = reader.readS();

        if(num_sequence_steps > 256)
        {
            lastError=_LE("invalid orders length!");
            DELETE_ORDERS
            delete[] file;
            return false;
        }

        sub_song->ordersLen = num_sequence_steps;

        for(int i = 0; i < num_sequence_steps; i++)
        {
            for(int j = 0; j < FZT_NUM_CHANNELS; j++)
            {
                orders[j][i][0] = reader.readC();
            }

            //logV("%02X %02X %02X %02X", orders[0][i][0], orders[1][i][0], orders[2][i][0], orders[3][i][0]);
        }

        int max_pat[FZT_NUM_CHANNELS];

        for(int i = 0; i < FZT_NUM_CHANNELS; i++) //fzt has global pattern indices while Furnace ones are per-channel
        {
            int pat_count = 0;

            for(int j = 0; j < num_sequence_steps; j++)
            {
                int y = 0;
                
                if(j > 0)
                {
                    y = search_pattern((int**)orders[i], j);
                }
                else
                {
                    y = -1;
                }

                orders[i][j][1] = (y == -1 ? pat_count : y);

                sub_song->orders.ord[i][j] = orders[i][j][1];

                if(y == -1)
                {
                    pat_count++;
                }
            }

            max_pat[i] = pat_count;
        }

        unsigned char num_patterns = reader.readC();

        TrackerSongPattern patterns[256];
        memset(patterns, 0xff, sizeof(TrackerSongPattern) * 256);

        for(int i = 0; i < 256; i++)
        {
            for(int j = 0; j < 256; j++)
            {
                set_command(&patterns[i].step[j], 0);
            }
        }

        for(int i = 0; i < num_patterns; i++)
        {
            logV("pat %d", i);
            for(int j = 0; j < pattern_length; j++)
            {
                patterns[i].step[j].note = reader.readC();
                patterns[i].step[j].inst_vol = reader.readC();
                patterns[i].step[j].command = reader.readS();

                if(i == 0 || i == 1 || i == 2) logV("%02X %02X %04X", patterns[i].step[j].note, patterns[i].step[j].inst_vol, patterns[i].step[j].command);
                //logV("%02X %02X %02X %04X", tracker_engine_get_note(&patterns[i].step[j]), tracker_engine_get_instrument(&patterns[i].step[j]), tracker_engine_get_volume(&patterns[i].step[j]), tracker_engine_get_command(&patterns[i].step[j]));
            }
        }

        for(int i = 0; i < FZT_NUM_CHANNELS; i++)
        {
            for(int j = 0; j < num_sequence_steps; j++)
            {
                DivPattern* pat = sub_song->pat[i].getPattern(sub_song->orders.ord[i][j], true);

                int fzt_pat_index = orders[i][j][0];

                for(int row = 0; row < pattern_length; row++)
                {
                    TrackerSongPatternStep* step = &patterns[fzt_pat_index].step[row];

                    int note = tracker_engine_get_note(step);

                    if(note != MUS_NOTE_NONE_FZT && note != MUS_NOTE_CUT_FZT && note != MUS_NOTE_RELEASE_FZT)
                    {
                        pat->data[row][0]=((note)%12);
                        pat->data[row][1]=(note)/12;

                        if(note % 12 == 0)
                        {
                            pat->data[row][0] = 12; //what the fuck?
                            pat->data[row][1]--;
                        }
                    }
                }
            }
        }

        if (active) quitDispatch();
        BUSY_BEGIN_SOFT;
        saveLock.lock();
        song.unload();
        song=ds;
        changeSong(0);
        recalcChans();
        saveLock.unlock();
        BUSY_END;
        if (active) 
        {
            initDispatch();
            BUSY_BEGIN;
            renderSamples();
            reset();
            BUSY_END;
        }
    } 
    catch (EndOfFileException& e) 
    {
        lastError=_LE("incomplete file");
    }

    DELETE_ORDERS
    delete[] file;
    return true;
}

SafeWriter* DivEngine::saveFZT()
{
    saveLock.lock();

    SafeWriter* w=new SafeWriter;
    w->init();

    //export...
    logV("exporting FZT module...");

    saveLock.unlock();
    return w;
}