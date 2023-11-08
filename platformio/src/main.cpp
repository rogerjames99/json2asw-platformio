#include <Arduino.h>
#include <Audio.h>
#include <cstdint>
#include <math.h>
#include "audio_defs.h"
#include "sample_data.h"
#include "irish2_samples.cpp"

void setup()
{
    while (!Serial);
    Serial.printf("sizeof(instrument_data) %d\n", sizeof(instrument_data));
    Serial.printf("sizeof(instrument_data::sample_count) %d offset %d\n",
        sizeof(instrument_data::sample_count),
        reinterpret_cast<unsigned long>(&irish2.sample_count) - reinterpret_cast<unsigned long>(&irish2));
    Serial.printf("sizeof(instrument_data::sample_note_ranges) %d offset %d\n",
        sizeof(instrument_data::sample_note_ranges),
        reinterpret_cast<unsigned long>(&irish2.sample_note_ranges) - reinterpret_cast<unsigned long>(&irish2));
    Serial.printf("sizeof(instrument_data::samples) %d offset %d\n",
        sizeof(instrument_data::samples),
        reinterpret_cast<unsigned long>(&irish2.samples) - reinterpret_cast<unsigned long>(&irish2));



    Serial.printf("sizeof(sample_data) %d\n", sizeof(sample_data));
    Serial.printf("sizeof(sample_data::sample) %d offset %d\n",
        sizeof(sample_data::sample),
        reinterpret_cast<unsigned long>(&irish2_samples[0].sample) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::number_of_raw_samples) %d offset %d\n",
        sizeof(sample_data::number_of_raw_samples),
        reinterpret_cast<unsigned long>(&irish2_samples[0].number_of_raw_samples) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::LOOP %d offset %d\n",
        sizeof(sample_data::LOOP),
        reinterpret_cast<unsigned long>(&irish2_samples[0].LOOP) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::INDEX_BITS) %d offset %d\n",
        sizeof(sample_data::INDEX_BITS),
        reinterpret_cast<unsigned long>(&irish2_samples[0].INDEX_BITS) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::PER_HERTZ_PHASE_INCREMENT) %d offset %d\n",
        sizeof(sample_data::PER_HERTZ_PHASE_INCREMENT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].PER_HERTZ_PHASE_INCREMENT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MAX_PHASE) %d offset %d\n",sizeof(sample_data::MAX_PHASE),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MAX_PHASE) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::LOOP_PHASE_END) %d offset %d\n",sizeof(sample_data::LOOP_PHASE_END),
        reinterpret_cast<unsigned long>(&irish2_samples[0].LOOP_PHASE_END) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::LOOP_PHASE_LENGTH) %d offset %d\n",sizeof(sample_data::LOOP_PHASE_LENGTH),
        reinterpret_cast<unsigned long>(&irish2_samples[0].LOOP_PHASE_LENGTH) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::INITIAL_ATTENUATION_SCALAR) %d offset %d\n",sizeof(sample_data::INITIAL_ATTENUATION_SCALAR),
        reinterpret_cast<unsigned long>(&irish2_samples[0].INITIAL_ATTENUATION_SCALAR) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::DELAY_COUNT) %d offset %d\n",sizeof(sample_data::DELAY_COUNT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].DELAY_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::ATTACK_COUNT) %d offset %d\n",sizeof(sample_data::ATTACK_COUNT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].ATTACK_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::HOLD_COUNT) %d offset %d\n",sizeof(sample_data::HOLD_COUNT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].HOLD_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::DECAY_COUNT) %d offset %d\n",sizeof(sample_data::DECAY_COUNT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].DECAY_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::RELEASE_COUNT) %d offset %d\n",sizeof(sample_data::RELEASE_COUNT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].RELEASE_COUNT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::SUSTAIN_MULT) %d offset %d\n",sizeof(sample_data::SUSTAIN_MULT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].SUSTAIN_MULT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::VIBRATO_DELAY) %d offset %d\n",sizeof(sample_data::VIBRATO_DELAY),
        reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_DELAY) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::VIBRATO_INCREMENT) %d offset %d\n",sizeof(sample_data::VIBRATO_INCREMENT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_INCREMENT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_INITIAL) %d offset %d\n",sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_INITIAL),
        reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_PITCH_COEFFICIENT_INITIAL) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_SECOND) %d offset %d\n",sizeof(sample_data::VIBRATO_PITCH_COEFFICIENT_SECOND),
        reinterpret_cast<unsigned long>(&irish2_samples[0].VIBRATO_PITCH_COEFFICIENT_SECOND) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MODULATION_DELAY) %d offset %d\n",sizeof(sample_data::MODULATION_DELAY),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_DELAY) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MODULATION_INCREMENT) %d offset %d\n",sizeof(sample_data::MODULATION_INCREMENT),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_INCREMENT) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_INITIAL) %d offset %d\n",sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_INITIAL),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_PITCH_COEFFICIENT_INITIAL) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_SECOND) %d offset %d\n",sizeof(sample_data::MODULATION_PITCH_COEFFICIENT_SECOND),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_PITCH_COEFFICIENT_SECOND) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MODULATION_AMPLITUDE_INITIAL_GAIN) %d offset %d\n",sizeof(sample_data::MODULATION_AMPLITUDE_INITIAL_GAIN),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_AMPLITUDE_INITIAL_GAIN) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
    Serial.printf("sizeof(sample_data::MODULATION_AMPLITUDE_SECOND_GAIN) %d offset %d\n",sizeof(sample_data::MODULATION_AMPLITUDE_SECOND_GAIN),
        reinterpret_cast<unsigned long>(&irish2_samples[0].MODULATION_AMPLITUDE_SECOND_GAIN) - reinterpret_cast<unsigned long>(&irish2_samples[0]));
}

void loop()
{
}

