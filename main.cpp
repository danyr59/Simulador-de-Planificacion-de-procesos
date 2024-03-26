#include <iostream>
#include "process.h"
#include "fcfs.h"
#include "SJF.h"
#include "npps.h"
#include "ps.h"
#include "random_selection.h"
#include "RR.h"

int main()
{
    //std::cout << "hola";
    //Fcfs fcfs(8); 
    //fcfs.execute();
    //SJF sjf(7);
    //sjf.execute();
    RandomSelection randomselection(7);
    randomselection.execute();
    NPPS npps(10);
    npps.execute();
    RR rr;
    rr.execute();
    PS ps(10);
    ps.execute();
    
    return 0;
}
