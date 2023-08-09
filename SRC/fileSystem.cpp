#include "fileSystem.h"


bool doesPathExist(std::string &path)
{
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

int createPath(std::string &path)
{
    std::string command = "mkdir -p " + path;
    int output = system(command.c_str());
    return output;
}

int createPathIfNotExist(std::string &path)
{
    if (doesPathExist(path)) {return 0; }
    else
    {
        if (createPath(path) == 0) {return 1; }
        return 2;
    }
}

int rmFile(std::string &path)
{remove(path.c_str()); return 0; }

cv::Mat loadPicture(std::string path)
{
    if (doesPathExist(path)==0) 
    {
        std::cerr<<"Error, file not found."<<std::endl; 
        exit(0);
    }
    cv::Mat output = cv::imread(path.c_str(), cv::IMREAD_COLOR);
    return output;
}

bool writePicture(cv::Mat &img, std::string path)
{
    return imwrite(path.c_str(), img);
}

std::string removeExtension(const std::string& filename) 
{
    return std::filesystem::path(filename).stem().string();
}