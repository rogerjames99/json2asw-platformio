#include <cstdint>
#include <math.h>
#include "sample_data.h"
#include "audio_defs.h"
#include "irish2_samples.cpp"

int main(int, char**)
{
	uint8_t sample_count  = irish2.sample_count;
	uint8_t* sample_note_ranges = irish2.sample_note_ranges;
	sample_data* samples = irish2.samples;

	// Now dump the buggers out.
	return 0;
}
