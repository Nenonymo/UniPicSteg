#pragma once

#include <string>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include "constant.h"

unsigned long long power(uint16_t a, ushort b);

uint16_t* encode(uint8_t alpha, std::string message, uint &outputSize);

char* decode(uint8_t alpha, uint16_t* bits, uint32_t size);