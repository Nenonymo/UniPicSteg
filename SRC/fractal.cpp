#include "fractal.h"

using namespace std;



/*********
 * TOOLS *
 *********/

typedef struct param
{
    double z;
    double a;
    double b;
    double c;
    double w;
    double p;
} param;

typedef complex<double> comp;

template <typename T> T mod(uint64_t a, T b)
{return ((a%b<0)?a%b+b:a%b); }



/*********************
 * FRACTAL FUNCTIONS *
 *********************/

comp cPLMS(param& par, comp z, comp z_)
{
    comp tempZ = pow(z, par.a) + pow(z, par.b)*par.c + par.p*z_;
    return par.c*tempZ*pow(comp(1-tempZ.real(),-tempZ.imag()), par.w-1);
}

comp cPLJS(param& par, comp z, comp z_, comp c)
{
    comp tempZ = pow(z, par.a) + pow(z, par.b)*c + par.p*z_;
    return c*tempZ*pow(comp(1-tempZ.real(), -tempZ.imag()), par.w-1);
}

uint fixedPointIter(comp initial, param par, double tolerance, uint maxIterations, comp c)
{
    comp x = initial;
    comp prevX = x;
    comp prevprevX = x;
    uint iterations=0;
    do
    {
        prevprevX = prevX;
        prevX = x;
        x = cPLJS(par, prevX, prevprevX, c);
        iterations++;
    }
    while (abs(x-prevX) > tolerance && iterations < maxIterations);
    return iterations;
}




/**********************************
 * PSEUDO RANDOM NUMBER GENERATOR *
 **********************************/
template<typename T>
T* genRandArray(double z0, double a, double b, double c, double p, double w, uint len, T boundary)
{
  //Create parameters struct
    param par;
    par.z=z0;
    par.a=a;
    par.b=b;
    par.c=c;
    par.p=p;
    par.w=w;
    //Initialize the Julia Set c parameter from the constant
    comp pljsC(PLJS_C1, PLJS_C2);
    comp inZ(z0,0);

  //Initialize the process
    comp zdataMS = cPLMS(par, inZ, inZ);
    comp zdataJS = cPLJS(par, inZ, inZ, pljsC);
    comp oldzdataMS = inZ;
    comp oldzdataJS = inZ;
    comp tmp;

    uint n=ceil(float(len/2));

    T* prng=new T[n*2];
    uint iter = fixedPointIter(zdataJS, par, 0.0008f, 10000, comp(c));
    comp uSeq;

  //Start the generation
    //Once we reach i=iter we should change the parameters a certain way and start again, to avoid reaching the point where we converge
    for (uint j=0; j<n; j++)
    {
        //Update parameters if we reach convergence point
        if(j*2>=iter)
        {
            par.z*=-1.000012f;
            par.a+=0.00000031f;
            par.b+=0.0000001176f;
            par.p*=-1.0000000001f;
            par.w+=0.00003f;
            inZ = comp(par.z, 0);

            zdataMS = cPLMS(par, inZ, inZ);
            zdataJS = cPLJS(par, inZ, inZ, pljsC);
            oldzdataMS = inZ;
            oldzdataJS = inZ;
            iter = 2*j + fixedPointIter(zdataJS, par, 0.001f, 10000, comp(par.c));
        }
        uSeq = (double)iter * zdataMS + zdataJS;
        double uRealSeq=zdataMS.real() * iter + zdataJS.real();
        double uImagSeq=zdataMS.imag() * iter + zdataJS.imag();

        prng[2*j] = mod<T>((uint64_t)round(uRealSeq * pow(2, 14)), boundary);
        prng[2*j+1] = mod<T>((uint64_t)round(uImagSeq * pow(2, 14)), boundary);

        tmp = oldzdataMS;
        oldzdataMS = zdataMS;
        zdataMS = cPLMS(par, zdataJS, tmp);

        tmp = oldzdataJS;
        oldzdataJS = zdataJS;
        zdataJS = cPLJS(par, zdataMS, tmp, pljsC);
    }
    
    return prng;
}

template<typename T>
T* sampleUniqueUniform(uint l, T L, T* array)
{
    vector<T> pixels; //vector for range [0; L] (size of picture)
    for(uint i=0;i<L;i++) {pixels.push_back(i); } //Init vector
    T* output = new T[l];
    T s=L;
    for (uint i=0;i<l;i++)
    {
        output[i]=pixels[floor((double)array[i]/L * pixels.size())];
        pixels.erase(pixels.begin() + (uint)floor(((double)(array[i])/L) * s));
        s--;
    }
    return output;
}



/*******************************************
 * EXPLICIT INSTANCIATION OF THE TEMPLATES *
 *******************************************/

//mod
template uint8_t mod(uint64_t a, uint8_t b);
template uint16_t mod(uint64_t a, uint16_t b);
template uint32_t mod(uint64_t a, uint32_t b);
template uint64_t mod(uint64_t a, uint64_t b);

//genRandArray
template uint8_t* genRandArray<uint8_t>(double z0, double a, double b, double c, double p, double w, uint len, uint8_t boundary);
template uint16_t* genRandArray<uint16_t>(double z0, double a, double b, double c, double p, double w, uint len, uint16_t boundary);
template uint32_t* genRandArray<uint32_t>(double z0, double a, double b, double c, double p, double w, uint len, uint32_t boundary);
template uint64_t* genRandArray<uint64_t>(double z0, double a, double b, double c, double p, double w, uint len, uint64_t boundary);

//sampleUniqueUniform
template uint8_t* sampleUniqueUniform(uint l, uint8_t L, uint8_t* array);
template uint16_t* sampleUniqueUniform(uint l, uint16_t L, uint16_t* array);
template uint32_t* sampleUniqueUniform(uint l, uint32_t L, uint32_t* array);
template uint64_t* sampleUniqueUniform(uint l, uint64_t L, uint64_t* array);