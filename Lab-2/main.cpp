#include <iostream>
#include <iostream>
#include <queue>
#include <vector>
#include "schedulingalgorithms/CPUScheduler.h"
#include "schedulingalgorithms/FirstComeFirstServedScheduler.h"
#include "schedulingalgorithms/RoundRobinScheduler.h"
#include "schedulingalgorithms/Process.h"

using namespace std;

// Generate random processes with different arrival times
queue<Process> generateProcesses(int numberOfProcesses)
{
    queue<Process> processes;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        processes.push(Process(i + 1, rand() % 10 + 1, rand() % 10));
    }
    return processes;
}
int main()
{
    CPUScheduler *scheduler;

    // Init processes array
    queue<Process> processes_tc1 = generateProcesses(5);
    queue<Process> processes_tc2 = generateProcesses(10);

    cout << "##### TEST CASE #1 #####" << endl;

    cout << "##### First Come First Served Scheduling Algorithm: TEST CASE#1 #####" << endl;
    // TODO: Create a FirstComeFirstServedScheduler object and assign it to the scheduler pointer
    scheduler = new FirstComeFirstServedScheduler(processes_tc1, 0);
    // Run the scheduler
    scheduler->schedule();

    // Display average wait time and average turnaround time
    scheduler->calculateAverageWaitTime();
    scheduler->calculateAverageTurnAroundTime();

    cout << "###############################################\n";

    cout << "##### Round Robin Scheduling Algorithm: TEST CASE#1 #####" << endl;
    scheduler = new RoundRobinScheduler(processes_tc1, 2);
    // Run the scheduler
    scheduler->schedule();

    // Display average wait time and average turnaround time
    scheduler->calculateAverageWaitTime();
    scheduler->calculateAverageTurnAroundTime();

    cout << "###############################################\n";
    cout << "##### TEST CASE #2 #####" << endl;
    cout << "##### First Come First Served Scheduling Algorithm: TEST CASE#1 #####" << endl;
    // TODO: Create a FirstComeFirstServedScheduler object and assign it to the scheduler pointer
    scheduler = new FirstComeFirstServedScheduler(processes_tc2, 0);
    // Run the scheduler
    scheduler->schedule();

    // Display average wait time and average turnaround time
    scheduler->calculateAverageWaitTime();
    scheduler->calculateAverageTurnAroundTime();

    cout << "###############################################\n";

    cout << "##### Round Robin Scheduling Algorithm: TEST CASE#1 #####" << endl;
    scheduler = new RoundRobinScheduler(processes_tc2, 2);
    // Run the scheduler
    scheduler->schedule();

    // Display average wait time and average turnaround time
    scheduler->calculateAverageWaitTime();
    scheduler->calculateAverageTurnAroundTime();

    return 0;
}