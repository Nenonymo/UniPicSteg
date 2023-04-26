#pragma once

#include <stdint.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "random.h"


unsigned int noise(cv::Mat &pic, uint8_t* refChannels, uint8_t alpha, RandomGenerator* generator);