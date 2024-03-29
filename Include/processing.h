#pragma once

#include <string>
#include <stdint.h>

#include "encoding.h"
#include "picture.h"
#include "encrypt.h"
#include "fileSystem.h"
#include "jobData.h"
#include "random.h"
#include "noiseGen.h"
#include "keyShaping.h"

std::string insertProcess(InsertJob* data, RandomGenerator* generator); //Returns signal for the process (0=success)

char* extractProcess(ExtractJob* data);
