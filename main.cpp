#include <iostream>
#include "process.h"
#include "fcfs.h"

int main()
{
    Fcfs fcfs(8); 
    fcfs.execute();
    return 0;
}