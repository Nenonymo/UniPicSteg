#pragma once
#include <stdlib.h>

class RandomGenerator
{
    public:
        RandomGenerator();
        ~RandomGenerator();

        unsigned int generateRandInt();

    private:
        unsigned int RANDMAX;
        unsigned int seed;
}