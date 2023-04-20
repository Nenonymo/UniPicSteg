#pragma once

#include <stdlib.h>
#include <stdint.h>

class RandomGenerator
{
    public:
        RandomGenerator(unsigned int seed, unsigned int maxVal=1);
        ~RandomGenerator();

        unsigned int generateRandInt();
        uint8_t* generateArray(unsigned int size, unsigned int max);
        uint8_t generateDifference(uint8_t aplha, uint8_t value);

        void setMaxVal(unsigned int maxVal, unsigned int open=0);

    private:
        unsigned int maxVal;
        const unsigned int seed;
};