#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H

#include <queue>
#include "Process.h"
#include "CPUScheduler.h"
using namespace std;

class RoundRobinScheduler : public CPUScheduler
{
public:
    RoundRobinScheduler(queue<Process> processes, int quantum);
    void schedule() override;
    void calculateAverageWaitTime() override;
    void calculateAverageTurnAroundTime() override;

    private:
    queue<Process> processes;
    int quantum;
};

#endif
