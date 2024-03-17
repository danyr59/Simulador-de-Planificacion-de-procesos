#include <iostream>
#include "process.h"
#include "fcfs.h"
#include "SJF.h"
#include "random_selection.h"

int main()
{
    //std::cout << "hola";
    //Fcfs fcfs(8); 
    //fcfs.execute();
    //SJF sjf(7);
    //sjf.execute();
    RandomSelection randomselection(7);
    randomselection.execute();
    
    return 0;
}
