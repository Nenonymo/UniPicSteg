#include "test.h"

using namespace std;
uint randi(uint a) {return std::rand() % a; }

string makeName(uint alpha, double usage)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << usage;
    std::string U_str = stream.str();

    // Remove the part before the decimal point
    size_t decimalPos = U_str.find('.');
    if (decimalPos != std::string::npos)
        U_str = U_str.substr(decimalPos + 1);

    if(U_str=="00") {U_str="100"; }

    // Concatenate the strings
    std::string filename = std::to_string(alpha) + "_" + U_str + ".png";

    return filename;
}

void test(InsertJob* data)
{
    //Open picture
    cv::Mat srcPic = loadPicture(DATA_IN_PREF+data->path);
    data->dims[0] = srcPic.rows; //Matrices dims are always row*col
    data->dims[1] = srcPic.cols;
    data->size = data->dims[0]*data->dims[1];
    int al[10]={1,2,3,4,5,6,8,12,20,41};
    double rates[3] = {0.0625f, 0.125f, 0.1875f};
    //double rates[10] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    cv::Mat dstPic = srcPic.clone();

    uint8_t pixBase;
    uint16_t base;
    
    uchar* picPtr=dstPic.ptr<uchar>(0);
    uchar* refPicPtr=srcPic.ptr<uchar>(0);
    uint g=0;
    std::srand(static_cast<int>(std::time(nullptr)));

    for(uint i=0;i<10;i++)
    {cout<<" & " << al[i];}
    cout<<"\\\\\n\\hline\n";
    for(uint r=0;r<3;r++)
    {
        printf("\$%.3f\\\%\$", rates[r]);
        for(uint a=0; a<10; a++)
        {
            dstPic=srcPic.clone();
            picPtr=dstPic.ptr<uchar>(0);
            pixBase = 2*al[a]+1;
            base = (2*al[a] + 1) + (2*al[a] + 1);
            uint encSize=min((uint)(data->size * rates[r]), data->size);
            uint8_t ref=0;

            cout<<data->size<<endl;

            uint32_t* randSeq = generatePosition(data->size, encSize, data->seed);
            uint32_t* positions = sampleUniqueUniform(encSize, data->size, randSeq);
            //for(uint i=0;i<encSize;i++){printf("(%d %d) ",randSeq[i],positions[i]); } cout<<endl;
            delete[] randSeq;

            for(unsigned long i=0;i<encSize;i++)
            {
                g=randi(base);
                ref=std::max(std::min(255,*(picPtr+positions[i]*3+(i+2)%3)+al[a])-(2*al[a]), 0) +al[a];
                *(picPtr+positions[i]*3+(i+0)%3)=ref-al[a]+g/pixBase; 
                *(picPtr+positions[i]*3+(i+1)%3)=ref-al[a]+g%pixBase; 
            }

            double mse=0;
            for(unsigned long i=0;i<encSize;i++)
            {
                uint tmp=0;
                ref=std::max(std::min(255,*(picPtr+positions[i]*3+(i+2)%3)+al[a])-(2*al[a]), 0) +al[a];
                //printf("(%d-%d)^2 = %d \n", *(refPicPtr+i*3+2), *(picPtr+i*3+0), (uint)pow(abs(*(refPicPtr+i*3+2) - *(picPtr+i*3+0)), 2));
                tmp+=(uint)pow(abs(ref - *(picPtr+positions[i]*3+(i+0)%3)), 2);
                tmp+=(uint)pow(abs(ref - *(picPtr+positions[i]*3+(i+1)%3)), 2);
                mse+=(double)tmp/3.0f;
            }
            //string name = makeName(al[a], r);
            //writePicture(dstPic,DATA_OU_PREF+name);
            //printf(" & %.3f",(double)mse/(data->size));
            printf(" & %.3f", 10*log10(pow(255, 2)/((double)mse/(data->size))));
            delete[] positions;
        }
        cout<<"\\\\\n";
    }
}