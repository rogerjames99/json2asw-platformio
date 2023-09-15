#include <fstream>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "sample_data.h"
#include "audio_defs.h"
#include "irish2_samples.cpp"

struct my_instrument_data : public instrument_data
{
    void serialize();
};

void my_instrument_data::serialize()
{
    std::size_t sample_count_size = sizeof sample_count;
    std::size_t sample_note_ranges_size = sizeof sample_note_ranges;
    std::size_t samples_size = sizeof samples;
    std::ofstream ostrm("irish2.dump", std::ios::binary);
    ostrm.write(reinterpret_cast<char*>(&sample_count_size), sizeof sample_count_size);
    ostrm.write(reinterpret_cast<char*>(&sample_note_ranges_size), sizeof sample_note_ranges);
    ostrm.write(reinterpret_cast<char*>(&samples_size), sizeof samples_size);
    ostrm.write(reinterpret_cast<char*>(&sample_count), sizeof sample_count);
    ostrm.write(reinterpret_cast<char*>(&sample_note_ranges), sizeof sample_note_ranges);
    ostrm.write(reinterpret_cast<char*>(&samples), sizeof samples);
}

int main(int, char**)
{
    my_instrument_data instrument = {irish2.sample_count, irish2.sample_note_ranges, irish2.samples};
    instrument.serialize();
	return 0;
}
