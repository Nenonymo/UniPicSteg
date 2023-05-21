#include "processing.h"

using namespace std;

unsigned int process(jobData* data, RandomGenerator* generator)
{
  //Open picture
    cv::Mat srcPic = loadPicture(DATA_IN_PREF+data->path);
    data->dims[0] = srcPic.rows; //Matrices dims are always row*col
    data->dims[1] = srcPic.cols;
    data->size = data->dims[0]*data->dims[1];

    cout << "Message: " << data->data.c_str() << endl;

  //Encode the data
    uint encSize;
    uint16_t* coded=encode(data->alpha, data->data, encSize);
    cout<<"Inserted array: ";
    for(uint i=0;i<encSize;i++) {cout<<(int)coded[i]<<" "; }
    cout<<"\n";

  //Add data in the picture
    cv::Mat dstPic = cv::Mat(srcPic.rows, srcPic.cols, CV_32FC1);
    srcPic.copyTo(dstPic);
    uint32_t* positions = generateRangeSample(data->key, data->size, encSize);
    insertEncoded(dstPic, encSize, positions, coded, data->alpha);

  //Noise picture
    /*uint8_t* refChannels = generator->generateArray(data->size, 0);
    if (noise(dstPic, refChannels, data->alpha, generator))
    {cerr<<"Error on the noising of the picture!"<<endl;}*/

  //Grab the data from the picture
    uint16_t* decoded=grabEncoded(dstPic,encSize,positions,data->alpha);
    cout<<"Extracted array: ";
    for(uint i=0;i<encSize;i++) {cout<<(int)decoded[i]<<" "; }
    cout<<"\n";

  //decode the data
    char* message=decode(data->alpha, decoded, encSize);
    printf("Decoded message: %s\n", message);

  //export the picture
    writePicture(dstPic, DATA_OU_PREF+data->path);

  //Cleaning
    delete[] positions;
    return 0;
}