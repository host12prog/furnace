/*This is an emulation code of software synth engine of LTVA's Flizzer Tracker
program, originally written for Flipper Zero. The Flizzer Tracker source code can be
downloaded there: https://github.com/LTVA1/flizzer_tracker */

#include "fzt.h"

#define PI 3.1415

#define FZT_NUM_CHANNELS 4

typedef enum {
    SE_WAVEFORM_NONE = 0,
    SE_WAVEFORM_NOISE = 1,
    SE_WAVEFORM_PULSE = 2,
    SE_WAVEFORM_TRIANGLE = 4,
    SE_WAVEFORM_SAW = 8,
    SE_WAVEFORM_NOISE_METAL = 16,
    SE_WAVEFORM_SINE = 32,
} SoundEngineWaveformType;

typedef enum {
    SE_ENABLE_FILTER = 1,
    SE_ENABLE_GATE = 2,
    SE_ENABLE_RING_MOD = 4,
    SE_ENABLE_HARD_SYNC = 8,
    SE_ENABLE_KEYDOWN_SYNC = 16, // sync oscillators on keydown
} SoundEngineFlags;

typedef enum {
    FIL_OUTPUT_LOWPASS = 1,
    FIL_OUTPUT_HIGHPASS = 2,
    FIL_OUTPUT_BANDPASS = 3,
    FIL_OUTPUT_LOW_HIGH = 4,
    FIL_OUTPUT_HIGH_BAND = 5,
    FIL_OUTPUT_LOW_BAND = 6,
    FIL_OUTPUT_LOW_HIGH_BAND = 7,
    /* ============ */
    FIL_MODES = 8,
} SoundEngineFilterModes;

typedef enum {
    ATTACK = 1,
    DECAY = 2,
    SUSTAIN = 3,
    RELEASE = 4,
    DONE = 5,
} SoundEngineEnvelopeStates;

typedef enum {
    TE_ENABLE_VIBRATO = 1,
    TE_ENABLE_PWM = 2,
    TE_PROG_NO_RESTART = 4,
    TE_SET_CUTOFF = 8,
    TE_SET_PW = 16,
    TE_RETRIGGER_ON_SLIDE = 32, // call trigger instrument function even if slide command is there
} TrackerEngineFlags;

#define MIDDLE_C (12 * 4)
#define MAX_NOTE (12 * 7 + 11)

const uint32_t frequency_table[FREQ_TAB_SIZE] = {
    (uint32_t)(2093.00 * 1024 * 4), // 7th octave, the highest in this tracker
    (uint32_t)(2217.46 * 1024 * 4), // frequency precision is 1 / 1024th of Hz
    (uint32_t)(2349.32 * 1024 * 4),
    (uint32_t)(2489.02 * 1024 * 4),
    (uint32_t)(2637.02 * 1024 * 4),
    (uint32_t)(2793.83 * 1024 * 4),
    (uint32_t)(2959.96 * 1024 * 4),
    (uint32_t)(3135.96 * 1024 * 4),
    (uint32_t)(3322.44 * 1024 * 4),
    (uint32_t)(3520.00 * 1024 * 4),
    (uint32_t)(3729.31 * 1024 * 4),
    (uint32_t)(3951.07 * 1024 * 4),
};

uint32_t get_freq(uint16_t note) {
    if(note >= ((FREQ_TAB_SIZE * 8 - 1) << 8)) {
        return frequency_table[FREQ_TAB_SIZE - 1];
    }

    if((note & 0xff) == 0) {
        return frequency_table[((note >> 8) % 12)] /
               (2 << ((NUM_OCTAVES - ((note >> 8) / 12)))); // wrap to one octave
    }

    else {
        uint64_t f1 = frequency_table[((note >> 8) % 12)] /
                      (uint64_t)(2 << ((NUM_OCTAVES - ((note >> 8) / 12))));
        uint64_t f2 = frequency_table[(((note >> 8) + 1) % 12)] /
                      (uint64_t)(2 << ((NUM_OCTAVES - (((note >> 8) + 1) / 12))));

        return f1 + (uint64_t)((f2 - f1) * (uint64_t)(note & 0xff)) / (uint64_t)256;
    }
}

int32_t sound_engine_cycle_and_output_adsr(
    int32_t input,
    SoundEngine* eng,
    SoundEngineADSR* adsr,
    uint16_t* flags) {
    switch(adsr->envelope_state) {
    case ATTACK: {
        adsr->envelope += adsr->envelope_speed;

        if(adsr->envelope >= MAX_ADSR) {
            adsr->envelope_state = DECAY;
            adsr->envelope = MAX_ADSR;

            adsr->envelope_speed = envspd(eng, adsr->d);
        }

        break;
    }

    case DECAY: {
        if(adsr->envelope > ((uint32_t)adsr->s << 17) + adsr->envelope_speed) {
            adsr->envelope -= adsr->envelope_speed;
        }

        else {
            adsr->envelope = (uint32_t)adsr->s << 17;
            adsr->envelope_state = (adsr->s == 0) ? RELEASE : SUSTAIN;

            adsr->envelope_speed = envspd(eng, adsr->r);
        }

        break;
    }

    case SUSTAIN:
    case DONE: {
        break;
    }

    case RELEASE: {
        if(adsr->envelope > adsr->envelope_speed) {
            adsr->envelope -= adsr->envelope_speed;
        }

        else {
            adsr->envelope_state = DONE;
            *flags &= ~SE_ENABLE_GATE;
            adsr->envelope = 0;
        }

        break;
    }
    }

    return (int32_t)((int32_t)input * (int32_t)(adsr->envelope >> 10) / (int32_t)(MAX_ADSR >> 10) *
                     (int32_t)adsr->volume / (int32_t)MAX_ADSR_VOLUME);
}

void sound_engine_filter_set_coeff(SoundEngineFilter* flt, uint32_t frequency, uint16_t resonance) {
    flt->cutoff = (frequency << 5);
    flt->resonance = ((int32_t)resonance * 11 / 6) - 200;
}

void sound_engine_filter_cycle(
    SoundEngineFilter* flt,
    int32_t input) // don't ask me how it works, stolen from Furnace tracker TSU synth
{
    input /= 8;
    flt->low = flt->low + ((flt->cutoff * flt->band) >> 16);
    flt->high = input - flt->low - (((256 - flt->resonance) * flt->band) >> 8);
    flt->band = ((flt->cutoff * flt->high) >> 16) + flt->band;
}

int32_t sound_engine_output_lowpass(SoundEngineFilter* flt) {
    return flt->low * 8;
}

int32_t sound_engine_output_highpass(SoundEngineFilter* flt) {
    return flt->high * 8;
}

int32_t sound_engine_output_bandpass(SoundEngineFilter* flt) {
    return flt->band * 8;
}

uint16_t sound_engine_pulse(uint32_t acc, uint32_t pw) // 0-FFF pulse width range
{
    return (
        ((acc >> (((uint32_t)OVERSAMPLE_ACC_BITS - 17))) >= ((pw == 0xfff ? pw + 1 : pw) << 4) ?
             (WAVE_AMP - 1) :
             0));
}

uint16_t sound_engine_saw(uint32_t acc) {
    return (acc >> (OVERSAMPLE_ACC_BITS - OUTPUT_BITS - 1)) & (WAVE_AMP - 1);
}

uint16_t sound_engine_triangle(uint32_t acc) {
    return (
        (((acc & (OVERSAMPLE_ACC_LENGTH / 2)) ? ~acc : acc) >> (OVERSAMPLE_ACC_BITS - OUTPUT_BITS - 2)) &
        (WAVE_AMP * 2 - 1));
}

uint16_t sound_engine_sine(uint32_t acc, SoundEngine* sound_engine) {
    return (
        (uint16_t)sound_engine->sine_lut[(acc >> (OVERSAMPLE_ACC_BITS - SINE_LUT_BITDEPTH))]
        << (OUTPUT_BITS - SINE_LUT_BITDEPTH));
}

void shift_lfsr(uint32_t* v, uint32_t tap_0, uint32_t tap_1) {
    typedef uint32_t T;
    const T zero = (T)(0);
    const T lsb = zero + (T)(1);
    const T feedback = ((lsb << (tap_0)) ^ (lsb << (tap_1)));

    *v = (*v >> 1) ^ ((zero - (*v & lsb)) & feedback);
}

uint16_t sound_engine_noise(SoundEngineChannel* channel, uint32_t prev_acc, uint8_t advance) {
    if((prev_acc & (OVERSAMPLE_ACC_LENGTH / 32)) != (channel->accumulator & (OVERSAMPLE_ACC_LENGTH / 32)) && advance) { //advance is to preserve noise sound from orig fzt
        if(channel->waveform & SE_WAVEFORM_NOISE_METAL) {
            shift_lfsr(&channel->lfsr, 14, 8);
            channel->lfsr &= (1 << (14 + 1)) - 1;
        }

        else {
            shift_lfsr(&channel->lfsr, 22, 17);
            channel->lfsr &= (1 << (22 + 1)) - 1;
        }
    }

    return (channel->lfsr) & (WAVE_AMP - 1);
}

uint16_t
    sound_engine_osc(SoundEngine* sound_engine, SoundEngineChannel* channel, uint32_t prev_acc, uint8_t advance) {
    switch(channel->waveform) {
    case SE_WAVEFORM_NOISE:
    case SE_WAVEFORM_NOISE_METAL:
    case(SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_noise(channel, prev_acc, advance);
        break;
    }

    case SE_WAVEFORM_PULSE: {
        return sound_engine_pulse(channel->accumulator, channel->pw);
        break;
    }

    case SE_WAVEFORM_TRIANGLE: {
        return sound_engine_triangle(channel->accumulator);
        break;
    }

    case SE_WAVEFORM_SAW: {
        return sound_engine_saw(channel->accumulator);
        break;
    }

    case SE_WAVEFORM_SINE: {
        return sound_engine_sine(channel->accumulator, sound_engine);
        break;
    }

    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_triangle(channel->accumulator) & sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator);
    }

    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_noise(channel, prev_acc, advance) & sound_engine_triangle(channel->accumulator);
    }

    case(SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_saw(channel->accumulator) & sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_saw(channel->accumulator);
    }

    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_saw(channel->accumulator) & sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW): {
        return sound_engine_triangle(channel->accumulator) &
               sound_engine_saw(channel->accumulator);
    }

    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_triangle(channel->accumulator) &
               sound_engine_saw(channel->accumulator) & sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_saw(channel->accumulator);
    }

    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(
        SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE |
        SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_saw(channel->accumulator) & sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE): {
        return sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE_METAL):
    case(
        SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_PULSE | SE_WAVEFORM_NOISE |
        SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_SAW): {
        return sound_engine_saw(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_saw(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_saw(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(
        SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE |
        SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_saw(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW): {
        return sound_engine_saw(channel->accumulator) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE):
    case(SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE_METAL):
    case(
        SE_WAVEFORM_SINE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW | SE_WAVEFORM_NOISE |
        SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_saw(channel->accumulator) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    case(SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW): {
        return sound_engine_saw(channel->accumulator) &
               sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine);
    }

    case(
        SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW |
        SE_WAVEFORM_NOISE):
    case(
        SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW |
        SE_WAVEFORM_NOISE_METAL):
    case(
        SE_WAVEFORM_SINE | SE_WAVEFORM_PULSE | SE_WAVEFORM_TRIANGLE | SE_WAVEFORM_SAW |
        SE_WAVEFORM_NOISE | SE_WAVEFORM_NOISE_METAL): {
        return sound_engine_saw(channel->accumulator) &
               sound_engine_pulse(channel->accumulator, channel->pw) &
               sound_engine_triangle(channel->accumulator) &
               sound_engine_sine(channel->accumulator, sound_engine) &
               sound_engine_noise(channel, prev_acc, advance);
    }

    default:
        break;
    }

    return WAVE_AMP / 2;
}

void sound_engine_init(
    SoundEngine* sound_engine,
    uint32_t sample_rate) {

    memset(sound_engine, 0, sizeof(SoundEngine));

    sound_engine->sample_rate = sample_rate;

    for(int i = 0; i < FZT_NUM_CHANNELS; ++i) {
        sound_engine->channel[i].lfsr = RANDOM_SEED;
    }

    for(int i = 0; i < SINE_LUT_SIZE; ++i) {
        sound_engine->sine_lut[i] = (uint8_t)((sinf(i / 64.0 * PI) + 1.0) * 127.0);
    }
}

void sound_engine_set_channel_frequency(
    SoundEngine* sound_engine,
    SoundEngineChannel* channel,
    uint16_t note) {
    uint32_t frequency = get_freq(note);

    if(frequency != 0) {
        channel->frequency = (uint64_t)(ACC_LENGTH) / (uint64_t)1024 * (uint64_t)(frequency) /
                             (uint64_t)sound_engine->sample_rate;
    }

    else {
        channel->frequency = 0;
    }
}

void sound_engine_enable_gate(SoundEngine* sound_engine, SoundEngineChannel* channel, bool enable) {
    if(enable) {
        channel->adsr.envelope = 0;
        channel->adsr.envelope_speed = envspd(sound_engine, channel->adsr.a);
        channel->adsr.envelope_state = ATTACK;

        channel->flags |= SE_ENABLE_GATE;

        if(channel->flags & SE_ENABLE_KEYDOWN_SYNC) {
            channel->accumulator = 0;
        }
    }

    else {
        channel->adsr.envelope_state = RELEASE;
        channel->adsr.envelope_speed = envspd(sound_engine, channel->adsr.r);
    }
}

void sound_engine_fill_buffer(
    SoundEngine* sound_engine,
    short** audio_buffer,
    size_t audio_buffer_size) {
    int32_t channel_output[FZT_NUM_CHANNELS];
    int32_t channel_output_final[FZT_NUM_CHANNELS];

    for(int i = 0; i < FZT_NUM_CHANNELS; i++)
    {
        if(sound_engine->osc_buf[i] != NULL)
        {
            free(sound_engine->osc_buf[i]);
        }

        sound_engine->osc_buf[i] = (short*)malloc(sizeof(short) * audio_buffer_size);
    }

    for(uint32_t i = 0; i < (uint32_t)audio_buffer_size; ++i) {
        int32_t output = 0;

        for(uint32_t chan = 0; chan < FZT_NUM_CHANNELS; ++chan) {
            SoundEngineChannel* channel = &sound_engine->channel[chan];
            channel_output[chan] = 0;

            if(channel->frequency > 0) 
            {
                channel->sync_bit = 0;
                channel->sync_bit |= (channel->accumulator > OVERSAMPLE_ACC_LENGTH ? 1 : 0);

                uint32_t prev_acc = channel->accumulator;

                for(int i = 0; i < 8; i++)
                {
                    channel->accumulator += channel->frequency;
                    channel->accumulator &= OVERSAMPLE_ACC_LENGTH - 1;

                    channel_output[chan] +=
                        sound_engine_osc(sound_engine, channel, prev_acc, i == 7);
                }

                channel_output[chan] >>= 3;
                channel_output[chan] -= WAVE_AMP / 2;

                if(channel->flags & SE_ENABLE_HARD_SYNC) {
                    uint8_t hard_sync_src = channel->hard_sync == 0xff ? chan : channel->hard_sync;

                    if(sound_engine->channel[hard_sync_src].sync_bit) {
                        channel->accumulator = 0;
                    }
                }

                if(channel->flags & SE_ENABLE_RING_MOD) {
                    uint8_t ring_mod_src = channel->ring_mod == 0xff ? chan : channel->ring_mod;
                    channel_output[chan] =
                        channel_output[chan] * channel_output[ring_mod_src] / WAVE_AMP;
                }

                channel_output_final[chan] = sound_engine_cycle_and_output_adsr(
                    channel_output[chan], sound_engine, &channel->adsr, &channel->flags);

                if(channel->flags & SE_ENABLE_FILTER) {
                    if(channel->filter_mode != 0) {
                        sound_engine_filter_cycle(&channel->filter, channel_output_final[chan]);

                        switch(channel->filter_mode) {
                        case FIL_OUTPUT_LOWPASS: {
                            channel_output_final[chan] =
                                sound_engine_output_lowpass(&channel->filter);
                            break;
                        }

                        case FIL_OUTPUT_HIGHPASS: {
                            channel_output_final[chan] =
                                sound_engine_output_highpass(&channel->filter);
                            break;
                        }

                        case FIL_OUTPUT_BANDPASS: {
                            channel_output_final[chan] =
                                sound_engine_output_bandpass(&channel->filter);
                            break;
                        }

                        case FIL_OUTPUT_LOW_HIGH: {
                            channel_output_final[chan] =
                                sound_engine_output_lowpass(&channel->filter) +
                                sound_engine_output_highpass(&channel->filter);
                            break;
                        }

                        case FIL_OUTPUT_HIGH_BAND: {
                            channel_output_final[chan] =
                                sound_engine_output_highpass(&channel->filter) +
                                sound_engine_output_bandpass(&channel->filter);
                            break;
                        }

                        case FIL_OUTPUT_LOW_BAND: {
                            channel_output_final[chan] =
                                sound_engine_output_lowpass(&channel->filter) +
                                sound_engine_output_bandpass(&channel->filter);
                            break;
                        }

                        case FIL_OUTPUT_LOW_HIGH_BAND: {
                            channel_output_final[chan] =
                                sound_engine_output_lowpass(&channel->filter) +
                                sound_engine_output_highpass(&channel->filter) +
                                sound_engine_output_bandpass(&channel->filter);
                            break;
                        }
                        }
                    }
                }

                output += channel_output_final[chan];
                sound_engine->osc_buf[chan][i] = channel_output_final[chan] >> 2;
            }
        }

        audio_buffer[0][i] = output >> 3;
    }
}