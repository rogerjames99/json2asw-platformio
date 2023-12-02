/** \file instrument.cpp
*/
#include <ArduinoLog.h>
#undef CR
#include <SD.h>
#include <vector>
#include <ArduinoJson.h>
#include "instrument.h"
#include "utils.h"

// Hack for padding
size_t sample_metadata_padding = 4;

static const int chipSelect = BUILTIN_SDCARD;

char filePosition[10];

CInstrument* CInstrument::singleton = nullptr;

CInstrument* CInstrument::getInstance()
{
    if (singleton == nullptr)
        singleton = new CInstrument();
    return singleton;
}

void CInstrument::updateFilePosition(File* file)
{
    snprintf(filePosition, 10, "%llu", file->position());
}

void CInstrument::dumpHexBytes(const uint8_t *bytes, size_t count)
{
    char row[256];
    size_t index = count - (count % 8);
    Log.verbose("Line %d bytes %x count %d index %d\n", __LINE__, bytes, count, index);
    size_t i = 0;
    for (; i < index; i = i + 8 )
    {
        snprintf(row, 256, "%lx %02x %02x %02x %02x %02x %02x %02x %02x\n",
            (long unsigned int)(bytes + i), bytes[i], bytes[i + 1], bytes[i + 2], bytes[i + 3],
            bytes[i + 4], bytes[i + 5], bytes[i + 6], bytes[i + 7]);
        Log.verbose("Line %d row %s",__LINE__, row);
    }

    if (index != count)
    {
        char * row_ptr = row;

        // Ordinary printf is safe here
        row_ptr = row_ptr + sprintf(row_ptr, "%lx ", (long unsigned int)(bytes + i));
        for (; i < count; i++)
        {
            row_ptr = row_ptr + sprintf(row_ptr, "%02x ", bytes[i]);
        }
        Log.verbose("Line %d row %s\n", __LINE__, row);
    }
}

void CInstrument::dumpHexBytes(const uint32_t *bytes, size_t count)
{
    char row[256];
    size_t index = count - (count % 8);
    Log.verbose("Line %d bytes %x count %d index %d\n", __LINE__, bytes, count, index);
    size_t i = 0;
    for (; i < index; i = i + 8 )
    {
        snprintf(row, 256, "%lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx\n",
            (long unsigned int)(bytes + i), bytes[i], bytes[i + 1], bytes[i + 2], bytes[i + 3],
            bytes[i + 4], bytes[i + 5], bytes[i + 6], bytes[i + 7]);
        Log.verbose("Line %d row %s",__LINE__, row);
    }

    if (index != count)
    {
        char * row_ptr = row;

        // Ordinary printf is safe here
        row_ptr = row_ptr + sprintf(row_ptr, "%lx ", (long unsigned int)(bytes + i));
        for (; i < count; i++)
        {
            row_ptr = row_ptr + sprintf(row_ptr, "%08lx ", bytes[i]);
        }
        Log.verbose("Line %d row %s\n", __LINE__, row);
    }
}

void CInstrument::dumpInstrumentData(instrument_data_t *instrumentData)
{
        char buf[256];
        snprintf(buf, 256, "Instrument data\n"
                            "===============\n"
                            "Number of samples %d\n"
                            "Sample note ranges pointer %p\n",
                            instrumentData->sample_count,
                            instrumentData->sample_note_ranges
                            );
        Log.verbose("%s", buf);
}

struct instrument_data_t* CInstrument::load(const char *name)
{
    size_t capacity = 50000;

    DynamicJsonDocument doc(capacity);
    DeserializationError retcode;

    instrument_data_t* instrument_data = new instrument_data_t;
    if (instrument_data == nullptr)
    {
        Log.verbose("Line %d Failed to allocate instrument_data", __LINE__);
        return nullptr;
    }

    if (!SD.begin(chipSelect))
    {
        Log.verbose("Line %d SD card intialisation failed\n", __LINE__);
        return nullptr;
    }

    if (!SD.exists(name))
    {
        Log.verbose("Line %d Cannot find file %s\n", __LINE__, name);
        return nullptr;
    }
    
    Log.verbose("Line %d Opening file %s\n", __LINE__, name);
    File data = SD.open(name);
    if (!data)
    {
        Log.verbose("Line %d Unable to open data file\n", __LINE__);
        return nullptr;
    }

    if ((retcode = deserializeJson(doc, data)) != DeserializationError::Ok)
    {
        Log.verbose("Line %d deserialisation failed %s\n", __LINE__, retcode.f_str());
        return nullptr;
    }
    instrument_data->sample_count = doc["sample_count"];
    //JsonObject top = doc.as<JsonObject>();
    JsonArray sample_ranges = doc["sample_note_ranges"].as<JsonArray>();
    JsonArray samples = doc["samples"].as<JsonArray>();

    // Create raw sample data
    std::vector<uint32_t> raw_samples_array;
    std::vector<size_t> sample_offsets_array;
    for (int i = 0; i < instrument_data->sample_count; i++)
    {
        size_t current_sample_offset = raw_samples_array.size();
        sample_offsets_array.push_back(current_sample_offset);
        Log.verbose("Line %d current sample size %d\n", __LINE__, current_sample_offset);
        JsonArray raw_samples = samples[i]["sample"].as<JsonArray>();
        for(JsonVariant v : raw_samples)
            raw_samples_array.push_back(v.as<uint32_t>());
    }
    size_t total_sample_size = raw_samples_array.size();
    Log.verbose("Line %d raw_samples_array size %d\n", __LINE__, total_sample_size);
    raw_sample_data_array =  std::make_unique<uint32_t[]>(total_sample_size);
    raw_sample_data_sizes_array = std::make_unique<size_t[]>(instrument_data->sample_count);

    // Create sample note ranges array
    sample_note_ranges_array = std::make_unique<uint8_t[]>(instrument_data->sample_count);

    for (int i = 0; i < instrument_data->sample_count; i++)
    {
        sample_note_ranges_array[i] = (uint8_t)sample_ranges[i];
        Log.verbose("Line %d sample_range[%d] %d\n", __LINE__, i, sample_note_ranges_array[i]);
    }

    // Create sample metadata array
    samples_metadata_array = std::make_unique<my_non_const_sample_metadata[]>(instrument_data->sample_count);
    
    return nullptr;   
}
