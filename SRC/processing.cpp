#include "processing.h"

using namespace std;

std::string insertProcess(InsertJob* data, RandomGenerator* generator)
{
  //Open picture
    cv::Mat srcPic = loadPicture(DATA_IN_PREF+data->path);
    data->dims[0] = srcPic.rows; //Matrices dims are always row*col
    data->dims[1] = srcPic.cols;
    data->size = data->dims[0]*data->dims[1];
    
  //Encode the data
    uint encSize;
    uint16_t* coded=encode(data->alpha, data->data, encSize);

  //Encrypt: generate positions
    uint32_t* randSeq = generatePosition(data->size, encSize, data->seed);
    uint32_t* positions = sampleUniqueUniform(encSize, data->size, randSeq);
    //for(uint i=0;i<encSize;i++){printf("(%d %d) ",randSeq[i],positions[i]); } cout<<endl;
    delete[] randSeq;

  //Add data in the picture
    insertEncoded(srcPic, encSize, positions, coded, data->alpha);
    delete[] coded;
    delete[] positions;

  //Noise picture
    /*uint8_t* refChannels = generator->generateArray(data->size, 0);
    if (noise(dstPic, refChannels, data->alpha, generator))
    {cerr<<"Error on the noising of the picture!"<<endl;}*/

  //export the picture
    writePicture(srcPic,DATA_OU_PREF+removeExtension(data->path)+EXTENSION);

  //Generate the key
    KeyData keyData;
    keyData.alpha=data->alpha;
    keyData.len=encSize;
    std::copy(data->seed, data->seed + 6, keyData.seed);
    std::string key=serialize(keyData);

  //Cleaning
    return key;
}

char* extractProcess(ExtractJob* data)
{
  //Interpret key
    KeyData key=deserialize(data->key);

  //Open picture
    cv::Mat srcPic = loadPicture(DATA_OU_PREF+data->path);
    data->dims[0] = srcPic.rows; //Matrices dims are always row*col
    data->dims[1] = srcPic.cols;
    data->size = data->dims[0]*data->dims[1];

  //Generate the position array
    uint32_t* randSeq = generatePosition(data->size, key.len, key.seed);
    uint32_t* positions = sampleUniqueUniform(key.len, data->size, randSeq);
    delete[] randSeq;

  //Grab the data from the picture
    uint16_t* decoded=grabEncoded(srcPic,key.len,positions,key.alpha);
    delete[] positions;

  //decode the data
    char* message=decode(key.alpha,decoded,key.len);

  //Cleaning
    delete[] decoded;
    return message;
}