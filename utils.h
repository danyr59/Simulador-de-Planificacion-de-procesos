#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <chrono>
#include <thread>

typedef unsigned short int ushort;

unsigned generateRandomNum(int min, int max);

//sleep for time milliseconds
void sleep(unsigned time);

#endif
