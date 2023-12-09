/** \file utils.cpp
*/
#include <ArduinoLog.h>
#undef CR
#include "utils.h"

void CUtils::dumpSampleMetadata(const struct AudioSynthWavetable::sample_data* metadata)
{
    char buf[2500];

	snprintf(buf, 2500,
            "sample %lx "
            "LOOP %d " 
            "INDEX_BITS %d "
            "PER_HERTZ_PHASE_INCREMENT %f "
            "MAX_PHASE %ld "
            "LOOP_PHASE_END %ld "
            "LOOP_PHASE_LENGTH %ld "
            "INITIAL_ATTENUATION_SCALAR %d\n"

	// VOLUME ENVELOPE VALUE
            "DELAY_COUNT %ld "
            "ATTACK_COUNT %ld "
            "HOLD_COUNT %ld "
            "DECAY_COUNT %ld "
            "RELEASE_COUNT %ld "
            "SUSTAIN_MULT %ld\n"

	// VIRBRATO VALUES
            "VIBRATO_DELAY %ld "
            "VIBRATO_INCREMENT %ld "
            "VIBRATO_PITCH_COEFFICIENT_INITIAL %f "
            "VIBRATO_PITCH_COEFFICIENT_SECOND %f\n"

	// MODULATION VALUES
            "MODULATION_DELAY %ld "
            "MODULATION_INCREMENT %ld "
            "MODULATION_PITCH_COEFFICIENT_INITIAL %f "
            "MODULATION_PITCH_COEFFICIENT_SECOND %f "
            "MODULATION_AMPLITUDE_INITIAL_GAIN %ld "
            "MODULATION_AMPLITUDE_SECOND_GAIN %ld\n",


            (unsigned long int)metadata->sample, metadata->LOOP, metadata->INDEX_BITS, 
            metadata->PER_HERTZ_PHASE_INCREMENT, metadata->MAX_PHASE, metadata->LOOP_PHASE_END,
            metadata->LOOP_PHASE_LENGTH, metadata->INITIAL_ATTENUATION_SCALAR, metadata->DELAY_COUNT,
            metadata->ATTACK_COUNT, metadata->HOLD_COUNT, metadata->DECAY_COUNT, metadata->RELEASE_COUNT,
            metadata->SUSTAIN_MULT, metadata->VIBRATO_DELAY, metadata->VIBRATO_INCREMENT,
            metadata->VIBRATO_PITCH_COEFFICIENT_INITIAL, metadata->VIBRATO_PITCH_COEFFICIENT_SECOND,
            metadata->MODULATION_DELAY, metadata->MODULATION_INCREMENT,
            metadata->MODULATION_PITCH_COEFFICIENT_INITIAL, metadata->MODULATION_PITCH_COEFFICIENT_SECOND,
            metadata->MODULATION_AMPLITUDE_INITIAL_GAIN, metadata->MODULATION_AMPLITUDE_SECOND_GAIN);

    Log.verbose("%s", buf);
}