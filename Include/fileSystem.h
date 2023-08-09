#pragma once

#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <string>
#include <filesystem>
#include "constant.h"

bool doesPathExist(std::string &path);
int createPath(std::string &path);
int createPathIfNotExist(std::string &path);
int rmFile(std::string &path);

cv::Mat loadPicture(std::string path);
bool writePicture(cv::Mat &img, std::string path);

std::string removeExtension(const std::string &filename);