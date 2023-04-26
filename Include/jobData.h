#pragma once

#include <string>

typedef struct jobData
{
    std::string path;
    unsigned int dims[2];
    unsigned int size;
    uint8_t alpha;
    std::string data;
    std::string key;
} jobData;