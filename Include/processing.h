#pragma once

#include <string>
#include <stdint.h>

#include "interface.h"
#include "fileSystem.h"
#include "jobData.h"
#include "random.h"
#include "noiseGen.h"

using namespace std;

unsigned int process(jobData* data, RandomGenerator* generator); //Returns signal for the process (0=success)