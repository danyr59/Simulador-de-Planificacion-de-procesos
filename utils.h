#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>

unsigned generateRandomNum(int min, int max) 
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

#endif