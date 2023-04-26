#include "processing.h"

using namespace std;

unsigned int process(jobData* data, RandomGenerator* generator)
{
  //Open picture
    cv::Mat srcPic = loadPicture(DATA_IN_PREF+data->path);
    data->dims[0] = srcPic.rows; //Matrices dims are always row*col
    data->dims[1] = srcPic.cols;
    data->size = data->dims[0]*data->dims[1];

    cout << "Alpha = " << data->alpha << endl;

  //Noise picture
    cv::Mat dstPic = cv::Mat(srcPic.rows, srcPic.cols, CV_32FC1);
    srcPic.copyTo(dstPic);
    uint8_t* refChannels = generator->generateArray(data->size, 2);
    if (noise(dstPic, refChannels, data->alpha, generator))
    {cerr<<"Error on the noising of the picture!"<<endl;}


  //Add data in the picture


  //export the picture
    writePicture(dstPic, DATA_OU_PREF+data->path);


  //Cleaning
    //delete data; //Will delete here when the creation of job data is automatic
    return 0;
}