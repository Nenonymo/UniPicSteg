#include "encrypt.h"

uint32_t* positionLattice(std::string key, unsigned int rangeSize, unsigned int sampleSize)
{
    unsigned int keyVal = 1563224; //Here, hash the key and transform the result into an integer
    unsigned int step = ((rangeSize/sampleSize)+keyVal)%rangeSize;

    uint32_t* res = new unsigned int[sampleSize];
    unsigned int index=0;

    unsigned int counter = keyVal % rangeSize;

    while (index < sampleSize)
    {
        res[index] = counter%rangeSize;
        index++;
        counter = counter + step;
    }

    return res;
}

uint32_t* generatePosition(uint32_t boundary, uint length, double seed[6])
{
    return genRandArray<uint32_t>(seed[0], seed[1], seed[2], seed[3], seed[4], seed[5], length, boundary);
}

