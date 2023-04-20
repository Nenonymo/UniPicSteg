#pragma once

#include <iostream>
#include <stdint.h>

#include "jobData.h"

jobData* inputJobStream(std::istream& inStream, std::ostream& outStream, std::ostream& errStream);
jobData* inputJobConsole();


void createImg(const char* name, unsigned int dims[2], uint8_t* array);