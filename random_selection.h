#ifndef __RANDOM_SELECTION__
#define __RANDOM_SELECTION__
#include <vector>
#include <algorithm>
#include "process.h"
#include "cpu.h"
#include "utils.h"
#include "base.h"

class RandomSelection : public Base {
private:
    //std::vector<sProcess> process_list; // Lista de todos los procesos
    std::vector<sProcess> blocked_process_queue; // Cola de procesos bloqueados

public:
    RandomSelection(int num_process);
    void execute(unsigned , unsigned ) override;
    bool is_done();
};

#endif
