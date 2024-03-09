#ifndef __CPU__
#define __CPU__
#include "process.h"

class cpu
{
private:
    unsigned tick;
    
public:
    cpu(/* args */);
    ~cpu();
};

#endif