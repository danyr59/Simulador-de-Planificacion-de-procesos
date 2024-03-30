#ifndef __RR__
#define __RR__

#include <queue>
#include <vector>
#include <algorithm>
#include "process.h"
#include "cpu.h"
#include "base.h"

// Round Robin
class RR : public Base
{
public:
    RR();
    RR(unsigned );
    std::queue<sProcess> process_queue;
    std::queue<sProcess> bloqued_process_queue;
    //std::vector<sProcess> process_list;

    void execute(); 
    //bool is_done();
};

#endif