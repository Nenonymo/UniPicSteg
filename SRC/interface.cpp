#include "interface.h"

using namespace std;

Job* inputJobArg(uint argc, char** argv)
{
    if(argc<2) {cerr<<"Insufficient parameters"<<endl; std::exit(0); }
    int mode = std::string(argv[1]) == "i" ? 0 : (std::string(argv[1]) == "e" ? 1 : -1);
    if(mode==0) 
    {return new InsertJob(argc, argv); }
    else if(mode==1) 
    {return new ExtractJob(argc, argv); }
    else
    {cerr<<"Unknown mode"<<endl; std::exit(0); }
}

InsertJob::InsertJob(uint argc, char** argv)
{
    if(argc<5) {cerr<<"Insufficient parameters"<<endl; std::exit(0); }
    this->alpha=stoi(argv[4]);
    this->data=std::string(argv[3]);
    this->path=std::string(argv[2]);
    this->mode=0;
    if(argc>5) //If parameters are given
    {
        for(ushort i=5;i<argc;i++)
        {
            if(std::string(argv[i]).substr(0,2)=="-z") 
            {this->seed[0]=std::stod(std::string(argv[i]).substr(2)); }
            else if(std::string(argv[i]).substr(0,2)=="-a") 
            {this->seed[1]=std::stod(std::string(argv[i]).substr(2)); }
            else if(std::string(argv[i]).substr(0,2)=="-b") 
            {this->seed[2]=std::stod(std::string(argv[i]).substr(2)); }
            else if(std::string(argv[i]).substr(0,2)=="-c") 
            {this->seed[3]=std::stod(std::string(argv[i]).substr(2)); }
            else if(std::string(argv[i]).substr(0,2)=="-p") 
            {this->seed[4]=std::stod(std::string(argv[i]).substr(2)); }
            else if(std::string(argv[i]).substr(0,2)=="-w") 
            {this->seed[5]=std::stod(std::string(argv[i]).substr(2)); }
        }
    }
}

ExtractJob::ExtractJob(uint argc, char** argv)
{
    if(argc<4) {cerr<<"Insufficient parameters"<<endl; std::exit(0); }
    this->key=std::string(argv[3]);
    this->path=std::string(argv[2]);
    this->mode=1;
}

ExtractJob::~ExtractJob()
{}

InsertJob::~InsertJob()
{}

Job::~Job()
{/*Nothing happening here*/}