#include <fstream>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "audio_defs.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include "sample_data.h"
#include "instrument_samples.cpp"

using namespace std;

int main(int, char**)
{
    /*
    uint8_t sample_count;
    uint8_t* sample_note_ranges;
    sample_data *samples;
    */

    std::ofstream ostrm("instrument.json");
    cereal::JSONOutputArchive archive(ostrm);

    instrument.serialize(archive);
    return 0;
}
