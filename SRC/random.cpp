RandomGenerator::RandomGenerator(unsigned int seed, unsigned int maxVal) 
                :seed(seed)
{
    srand(this->seed());
    this->maxVal=maxVal;
}

void RandomGenerator::setMaxVal(unsigned int maxVal, unsigned int open)
{
    this->maxVal = maxVal + open;
}

unsigned int generateRandInt()
{return (rand()%this->maxVal); }

uint8_t generateArray(unsigned int size, unsigned int maxVal)
{
    uint8_t* array = new uint8_t[size];
    for (unsigned int index=0; index<size; index++)
    {array[index]=rand()%(maxVal+1); }
}

uint8_t generateDifference(uint8_t alpha, uint8_t value)
{return value-alpha+(rand()%(2*alpha+2)); }