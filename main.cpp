#include <fstream>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "sample_data.h"
#include "audio_defs.h"
#include "irish2_samples.cpp"

using namespace std;

/*
TODO
====
1. Worry about structure alignment and packing. If I run this program on 64bit PC
and then decode the file on an arm m7. Will it work?
*/

struct my_instrument_data : public instrument_data
{
    void serialize();
};

void my_instrument_data::serialize()
{

    std::ofstream ostrm("irish2.bin", ios::binary);
    //cout << "sizeof(unit8_t) " << sizeof(uint8_t) << endl;
    ostrm.write((char*)&sample_count, sizeof(uint8_t));
    // Dump the sample_note_ranges
    for (int i = 0; i < sample_count; i++)
        ostrm.write((char*)&sample_note_ranges[i], sizeof(uint8_t));

    // Dump the sample metadata
    cout << "sizeof(sample_data) " << sizeof(sample_data) << endl;
    for (int i = 0; i < sample_count; i++)
       ostrm.write((char*)&samples[i], sizeof(sample_data));

    // Dump the raw sample data
    //for (int i = 0; i < sample_count; i++)
    //    ostrm.write((char*)samples[i].sample, samples[i].number_of_raw_samples * sizeof(uint16_t));
}

int main(int, char**)
{
    my_instrument_data instrument = {irish2.sample_count, irish2.sample_note_ranges, irish2.samples};
    instrument.serialize();
	return 0;
}
