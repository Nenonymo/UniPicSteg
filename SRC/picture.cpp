#include "picture.h"

void highlightPixels(cv::Mat &pic, uint size, uint* positions)
{
    unsigned int channels = pic.channels();
    uchar* picPtr = pic.ptr<uchar>(0);
    for (uint i=0; i<size; i++)
    {
        *(picPtr + positions[i]*channels)=0;
        *(picPtr + positions[i]*channels+1)=0;
        *(picPtr + positions[i]*channels+2)=255;
    }
}