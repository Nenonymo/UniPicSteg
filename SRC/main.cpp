#include <processing.h>
#include <iostream>

#include "interface.h"
#include "processing.h"
#include "constant.h"


using namespace std;

int main (int argc, char** argv)
{
    RandomGenerator* generator = new RandomGenerator(SEED, 16);
    jobData* data = inputJobConsole();

    cout << "job data inputed" << endl;
    if (process(data, generator) != 0) 
    {cerr << "Process did not go as intended"; }

    delete data;

    return 0;
}