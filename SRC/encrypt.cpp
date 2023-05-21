#include "encrypt.h"

uint32_t* generateRangeSample(std::string key, unsigned int rangeSize, unsigned int sampleSize)
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

