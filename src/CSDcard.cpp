
#include <SD.h>
#include "CSDcard.h"

CSDcard* CSDcard::singleton = nullptr;

CSDcard* CSDcard::getInstance()
{
    if (singleton == nullptr)
        singleton = new CSDcard();
    return singleton;
}

bool CSDcard::initialise()
{
    // Start the sd card
}

