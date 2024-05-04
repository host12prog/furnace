/*This is an emulation code of software synth engine of LTVA's Flizzer Tracker
program, originally written for Flipper Zero. The Flizzer Tracker source code can be
downloaded there: https://github.com/LTVA1/flizzer_tracker */

#pragma once

#ifndef FZT_H
#define FZT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define FZT_NUM_CHANNELS 4

#define RANDOM_SEED 0xf31782ce

#define ACC_BITS 23
#define ACC_LENGTH (1 << (ACC_BITS - 1))

#define OVERSAMPLE_ACC_BITS 26
#define OVERSAMPLE_ACC_LENGTH (1 << (OVERSAMPLE_ACC_BITS - 1))

#define OUTPUT_BITS 16
#define WAVE_AMP (1 << OUTPUT_BITS)

#define SINE_LUT_SIZE 256
#define SINE_LUT_BITDEPTH 8

#define MAX_ADSR (0xff << 17)
#define MAX_ADSR_VOLUME 0x80
#define BASE_FREQ 22050
#define envspd(eng, slope)                                                                     \
    ((slope) != 0 ?                                                                            \
         (((uint64_t)MAX_ADSR / ((slope) * (slope)*256 / 8)) * BASE_FREQ / eng->sample_rate) : \
         ((uint64_t)MAX_ADSR * BASE_FREQ / eng->sample_rate))

#define FREQ_TAB_SIZE 12 /* one octave */
#define NUM_OCTAVES 8 /* 0-7th octaves */

typedef struct {
    uint8_t a, d, s, r, volume, envelope_state;
    uint32_t envelope, envelope_speed;
} SoundEngineADSR;

typedef struct {
    int32_t cutoff, resonance, low, high, band;
} SoundEngineFilter;

typedef struct {
    uint32_t accumulator;
    uint32_t frequency;
    uint8_t waveform;
    uint16_t pw;
    uint32_t lfsr;
    SoundEngineADSR adsr;

    uint16_t flags;

    uint8_t ring_mod, hard_sync; // 0xff = self
    uint8_t sync_bit;

    uint8_t filter_mode;

    SoundEngineFilter filter;
} SoundEngineChannel;

typedef struct {
    SoundEngineChannel channel[FZT_NUM_CHANNELS];
    uint32_t sample_rate;
    bool external_audio_output;
    uint8_t sine_lut[SINE_LUT_SIZE];

    short* osc_buf[FZT_NUM_CHANNELS];
} SoundEngine;

uint16_t sound_engine_triangle(uint32_t acc);
uint32_t get_freq(int note);

void sound_engine_init(
    SoundEngine* sound_engine,
    uint32_t sample_rate);
void sound_engine_set_channel_frequency(
    SoundEngine* sound_engine,
    SoundEngineChannel* channel,
    int note);
void sound_engine_filter_set_coeff(SoundEngineFilter* flt, uint32_t frequency, uint16_t resonance);
void sound_engine_fill_buffer(
    SoundEngine* sound_engine,
    short** audio_buffer,
    size_t audio_buffer_size);
void sound_engine_enable_gate(SoundEngine* sound_engine, SoundEngineChannel* channel, bool enable);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FZT_H