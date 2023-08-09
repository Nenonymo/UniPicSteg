#pragma once

#include <cstring>
#include <string>
#include <iostream>

#include "base64.h"

typedef struct KeyData
{
    uint8_t alpha;
    uint32_t len;
    double seed[6];
} KeyData;

std::string serialize(const KeyData& key);

KeyData deserialize(const std::string& str);