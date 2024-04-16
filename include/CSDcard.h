#ifndef CSDCARD_H
#define CSDCARD_H

#pragma once

/**
 * @brief Declaration of CSDcard class.
*/
class CSDcard
{
public:
    /** @brief Deleted copy constructor.*/
    CSDcard(CSDcard &other) = delete;

    /** @brief Deleted operator overload.*/
    void operator = (const CSDcard &) = delete;

    /** @brief Create a singleton if necessary.
     * @return A pointer the the singleton.*/
    static CSDcard *getInstance();

    bool initialise();

protected:
    /** @brief constructor.*/
    CSDcard() {}

    /** @brief A pointer to the singleton.*/
    static CSDcard* singleton;

};

#endif