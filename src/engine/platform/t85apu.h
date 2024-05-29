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

#ifndef _T85APU_H
#define _T85APU_H

#include "../dispatch.h"
#include "../../fixedQueue.h"
#include "sound/attiny85apu/t85apu.h"

#define T85APU_NUM_CHANS 8
#define T85APU_NUM_REAL_CHANS 5

class DivPlatformT85APU: public DivDispatch {
  public:
    struct Channel: public SharedChannel<int> {
      int octave, increment;
      int duty;
      bool noise, envelope;
      int env_num, env_shape;
      Channel():
        SharedChannel<int>(255),
        octave(0),
        increment(0),
        duty(0x80),
        noise(false),
        envelope(false),
        env_num(0) {}
    };
    Channel chan[T85APU_NUM_CHANS];
    int env_shape[2];
    int env_init_phase[2];
    bool isMuted[T85APU_NUM_CHANS];
    DivDispatchOscBuffer* oscBuf[T85APU_NUM_CHANS];
    struct QueuedWrite {
        unsigned char addr;
        unsigned char val;
        QueuedWrite(): addr(0), val(0) {}
        QueuedWrite(unsigned char a, unsigned char v): addr(a), val(v) {}
    };
    FixedQueue<QueuedWrite,128> writes;

    t85APU* t85_synth;

    unsigned char regPool[0x20];

    void acquire(short** buf, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    unsigned char* getRegisterPool();
    int getRegisterPoolSize();
    void reset();
    int getOutputCount();
    void forceIns();
    void tick(bool sysTick=true);

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
    ~DivPlatformT85APU();
};

#endif
