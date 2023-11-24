/** \file instrument.h
*/
#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include <Audio.h>

/**
 * @brief Declaration of CInstrument class.
*/
class CInstrument
{
public:
    struct my_instrument_data_t
    {
        uint8_t sample_count;
        uint8_t* sample_note_ranges;
        AudioSynthWavetable::sample_data* samples;
    };
    /** @brief Deleted copy constructor.*/
    CInstrument(CInstrument &other) = delete;

    /** @brief Deleted operator overload.*/
    void operator = (const CInstrument &) = delete;

    /** @brief Create a singleton if necessary.
     * @return A pointer the the singleton.*/
    static CInstrument *getInstance();


    struct AudioSynthWavetable::instrument_data* load(const char* name);

protected:
    /** @brief constructor.*/
    CInstrument() {};

    /** @brief Dump hex bytes.
     * @param[in] bytes Pointer to the memory to be dumped.
     * @param[in] count Number of bytes to be dumped.
    */
    static void dumpHexBytes(const uint8_t *bytes, size_t count);
    static void dumpHexBytes(const uint32_t *bytes, size_t count);

    /** @brief update the current binary file position
     * @param[in] file a pointer to the File structure to query.
    */
    static void updateFilePosition(File* file);
    
    /** @brief Dump instrument data to log.
     * @param[in] instrumentData A pointer to the instrument data to be logged.
    */
    void dumpInstrumentData(AudioSynthWavetable::instrument_data *instrumentData);

    /** @brief A pointer to the singleton.*/
    static CInstrument* singleton;
    /** @brief A non const version of the instrument_data struct.*/
    my_instrument_data_t instrument_data =
    {
        0,
        nullptr,
        nullptr
    };
    /** @brief A pointer to the raw sample sizes array*/
    uint16_t* raw_sample_sizes = nullptr;
    /** @brief A pointer to the sample note ranges array.*/
    uint8_t* sample_note_ranges_array = nullptr;
    /** @brief A pointer to the samples metadata array.*/
    AudioSynthWavetable::sample_data *samples_metadata_array = nullptr;
};
#endif // INSTRUMENT_H
