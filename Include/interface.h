#pragma once

#include <iostream>
#include <stdint.h>
#include <cstdlib>

#include "jobData.h"

Job* inputJobArg(uint argc, char* argv[]);

void createImg(const char* name, unsigned int dims[2], uint8_t* array);