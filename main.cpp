#include <iostream>
#include "process.h"
#include "fcfs.h"
#include "SJF.h"

int main()
{
    //std::cout << "hola";
    //Fcfs fcfs(8); 
    //fcfs.execute();
    SJF sjf(7);
    sjf.execute();
    
    return 0;
}