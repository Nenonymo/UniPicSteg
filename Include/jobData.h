#pragma once

#include <string>


class Job
{
    public:
        virtual ~Job();
        uint mode;
        std::string path;
        unsigned int dims[2]; //Automatially computed
        unsigned int size; //Same
};

class InsertJob: public Job
{
    public:
        InsertJob(uint argc, char** argv);
        ~InsertJob();
        uint8_t alpha;
        std::string data;
        double seed[6] = {.09f, 2.0f, 1.0f, .0f, -0.03f, 3.0f};
};

class ExtractJob: public Job 
{
    public:
        ExtractJob(uint argc, char** argv);
        ~ExtractJob();
        std::string key;
};
