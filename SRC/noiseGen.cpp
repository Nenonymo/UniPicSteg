#include "noiseGen.h"

using namespace std;


unsigned int noise(cv::Mat &pic, uint8_t* refChannels, uint8_t alpha, RandomGenerator* generator)
{
    unsigned int height = pic.rows;
    unsigned int width = pic.cols;
    unsigned int channels = pic.channels();
    unsigned short* tmpRef = new unsigned short;

    for (uint rI=0; rI<height; rI++)
    {
        uchar* rowPtr = pic.ptr<uchar>(rI);
        for(uint cI=0; cI<width; cI++)
        {
            
            //Casts refVal to [alpha, 255-alpha] to ensure full range of noising
            *tmpRef = std::max(std::min(255, *(rowPtr+(cI*channels)+refChannels[rI*width+cI])+alpha)-(2*alpha), 0) +alpha;
            for (uint k=0; k<channels; k++)
            {
                //if(refChannels[rI*width+cI]==k) {continue; }
                uchar* pixPtr = rowPtr + (cI*channels) + k;
                //printf("Pixel (%d,%d . %d)=%d, ref=%d, ", rI, cI, k, *pixPtr, *tmpRef);
                uint ran= generator->generateRandInt(2*alpha+1);
                *pixPtr = *tmpRef - alpha + ran;
                //printf("result = %d - %d + %d = %d\n", *tmpRef, alpha, ran, *pixPtr);

            }
        }
    }

    return 0;
}