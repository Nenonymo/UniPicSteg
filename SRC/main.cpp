#include <processing.h>
#include <iostream>

#include "interface.h"
#include "processing.h"
#include "constant.h"
#include "fractal.h"
#include "test.h"

using namespace std;

int main (int argc, char** argv)
{
    RandomGenerator* generator = new RandomGenerator(SEED, 16);
    Job* job = inputJobArg(argc, argv);
    if(job->mode==0) //Insert data in the picture
    {   
        InsertJob* newjob = dynamic_cast<InsertJob*>(job);
        //printf("%s\n", insertProcess(newjob, generator).c_str());
        test(newjob);
    }
    else if(job->mode==1)
    {
        ExtractJob* newjob = dynamic_cast<ExtractJob*>(job);
        char* message=extractProcess(newjob); 
        printf("%s\n",message);
        delete[] message;
    }

    delete job;

    return 0;
}