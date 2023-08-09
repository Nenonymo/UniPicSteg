#pragma once

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>


#define PLJS_C1 0.7444196429f
#define PLJS_C2 0.6863839286f


template<typename T>
T* genRandArray(double z0, double a, double b, double c, double p, double w, uint len, T boundary);

template<typename T>
T* sampleUniqueUniform(uint l, T L, T* array);