#include "interface.h"

using namespace std;


/* Lots of issue to fix to make it work with a file
jobData* inputJobStram(std::istream& inStream, std::ostream& outStream, std::ostream& errStream)
{
    jobData* output = new jobData;

    string workString;

    //First, the path to the picture
    inStream >> workString;
    output->path = workString.str();

    //Dimensions and size of the picture
    inStream >> output->dimensions[0] >> output->dimensions[1];
    output->size = output->dimensions [0] * output->dimensions[1];

    //Alpha
    inStream >> output->alpha;

    //Data
    inStream >> workString;
    output->data = workString.str();

    //Key
    inStream >> workString;
    output->key = workString.str();

    return output;
}*/

jobData* inputJobConsole()
{
    jobData* output = new jobData;

    //First, the path to the picture
    cin >> output->path;

    //Dimensions and size of the picture
    cin >> output->dimensions[0] >> output->dimensions[1];
    output->size = output->dimensions [0] * output->dimensions[1];

    //Alpha
    cin >> output->alpha;

    //Data
    cin >> output->data;

    //Key
    cin >> output->key;

    return output;
}

void createImg(const char* name, unsigned int dims[2], uint8_t* array)
{
    FILE *fout = fopen(name, "wb");
    fprintf(fout, "P6\n %s\n %d\n %d\n %d\n", "# no comment", dims[0], dims[1], 1);
    fwrite(array, 3*sizeof(uint8_t), dims[0]*dims[1], fout);
    fclose(fout);
}