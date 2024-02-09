#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H
class CPUScheduler
{
public:
    virtual void schedule() = 0;
    virtual void calculateAverageWaitTime() = 0;
    virtual void calculateAverageTurnAroundTime() = 0;
    virtual ~CPUScheduler() {}
};

#endif
