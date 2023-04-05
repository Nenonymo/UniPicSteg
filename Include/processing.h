#include <string>
#include <opencv2/opencv.hpp>

using namespace std;

typedef struct jobData
{
    char* path;
    unsigned int size[2];
    unsigned int alpha;
    char* data;
    char* key;
} jobData;


char* process(jobData* data); //Returns path to modified picture