#pragma once

#include <string>

#include "fractal.h"

uint32_t* positionLattice(std::string key, uint rangeSize, uint sampleSize);

uint32_t* generatePosition(uint32_t boundary, uint length, double seed[6]);