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

#ifndef _FZT_H
#define _FZT_H

#include "../dispatch.h"
#include "../../fixedQueue.h"
#include "sound/fzt.h"

#define FZT_NUM_CHANNELS 4

#define MUS_NOTE_VOLUME_NONE 255

typedef enum {
    TEC_PLAYING = 1,
    TEC_PROGRAM_RUNNING = 2,
    TEC_DISABLED = 4,
} TrackerEngineChannelFlags;

typedef struct {
    unsigned short flags;

    unsigned char channel_flags;

    int note, target_note, last_note, fixed_note;
    signed short finetune_note;
    int arpeggio_note;

    unsigned char volume;

    unsigned char program_counter, program_tick, program_loop, program_period;

    unsigned short filter_cutoff, filter_resonance;
    unsigned char filter_type;

    unsigned char vibrato_speed, vibrato_depth, vibrato_delay;
    unsigned char pwm_speed, pwm_depth, pwm_delay;

    unsigned int vibrato_position, pwm_position; // basically accumulators

    unsigned char extarp1, extarp2;

    int pw;

    unsigned char slide_speed;

    unsigned char fur_volume;

    int pitch_note;
} TrackerEngineChannel;

class DivPlatformFZT: public DivDispatch {
  public:
    struct Channel: public SharedChannel<int> {
      int fzt_note;
      int fzt_octave;
      Channel():
        SharedChannel<int>(255),
        fzt_note(0),
        fzt_octave(0) {}
    };
    Channel chan[FZT_NUM_CHANNELS];
    TrackerEngineChannel fztChan[FZT_NUM_CHANNELS];
    bool isMuted[FZT_NUM_CHANNELS];
    DivDispatchOscBuffer* oscBuf[FZT_NUM_CHANNELS];
    struct QueuedWrite {
        unsigned char addr;
        unsigned char val;
        QueuedWrite(): addr(0), val(0) {}
        QueuedWrite(unsigned char a, unsigned char v): addr(a), val(v) {}
    };
    FixedQueue<QueuedWrite,512> writes;

    SoundEngine* sound_engine;
    int current_tick;

    void acquire(short** buf, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    void reset();
    void forceIns();
    void tick(bool sysTick=true);

    void tracker_engine_trigger_instrument_internal(int chan, DivInstrument* pinst, int note);
    void tracker_engine_set_note(int chan, int note, bool update_note);
    void tracker_engine_execute_volume(int vol, int chan);
    void tracker_engine_execute_track_command(int chan, bool first_tick, int opcode);
    void do_command(int opcode, int channel, int tick, bool from_program);
    void tracker_engine_execute_program_tick(int chan, int advance);
    void tracker_engine_advance_channel(int chan);
    void tracker_engine_advance_tick(int chann, int opcode, bool do_retrig);

    void muteChannel(int ch, bool mute);
    void setFlags(const DivConfig& flags);
    void notifyInsChange(int ins);
    bool getWantPreNote();
    float getPostAmp();
    DivMacroInt* getChanMacroInt(int ch);
    DivChannelModeHints getModeHints(int chan);
    void notifyInsDeletion(void* ins);
    int init(DivEngine* parent, int channels, int sugRate, const DivConfig& flags);
    void quit();
    ~DivPlatformFZT();
};

#endif
