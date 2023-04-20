#include "noiseGen.h"

using namespace std;

unsigned int noise(unsigned int size, uint8_t* array, uint8_t* refChannels, uint8_t alpha, RandomGenerator* randGen)
{
    //Here, possibility of parallelization
    for (unsigned long int pixel = 0; pixel<size; pixel++)
    {
        //printf("Reference channel for pixel %ld: %d. ", pixel, refChannels[pixel]);
        for (uint8_t channel=0; channel<3; channel++)
        {
            if (refChannels[pixel]==channel) //Skip modifying the reference channel
            {continue; }
            array[pixel*3 + channel]=randGen->generateDifference(alpha, array[pixel*3+refChannels[pixel]]);
        }
        //printf("(%d;%d;%d)\n", array[pixel*3], array[pixel*3+1], array[pixel*3+2]);
    }

    return 0;
}