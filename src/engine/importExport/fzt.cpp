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

#define FZT_SONG_NAME_LEN 17
#define FZT_INST_NAME_LEN (FZT_SONG_NAME_LEN - 3)

#define FZT_SONG_MAX_PATTERNS 256

#define WARNING_ABOUT_ONE_DIGIT_COMMAND(eff) \
if(pat->data[row][4] == eff && pat->data[row][5] > 0xf && !found_invalid_effects[eff]) \
{ \
    warnings += fmt::sprintf(_LE("You are using %02Xxx effect with param higher than 0xf (channel %d, pattern %d, row %d).\nThe effect param will be capped at 0xf.\n\n"), eff, i, j, row); \
    found_invalid_effects[eff] = true; \
}

#define WARNING_ABOUT_TWO_DIGIT_COMMAND(eff) \
if(pat->data[row][4] == eff && !found_invalid_effects[eff]) \
{ \
    warnings += fmt::sprintf(_LE("You are using %02Xxx effect which is not supported by FZT format (channel %d, pattern %d, row %d).\n\n"), eff, i, j, row); \
    found_invalid_effects[eff] = true; \
}

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
  { 0x0300, TEE_EFFECT_SLIDE},
  { DivInstrumentFZT::TE_EFFECT_VIBRATO, TEE_EFFECT_VIBRATO},
  { DivInstrumentFZT::TE_EFFECT_PWM, TEE_EFFECT_PWM},
  { DivInstrumentFZT::TE_EFFECT_SET_PW, TEE_EFFECT_SET_PW},
  { DivInstrumentFZT::TE_EFFECT_PW_DOWN, TEE_EFFECT_PW_DOWN},
  { DivInstrumentFZT::TE_EFFECT_PW_UP, TEE_EFFECT_PW_UP},
  { DivInstrumentFZT::TE_EFFECT_SET_CUTOFF, TEE_EFFECT_SET_CUTOFF},
  { DivInstrumentFZT::TE_EFFECT_VOLUME_FADE, TEE_EFFECT_VOLUME_FADE},
  { DivInstrumentFZT::TE_EFFECT_SET_WAVEFORM, TEE_EFFECT_SET_WAVEFORM},
  { DivInstrumentFZT::TE_EFFECT_SET_VOLUME, TEE_EFFECT_SET_VOLUME},
  { 0x0d00, TEE_EFFECT_SKIP_PATTERN},
  { DivInstrumentFZT::TE_EFFECT_EXT_TOGGLE_FILTER, TEE_EFFECT_EXT_TOGGLE_FILTER},
  { DivInstrumentFZT::TE_EFFECT_EXT_PORTA_UP, TEE_EFFECT_EXT_PORTA_UP},
  { DivInstrumentFZT::TE_EFFECT_EXT_PORTA_DN, TEE_EFFECT_EXT_PORTA_DN},
  { DivInstrumentFZT::TE_EFFECT_EXT_FILTER_MODE, TEE_EFFECT_EXT_FILTER_MODE},
  { -1, TEE_EFFECT_EXT_PATTERN_LOOP }, //does not exist in Furnace-B (yet?)
  { DivInstrumentFZT::TE_EFFECT_EXT_RETRIGGER, TEE_EFFECT_EXT_RETRIGGER},
  { DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_DOWN, TEE_EFFECT_EXT_FINE_VOLUME_DOWN},
  { DivInstrumentFZT::TE_EFFECT_EXT_FINE_VOLUME_UP, TEE_EFFECT_EXT_FINE_VOLUME_UP},
  { DivInstrumentFZT::TE_EFFECT_EXT_NOTE_CUT, TEE_EFFECT_EXT_NOTE_CUT},
  { 0xED00, TEE_EFFECT_EXT_NOTE_DELAY},
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
  { 0xEA00, TEE_EFFECT_LEGATO},
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

int convert_fzt_eff_to_furnace(uint16_t fzt_eff, bool mask_value)
{
    uint8_t eff_val_hex2 = fzt_eff & 0xff;
    uint8_t eff_val_hex1 = fzt_eff & 0xf;

    int index = 0;

    if(fzt_eff == 0) return -1;

    while(fzt_commands_map_real[index][0] != -1 || fzt_commands_map_real[index][1] != -1)
    {
        if((fzt_eff & 0x7ff0) == fzt_commands_map_real[index][1] && (fzt_eff & 0x7fff) >= TEE_EFFECT_EXT_TOGGLE_FILTER && (fzt_eff & 0x7fff) < TEE_EFFECT_SET_SPEED_PROG_PERIOD)
        {
            return fzt_commands_map_real[index][0] | (mask_value ? 0 : eff_val_hex1);
        }
        if((fzt_eff & 0x7f00) == fzt_commands_map_real[index][1] && ((fzt_eff & 0x7fff) < TEE_EFFECT_EXT_TOGGLE_FILTER || (fzt_eff & 0x7fff) >= TEE_EFFECT_SET_SPEED_PROG_PERIOD))
        {
            return fzt_commands_map_real[index][0] | (mask_value ? 0 : eff_val_hex2);
        }
        if((fzt_eff & 0x7fff) == TEE_PROGRAM_NOP)
        {
            return DivInstrumentFZT::TE_PROGRAM_NOP;
        }
        if((fzt_eff & 0x7fff) == TEE_PROGRAM_END)
        {
            return DivInstrumentFZT::TE_PROGRAM_END;
        }

        index++;
    }

    return -1;
}

bool is_0_f_fzt_command(uint16_t command)
{
    int index = 0;

    if (command == 0) return false;

    while (fzt_commands_map_real[index][0] != -1 || fzt_commands_map_real[index][1] != -1)
    {
        if ((command & 0x7fff) >= TEE_EFFECT_EXT_TOGGLE_FILTER && (command & 0x7fff) < TEE_EFFECT_SET_SPEED_PROG_PERIOD)
        {
            return true;
        }

        index++;
    }

    return false;
}

uint16_t convert_furnace_eff_to_fzt(uint16_t fur_eff, bool mask_value)
{
    uint8_t eff_val_hex2 = fur_eff & 0xff;
    uint8_t eff_val_hex1 = MIN(0xf, (fur_eff & 0xff));

    int index = 0;

    if (fur_eff == 0) return 0;

    while(fzt_commands_map_real[index][0] != -1 || fzt_commands_map_real[index][1] != -1)
    {
        if(fur_eff == DivInstrumentFZT::TE_PROGRAM_NOP)
        {
            return TEE_PROGRAM_NOP;
        }
        if(fur_eff == DivInstrumentFZT::TE_PROGRAM_END)
        {
            return TEE_PROGRAM_END;
        }
        if((fur_eff & 0xff00) == fzt_commands_map_real[index][0])
        {
            return fzt_commands_map_real[index][1] | (mask_value ? 0 : (is_0_f_fzt_command(fzt_commands_map_real[index][1]) ? eff_val_hex1 : eff_val_hex2));
        }

        index++;
    }

    return 0;
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

        if(loop_start >= loop_end && loop_end != 0)
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
            //logV("pat %d", i);
            for(int j = 0; j < pattern_length; j++)
            {
                patterns[i].step[j].note = reader.readC();
                patterns[i].step[j].inst_vol = reader.readC();
                patterns[i].step[j].command = reader.readS();

                //if(i == 0 || i == 1 || i == 2) logV("%02X %02X %04X", patterns[i].step[j].note, patterns[i].step[j].inst_vol, patterns[i].step[j].command);
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
                    if(note == MUS_NOTE_CUT_FZT)
                    {
                        pat->data[row][0] = 100;
                    }
                    if(note == MUS_NOTE_RELEASE_FZT)
                    {
                        pat->data[row][0] = 101;
                    }

                    int inst = tracker_engine_get_instrument(step);

                    if(inst != MUS_NOTE_INSTRUMENT_NONE_FZT)
                    {
                        pat->data[row][2] = inst;
                    }

                    int vol = tracker_engine_get_volume(step);

                    if(vol != MUS_NOTE_VOLUME_NONE_FZT)
                    {
                        pat->data[row][3] = (short)((float)vol * 255.0f / (float)(MUS_NOTE_VOLUME_NONE_FZT - 1));
                    }

                    int effect = convert_fzt_eff_to_furnace(tracker_engine_get_command(step), false);

                    if(effect != -1)
                    {
                        pat->data[row][4] = effect >> 8;
                        pat->data[row][5] = effect & 0xff;
                    }
                }
            }
        }

        unsigned char num_instruments = reader.readC();

        if(num_instruments > 31)
        {
            lastError=_LE("too many instruments!");
            DELETE_ORDERS
            delete[] file;
            return false;
        }

        for(int i = 0; i < num_instruments; i++)
        {
            DivInstrument* ins = new DivInstrument;
            ins->type = DIV_INS_FZT;

            for(int j = 0; j < FZT_INST_PROG_LEN; j++)
            {
                ins->fzt.program[j].cmd = DivInstrumentFZT::TE_PROGRAM_NOP;
                ins->fzt.program[j].val = 0;
                ins->fzt.program[j].unite = false;
            }

            ins->name = reader.readString(14);

            ins->fzt.waveform = reader.readC();
            ins->fzt.flags = reader.readS();
            ins->fzt.sound_engine_flags = reader.readS();

            ins->fzt.base_note = reader.readC();
            ins->fzt.finetune = (signed char)reader.readC();

            ins->fzt.slide_speed = reader.readC();

            ins->fzt.adsr.a = reader.readC();
            ins->fzt.adsr.d = reader.readC();
            ins->fzt.adsr.s = reader.readC();
            ins->fzt.adsr.r = reader.readC();
            ins->fzt.adsr.volume = reader.readC();

            ins->fzt.pw = reader.readC();

            if(ins->fzt.sound_engine_flags & SE_ENABLE_RING_MOD)
            {
                ins->fzt.ring_mod = reader.readC();
            }

            if(ins->fzt.sound_engine_flags & SE_ENABLE_HARD_SYNC)
            {
                ins->fzt.hard_sync = reader.readC();
            }

            unsigned char progsteps = reader.readC();

            if(progsteps > FZT_INST_PROG_LEN)
            {
                lastError=_LE("instrument program is too long!");
                DELETE_ORDERS
                delete[] file;
                return false;
            }

            if(progsteps > 0)
            {
                for(int j = 0; j < progsteps; j++)
                {
                    uint16_t command = reader.readS();

                    uint16_t fur_command = convert_fzt_eff_to_furnace(command, true);
                    
                    ins->fzt.program[j].cmd = fur_command;

                    if((command & 0x7fff) == 0)
                    {
                        ins->fzt.program[j].cmd = DivInstrumentFZT::TE_EFFECT_ARPEGGIO;
                    }

                    if(is_0_f_fzt_command(command))
                    {
                        ins->fzt.program[j].val = command & 0xf;
                    }
                    else
                    {
                        ins->fzt.program[j].val = command & 0xff;
                    }

                    if(command & 0x8000)
                    {
                        ins->fzt.program[j].unite = true;
                    }
                }
            }

            ins->fzt.program_period = reader.readC();

            if(ins->fzt.flags & TE_ENABLE_VIBRATO)
            {
                ins->fzt.vibrato_speed = reader.readC();
                ins->fzt.vibrato_depth = reader.readC();
                ins->fzt.vibrato_delay = reader.readC();
            }

            if(ins->fzt.flags & TE_ENABLE_PWM)
            {
                ins->fzt.pwm_speed = reader.readC();
                ins->fzt.pwm_depth = reader.readC();
                ins->fzt.pwm_delay = reader.readC();
            }

            if(ins->fzt.sound_engine_flags & SE_ENABLE_FILTER)
            {
                ins->fzt.filter_cutoff = reader.readC();
                ins->fzt.filter_resonance = reader.readC();
                ins->fzt.filter_type = reader.readC();
            }

            ds.ins.push_back(ins);
        }

        ds.insLen = ds.ins.size();

        if(loop_start != loop_end && loop_end > 0)
        {
            bool placed_0bxx = false;

            for(int i = 0; i < FZT_NUM_CHANNELS; i++) //try to find place for 0bxx effect in first effect column of some channel
            {
                DivPattern* pat = sub_song->pat[i].getPattern(sub_song->orders.ord[i][num_sequence_steps - 1], true);

                if(pat->data[pattern_length - 1][4] == -1 && pat->data[pattern_length - 1][5] == -1)
                {
                    pat->data[pattern_length - 1][4] = 0x0b;
                    pat->data[pattern_length - 1][5] = loop_start;

                    placed_0bxx = true;
                    break;
                }
            }
            if(!placed_0bxx) //search other effect columns!
            {
                for(int i = 0; i < FZT_NUM_CHANNELS; i++) //try to find place for 0bxx effect in first effect column of some channel
                {
                    DivPattern* pat = sub_song->pat[i].getPattern(sub_song->orders.ord[i][num_sequence_steps - 1], true);

                    for(int j = 1; j < DIV_MAX_EFFECTS; j++)
                    {
                        if(pat->data[pattern_length - 1][4 + j*2] == -1 && pat->data[pattern_length - 1][5 + j*2] == -1)
                        {
                            pat->data[pattern_length - 1][4 + j*2] = 0x0b;
                            pat->data[pattern_length - 1][5 + j*2] = loop_start;

                            placed_0bxx = true;
                            break;
                        }
                    }
                }
            }
            if(!placed_0bxx) //strange but well...
            {
                logW("couldn't place 0Bxx command to make a loop point");
                addWarning(_LE("couldn't place 0Bxx command to make a loop point"));
            }
        }

        ds.is_prohibited_to_save = true;

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

bool DivEngine::exportFZTFindErrors()
{
    if(song.systemLen != 1)
    {
        lastError += _LE("song contains more than one system.");
        return true;
    }

    if(song.system[0] != DIV_SYSTEM_FZT)
    {
        lastError += _LE("system is not FZT sound source.");
        return true;
    }

    if((int)song.subsong.size() == 0)
    {
        lastError += _LE("you have no subsongs in the module.");
        return true;
    }

    if((int)song.insLen == 0)
    {
        lastError += _LE("you must have at least one instrument in the song.");
        return true;
    }

    return false;
}

typedef struct
{
    uint8_t channel;
    uint8_t pattern;
} fzt_pat;

typedef struct
{
    std::vector<fzt_pat> patterns;
} fzt_pat_list;

bool DivEngine::cmp_pats(DivPattern* pat1, DivPattern* pat2, int patLen)
{
    for(int i = 0; i < patLen; i++)
    {
        for(int j = 0; j < DIV_MAX_COLS; j++)
        {
            if(pat1->data[i][j] != pat2->data[i][j])
            {
                return true;
            }
        }
    }

    return false;
}

bool DivEngine::pattern_unique(int chan, int order)
{
    DivSubSong* sub_song = song.subsong[0];
    DivPattern* pat = sub_song->pat[chan].getPattern(sub_song->orders.ord[chan][order], true);

    for(int j = 0; j < order; j++)
    {
        for(int i = 0; i < ((j < order) ? FZT_NUM_CHANNELS : (chan - 1)); i++)
        {
            DivPattern* pat_curr = sub_song->pat[i].getPattern(sub_song->orders.ord[i][j], true);

            if(!cmp_pats(pat_curr, pat, sub_song->patLen))
            {
                return false;
            }
        }
    }

    return true;
}

int DivEngine::exportFZTFindWarnings(int* loop_start, int* loop_end, void* fuck_you)
{
    fzt_pat_list* fzt_patterns = (fzt_pat_list*)fuck_you;

    if((int)song.name.length() > 17)
    {
        warnings += fmt::sprintf(_LE("song name is too long. Only first %d characters will be written.\n\n"), FZT_SONG_NAME_LEN);
    }

    DivSubSong* sub_song = song.subsong[0];

    bool found_0b = false;

    for(int i = 0; i < FZT_NUM_CHANNELS && !found_0b; i++)
    {
        for(int j = 0; j < sub_song->ordersLen && !found_0b; j++)
        {
            DivPattern* pat = sub_song->pat[i].getPattern(sub_song->orders.ord[i][j], true);

            for(int row = 0; row < sub_song->patLen && !found_0b; row++)
            {
                for(int col = 0; col < DIV_MAX_EFFECTS && !found_0b; col++)
                {
                    if(pat->data[row][4 + col*2] == 0x0b)
                    {
                        if(row != sub_song->patLen - 1)
                        {
                            String temp = fmt::sprintf(_LE("you have 0Bxx command placed not on the last pattern row (channel %d, pattern %d, row %d, effect column %d).\n"
                            "FZT export will try to loop your song as if it was placed on last pattern row.\n\n"), i, j, row, col);
                        }

                        *loop_end = j;
                        *loop_start = pat->data[row][5 + col*2];

                        found_0b = true;
                    }
                }
            }
        }
    }

    if(!found_0b)
    {
        warnings += _LE("There wasn't any 0Bxx command, so your song won't be looped.\n"
        "To make song loop, place 0Bxx command somewhere in the song on the last pattern row.\n\n");
    }

    int current_fzt_pattern = 0;

    for(int j = 0; j < sub_song->ordersLen; j++)
    {
        for(int i = 0; i < FZT_NUM_CHANNELS; i++)
        {
            if(pattern_unique(i, j) && current_fzt_pattern < FZT_SONG_MAX_PATTERNS)
            {
                fzt_patterns[current_fzt_pattern].patterns[0].channel = i;
                fzt_patterns[current_fzt_pattern].patterns[0].pattern = j;
                current_fzt_pattern++;
            }
            else
            {
                //fzt_patterns[current_fzt_pattern].patterns[0].channel = 0xff;
            }
        }
    }

    if(current_fzt_pattern >= FZT_SONG_MAX_PATTERNS)
    {
        warnings += fmt::sprintf(_LE("there are more than %d patterns in the song. only %d patterns will be saved.\n\n"), FZT_SONG_MAX_PATTERNS, FZT_SONG_MAX_PATTERNS);
    }

    if(sub_song->speeds.len > 1 || song.grooves.size() > 0)
    {
        warnings += _LE("you are using two speeds or groove patterns which are not supported in FZT.\nFirst speed will be used.\n\n");
    }

    if(sub_song->virtualTempoD != sub_song->virtualTempoN)
    {
        warnings += _LE("you are using virtual tempo which is not supported in FZT.\nTo stop using virtual tempo, simply make virtual tempo numerator and denominator equal.\nFZT does not support virtual tempo, so the settings will be ignored.\n\n");
    }

    bool rate_too_high = false;
    bool inst_index_out_of_bounds = false;

    if(sub_song->hz > 255.0f)
    {
        rate_too_high = true;
        warnings += _LE("Your song rate is higher than 255 Hz. It will be capped at 255 Hz in FZT file.\n\n");
    }

    for(int i = 0; i < FZT_NUM_CHANNELS && !rate_too_high; i++)
    {
        for(int j = 0; j < sub_song->ordersLen && !rate_too_high; j++)
        {
            DivPattern* pat = sub_song->pat[i].getPattern(sub_song->orders.ord[i][j], true);

            for(int row = 0; row < sub_song->patLen && !rate_too_high; row++)
            {
                for(int col = 0; col < DIV_MAX_EFFECTS && !rate_too_high; col++)
                {
                    if((pat->data[row][4 + col*2] & 0xf0) == 0xc0)
                    {
                        int param = ((pat->data[row][4 + col*2] & 0x0f) << 8) | (pat->data[row][5 + col*2] & 0xff);
                        if(param > 0xff)
                        {
                            rate_too_high = true;
                            warnings += fmt::sprintf(_LE("You are setting engine rate that is higher than 255 Hz (channel %d, pattern %d, row %d, effect column %d).\nThe command(s) will be capped at 255 Hz.\n\n"), i, j, row, col);
                        }
                    }
                }

                if(pat->data[row][2] > MUS_NOTE_INSTRUMENT_NONE_FZT - 1 && !inst_index_out_of_bounds)
                {
                    warnings += fmt::sprintf(_LE("You are using instrument index that is higher than %02X (channel %d, pattern %d, row %d).\nThe index will be capped at %02X.\n\n"), MUS_NOTE_INSTRUMENT_NONE_FZT - 1, i, j, row, MUS_NOTE_INSTRUMENT_NONE_FZT - 1);
                    inst_index_out_of_bounds = true;
                }
            }
        }
    }

    bool found_invalid_effects[256];

    for(int i = 0; i < 256; i++)
    {
        found_invalid_effects[i] = false;
    }

    for(int i = 0; i < FZT_NUM_CHANNELS && !rate_too_high; i++)
    {
        for(int j = 0; j < sub_song->ordersLen && !rate_too_high; j++)
        {
            DivPattern* pat = sub_song->pat[i].getPattern(sub_song->orders.ord[i][j], true);

            for(int row = 0; row < sub_song->patLen && !rate_too_high; row++)
            {
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0x17);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0xf1);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0xf2);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0x18);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0x0c);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0xf3);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0xf4);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0xec);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0xed);
                WARNING_ABOUT_ONE_DIGIT_COMMAND(0x19);

                WARNING_ABOUT_TWO_DIGIT_COMMAND(0x05);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0x06);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0x07);

                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE0);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE1);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE2);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE3);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE4);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE6);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE7);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE8);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xE9);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xEE);

                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xF0);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xF5);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xF6);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xF7);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xF8);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xF9);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xFA);
                WARNING_ABOUT_TWO_DIGIT_COMMAND(0xFC);

                if((pat->data[row][4] == 0xfd || pat->data[row][4] == 0xfe) && (!found_invalid_effects[0xfd] && !found_invalid_effects[0xfe]))
                {
                    warnings += fmt::sprintf(_LE("You are using virtual tempo control effect (channel %d, pattern %d, row %d).\nThe effect is not supported in FZT and will be ignored.\n\n"), i, j, row);
                    found_invalid_effects[0xfd] = true;
                }
            }
        }
    }

    bool found_macro = false;

    for(int i = 0; i < song.insLen && !found_macro; i++)
    {
        for(int j = 0; j < (int)DIV_MACRO_EX20 && !found_macro; j++)
        {
            DivInstrument* ins = getIns(i, DIV_INS_FZT);
            
            if(ins->std.get_macro((DivMacroType)j, false)->len > 0)
            {
                warnings += fmt::sprintf(_LE("You are using macros in instrument %d.\nFZT does not support macros, so they will be ignored.\n\n"), i);
                found_macro = true;
            }
        }
    }

    return current_fzt_pattern;
}

SafeWriter* DivEngine::saveFZT()
{
    saveLock.lock();

    SafeWriter* w=new SafeWriter;
    w->init();

    logV("exporting FZT module...");
    lastError = "";
    warnings = "";

    if(exportFZTFindErrors())
    {
        saveLock.unlock();
        return NULL;
    }

    int loop_start = 0;
    int loop_end = 0;

    fzt_pat_list fzt_patterns[FZT_SONG_MAX_PATTERNS];

    for (int i = 0; i < FZT_SONG_MAX_PATTERNS; i++)
    {
        fzt_patterns[i].patterns.push_back(fzt_pat());
    }

    int num_pats_fzt = exportFZTFindWarnings(&loop_start, &loop_end, (void*)fzt_patterns); //we still try to export but warn user that some things will be not exported or will be exported wrong

    w->writeText(DIV_FZT_MAGIC);
    w->writeC(TRACKER_ENGINE_VERSION);

    String name = song.name;
    for (auto & c: name) c = toupper(c);

    if (name.length() > 0)
    {
        name.erase(name.begin() + MIN(FZT_SONG_NAME_LEN, (int)name.length()), name.end());
    }

    for (int i = 0; i < FZT_SONG_NAME_LEN; i++)
    {
        if (i < (int)name.length())
        {
            w->writeC(name[i]);
        }
        else
        {
            w->writeC(0);
        }
    }

    DivSubSong* sub_song = song.subsong[0];

    w->writeC(loop_start);
    w->writeC(loop_end);
    w->writeS(sub_song->patLen);

    w->writeC(sub_song->speeds.val[0]);
    w->writeC((unsigned char)MIN((int)sub_song->hz, (int)255));

    w->writeS(sub_song->ordersLen);

    for(int j = 0; j < sub_song->ordersLen; j++)
    {
        //String ssss = "";

        for(int i = 0; i < FZT_NUM_CHANNELS; i++)
        {
            for(int pat = 0; pat < num_pats_fzt; pat++)
            {
                DivPattern* patt = sub_song->pat[i].getPattern(sub_song->orders.ord[i][j], false);

                if(fzt_patterns[pat].patterns[0].channel == i && fzt_patterns[pat].patterns[0].pattern == j) //new pattern
                {
                    w->writeC(pat);
                    //ssss += fmt::sprintf(" %d %02X |", i, pat);
                    goto finish;
                }
                else //a copy of that pattern exists "before" the current encounter
                {
                    for(int j1 = 0; j1 <= j; j1++)
                    {
                        for(int i1 = 0; i1 < (j1 == j ? i : FZT_NUM_CHANNELS); i1++)
                        {
                            DivPattern* kill_me = sub_song->pat[i1].getPattern(sub_song->orders.ord[i1][j1], false);

                            if(!cmp_pats(kill_me, patt, sub_song->patLen)) //patterns are equal
                            {
                                for(int pat1 = 0; pat1 < num_pats_fzt; pat1++)
                                {
                                    if(fzt_patterns[pat1].patterns[0].channel == i1 && fzt_patterns[pat1].patterns[0].pattern == j1)
                                    {
                                        w->writeC(pat1);
                                        //ssss += fmt::sprintf(" %d %02X |", i, pat1);
                                        goto finish;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            finish:;
        }

        //logV(ssss.c_str());
    }

    w->writeC(num_pats_fzt);

    for(int i = 0; i < num_pats_fzt; i++)
    {
        DivPattern* pat = sub_song->pat[fzt_patterns[i].patterns[0].channel].getPattern(sub_song->orders.ord[fzt_patterns[i].patterns[0].channel][fzt_patterns[i].patterns[0].pattern], false);

        for(int row = 0; row < sub_song->patLen; row++)
        {
            TrackerSongPatternStep step;

            set_note(&step, MUS_NOTE_NONE_FZT);
            set_instrument(&step, MUS_NOTE_INSTRUMENT_NONE_FZT);
            set_volume(&step, MUS_NOTE_VOLUME_NONE_FZT);
            set_command(&step, 0);
            
            if(pat->data[row][0] > 0 && pat->data[row][1] > -1)
            {
                if(pat->data[row][0] == 100)
                {
                    set_note(&step, MUS_NOTE_CUT_FZT);
                }
                else if(pat->data[row][0] == 101)
                {
                    set_note(&step, MUS_NOTE_RELEASE_FZT);
                }
                else if(pat->data[row][0] < 20)
                {
                    int note = pat->data[row][0];
                    int octave = pat->data[row][1];

                    if(note == 12)
                    {
                        note = 0;
                        octave++;
                    }

                    set_note(&step, note + octave * 12);
                }
            }
            if(pat->data[row][2] > -1)
            {
                set_instrument(&step, MIN(MUS_NOTE_INSTRUMENT_NONE_FZT - 1, pat->data[row][2]));
            }
            if(pat->data[row][3] > -1)
            {
                set_volume(&step, (uint8_t)((float)pat->data[row][3] * (float)(MUS_NOTE_VOLUME_NONE_FZT - 1) / 255.0f));
            }
            
            // "what is written below ~~can~~ **MUST** be used against me in programming crimes court" - LTVA

            uint16_t command = convert_furnace_eff_to_fzt((MAX(0, pat->data[row][4]) << 8) | MAX(0, pat->data[row][5]), false);
            set_command(&step, command);

            //logV("pat %d step %d command %04X", i, row, command);

            w->writeC(step.note);
            w->writeC(step.inst_vol);
            w->writeS(step.command);
        }
    }

    w->writeC(MIN(MUS_NOTE_INSTRUMENT_NONE_FZT, song.insLen));

    for(int i = 0; i < MIN(MUS_NOTE_INSTRUMENT_NONE_FZT, song.insLen); i++)
    {
        DivInstrument* ins = getIns(i,DIV_INS_FZT);

        String name = ins->name;
        for (auto & c: name) c = toupper(c);

        if (name.length() > 0)
        {
            name.erase(name.begin() + MIN(FZT_INST_NAME_LEN, (int)name.length()), name.end());
        }

        for (int i = 0; i < FZT_INST_NAME_LEN; i++)
        {
            if (i < (int)name.length())
            {
                w->writeC(name[i]);
            }
            else
            {
                w->writeC(0);
            }
        }

        w->writeC(ins->fzt.waveform);
        w->writeS(ins->fzt.flags);
        w->writeS(ins->fzt.sound_engine_flags);

        w->writeC(ins->fzt.base_note);
        w->writeC(ins->fzt.finetune);

        w->writeC(ins->fzt.slide_speed);

        w->writeC(ins->fzt.adsr.a);
        w->writeC(ins->fzt.adsr.d);
        w->writeC(ins->fzt.adsr.s);
        w->writeC(ins->fzt.adsr.r);
        w->writeC(ins->fzt.adsr.volume);

        w->writeC(ins->fzt.pw);

        if(ins->fzt.sound_engine_flags & SE_ENABLE_RING_MOD)
        {
            w->writeC(ins->fzt.ring_mod);
        }

        if(ins->fzt.sound_engine_flags & SE_ENABLE_HARD_SYNC)
        {
            w->writeC(ins->fzt.hard_sync);
        }

        int progsteps = 0;

        for(int j = 0; j < FZT_INST_PROG_LEN; j++)
        {
            if(ins->fzt.program[j].cmd != DivInstrumentFZT::TE_PROGRAM_NOP)
            {
                progsteps = j + 1;
            }
        }

        w->writeC(progsteps);

        if(progsteps > 0)
        {
            for(int j = 0; j < progsteps; j++)
            {
                uint16_t command = convert_furnace_eff_to_fzt(ins->fzt.program[j].cmd, true) | ins->fzt.program[j].val;

                if(ins->fzt.program[j].unite) command |= 0x8000;

                w->writeS(command);
            }
        }

        w->writeC(ins->fzt.program_period);

        if(ins->fzt.flags & TE_ENABLE_VIBRATO)
        {
            w->writeC(ins->fzt.vibrato_speed);
            w->writeC(ins->fzt.vibrato_depth);
            w->writeC(ins->fzt.vibrato_delay);
        }

        if(ins->fzt.flags & TE_ENABLE_PWM)
        {
            w->writeC(ins->fzt.pwm_speed);
            w->writeC(ins->fzt.pwm_depth);
            w->writeC(ins->fzt.pwm_delay);
        }

        if(ins->fzt.sound_engine_flags & SE_ENABLE_FILTER)
        {
            w->writeC(ins->fzt.filter_cutoff);
            w->writeC(ins->fzt.filter_resonance);
            w->writeC(ins->fzt.filter_type);
        }
    }

    saveLock.unlock();
    return w;
}