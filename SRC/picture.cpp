#include "picture.h"

void highlightPixels(cv::Mat &pic, uint size, uint32_t* positions)
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

uint8_t* genDiff(uint16_t val, uint16_t pixBase)
{
    uint8_t* diff=new uint8_t[2];
    diff[0]=(uint8_t)(val/pixBase);
    diff[1]=(uint8_t)(val%pixBase);
    //printf("val: %d -> (%d,%d)\n",val,diff[0],diff[1]);
    return diff;
}

void insertEncoded(cv::Mat &pic, uint size, uint32_t* positions, uint16_t* encoded, uint8_t alpha)
{
    uint16_t pixBase=2*alpha+1;
    uchar* picPtr=pic.ptr<uchar>(0);
    uchar ref=0;
    for(unsigned long i=0;i<size;i++)
    {
        uint8_t* diff=genDiff(encoded[i],pixBase);
        //Add the diff pattern to the picture
        ref=std::max(std::min(255,*(picPtr+positions[i]*3)+alpha)-(2*alpha), 0) +alpha;
        for(uint8_t c=0;c<2;c++)
        {*(picPtr+positions[i]*3+(c+(i%3))%3)=ref-alpha+diff[c]; }
        delete[] diff;
    }
}

uint16_t* grabEncoded(cv::Mat &pic, uint size, uint32_t* positions, uint8_t alpha)
{
    uint8_t pixBase=2*alpha+1;
    uchar* picPtr=pic.ptr<uchar>(0);
    uchar ref=0;
    uint16_t* output=new uint16_t[size];
    for(unsigned long i=0;i<size;i++)
    {
        ref=std::max(std::min(255,*(picPtr+positions[i]*3+(i+2)%3)+alpha)-(2*alpha),0)+alpha;
        output[i]=(*(picPtr+positions[i]*3+(i%3))+alpha-ref)*pixBase+(*(picPtr+positions[i]*3+(i+1)%3)+alpha-ref);
        //printf("Pixel %ld: %d\n", i, output[i]);
    }
    return output;
}