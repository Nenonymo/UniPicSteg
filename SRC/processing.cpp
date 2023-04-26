#include "processing.h"

using namespace std;

unsigned int process(jobData* data, RandomGenerator* generator)
{
  //Open picture
    cv::Mat srcPic = loadPicture(DATA_IN_PREF+data->path);
    data->dims[0] = srcPic.rows; //Matrices dims are always row*col
    data->dims[1] = srcPic.cols;
    data->size = data->dims[0]*data->dims[1];


  //Noise picture
    cv::Mat dstPic = cv::Mat(srcPic.rows, srcPic.cols, CV_32FC1);
    srcPic.copyTo(dstPic);
    uint8_t* refChannels = generator->generateArray(data->size, 2);
    //unsigned int res = noise(data->size, picture, refChannels, data->alpha, generator);


  //Add data in the picture


  //export the picture
    writePicture(srcPic, DATA_OU_PREF+data->path);


  //Cleaning
    //delete data; //Will delete here when the creation of job data is automatic
    return 0;
}