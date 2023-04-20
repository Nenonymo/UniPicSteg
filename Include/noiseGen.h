#pragma once

#include <stdint.h>
#include <iostream>

#include "random.h"


unsigned int noise(unsigned int size, uint8_t* array, uint8_t* refChannels, uint8_t alpha, RandomGenerator* generator);