#include "processing.h"

using namespace std;

unsigned int process(jobData* data, RandomGenerator* generator)
{
    //Open picture
    uint8_t* picture = new uint8_t[data->size*3];
    for (unsigned int pixel=0; pixel<data->size*3; pixel++)
    {picture[pixel]=128; }


    //Noise picture
    uint8_t* refChannels = generator->generateArray(data->size, 2);
    unsigned int res = noise(data->size, picture, refChannels, data->alpha, generator);
    for (unsigned int pixel=0; pixel<data->size; pixel++)
    {cout << (unsigned int)picture[pixel*3] << (unsigned int)picture[pixel*3+1] << (unsigned int)picture[pixel*3+2] << endl; }

    //Add data in the picture

    //export the picture
    cout << "Exporting picture" << endl;
    createImg(data->path.c_str(), data->dimensions, picture);


    

    //Cleaning
    delete[] picture;
    //delete data; //Will delete here when the creation of job data is automatic
    return 0;
}