#include "encoding.h"


using namespace std;

uint16_t* encode(uint8_t alpha, std::string message, uint &outputSize)
{
    uint16_t base=pow((2*(uint)alpha+1),2);
    //Size of the output array, computed by using the log in base of the highest possible values of the units to determine number of "bits"
    outputSize=(ceil((log2(pow(256,UNIT_SIZE))/log2(base)))*(message.size()/UNIT_SIZE)+ceil((log2(pow(256,(message.size()%UNIT_SIZE)))/log2(base))));
    uint16_t* output=new uint16_t[outputSize];
    uint cursor=0;

    for(ushort unit=0;unit<ceil((double)(message.size())/UNIT_SIZE);unit++)
    {
        uint8_t unitSize=min((int)(message.size()-UNIT_SIZE*unit),UNIT_SIZE); //Last unit will be size len(message)%18
        uint8_t unitOutputSize=ceil(log2(pow(256,unitSize))/log2(base));
        unsigned long long ascii=0;
        for(ushort i=0;i<unitSize;i++)
        {ascii+=power((uint16_t)256, i)*(uint8_t)(char)message[i+unit*UNIT_SIZE]; }
        for(ushort i=0;i<unitOutputSize;i++)
        {
            output[cursor]=ascii%base;
            ascii/=base;
            cursor++;
        }
    }
    return output;
}

char* decode(uint8_t alpha, uint16_t* bits, uint32_t size)
{
    uint16_t base=pow((2*(uint)alpha+1),2);
    //Size of the output string
    ushort uSize=ceil(log2(pow(256,UNIT_SIZE))/log2(base)); //Size of an encoded unit of UNIT_SIZE*char
    ushort stringSize=floor(size/uSize)*UNIT_SIZE+floor(log2(pow(base,size%uSize))/log2(256));
    char* output=new char[stringSize];

    for(ushort unit=0;unit<ceil((double)size/uSize);unit++)
    {
        uint8_t unitSize=min((ushort)(size-uSize*unit), uSize);
        uint8_t unitOutputSize=floor(log2(pow(base, unitSize))/log2(256));
        unsigned long long ascii=0;
        for(ushort i=0;i<unitSize;i++)
        {ascii+=bits[i+unit*uSize]*power(base, i); }
        for(ushort i=0;i<unitOutputSize;i++)
        {
            output[unit*UNIT_SIZE + i]=(unsigned char)(unsigned long long)(ascii%256);
            ascii=ascii/256;
        }
    }
    return output;
}

unsigned long long power(uint16_t a, ushort b)
{
    if(b==0){return 1; }
    unsigned long long res = a;
    for(ushort i=1;i<b;i++){res*=a;}
    return res;
}
