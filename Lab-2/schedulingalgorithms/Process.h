// Added an include guard to prevent multiple inclusions of this header file,
// which was causing a "redefinition of 'Process'" error during compilation.

#ifndef PROCESS_H
#define PROCESS_H

struct Process
{
    int id;
    int burstTime;
    int arrivalTime;
    int waitTime;
    int remainingTime;

    Process(int id, int burstTime) : id(id), burstTime(burstTime) {}
    Process(int id, int burstTime, int arrivalTime) : id(id), burstTime(burstTime), arrivalTime(arrivalTime) {}
};

#endif