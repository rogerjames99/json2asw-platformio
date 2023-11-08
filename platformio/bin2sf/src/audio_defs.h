/*
 * audio_defs.h
 *
 *  Created on: 14 Sept 2023
 *      Author: roger
 */

#ifndef AUDIO_DEFS_H_
#define AUDIO_DEFS_H_

#define WAVETABLE_CENTS_SHIFT(C) (pow(2.0, (C)/1200.0))
#define WAVETABLE_NOTE_TO_FREQUENCY(N) (440.0 * pow(2.0, ((N) - 69) / 12.0))
#define WAVETABLE_DECIBEL_SHIFT(dB) (pow(10.0, (dB)/20.0))
#define AUDIO_SAMPLE_RATE_EXACT 44100.0f
#define AUDIO_BLOCK_SAMPLES  128

static const int32_t UNITY_GAIN = INT32_MAX;
static constexpr float SAMPLES_PER_MSEC = (AUDIO_SAMPLE_RATE_EXACT/1000.0f);
static const int32_t LFO_SMOOTHNESS = 3;
static constexpr float LFO_PERIOD = (AUDIO_BLOCK_SAMPLES/(1 << (LFO_SMOOTHNESS-1)));
static const int32_t ENVELOPE_PERIOD = 8;

#endif /* AUDIO_DEFS_H_ */
