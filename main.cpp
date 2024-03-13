#include <iostream>
#include "process.h"
#include "fcfs.h"

int main()
{
    //std::cout << "hola";
    Fcfs fcfs(8); 
    fcfs.execute();
    return 0;
}