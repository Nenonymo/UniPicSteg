#pragma once
#include <opencv2/opencv.hpp>
#include <cmath>

#include "constant.h"

void highlightPixels(cv::Mat &pic, uint size, uint* positions);

void insertEncoded(cv::Mat &pic, uint size, uint32_t* positions, uint16_t* encoded, uint8_t alpha);

uint16_t* grabEncoded(cv::Mat &pic, uint size, uint32_t* positions, uint8_t alpha);