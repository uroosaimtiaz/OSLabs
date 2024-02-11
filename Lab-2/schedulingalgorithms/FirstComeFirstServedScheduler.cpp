#include "FirstComeFirstServedScheduler.h"
#include <algorithm> // std::sort

FirstComeFirstServedScheduler::FirstComeFirstServedScheduler(queue<Process> processes, int quantum)
{
    this->quantum = quantum;
    queue<Process> tempQueue;
    while (!processes.empty()) {
        Process p = processes.front();
        processes.pop();
        p.remainingTime = p.burstTime; // Ensure remainingTime is initialized
        tempQueue.push(p);
    }
    this->processes = tempQueue; // Assign the updated queue to the member variable
}

/*  Schedule the processes using First Come First Served scheduling algorithm
    The sort function from the algorithm library is used to sort the processes by arrival time.
    Then the processes queue is iterated through and the processes are executed in the order
    they arrive. The time variable is used to keep track of the current time in the simulation,
    which is complete when the queue is empty.
    The wait time is the time the process is in the queue before starting execution,
    which is calculated by the time elpased since the process arrived and current time
    minus the time it was executing (burst time).
*/
void FirstComeFirstServedScheduler::schedule()
{
    int time = 0; // Current time in the simulation starts at 0

    // Sort the processes by arrival time
    vector<Process> tempVector; // temporary vector to store the processes
    while (!processes.empty()) {
        Process p = processes.front(); // Get the front process
        tempVector.push_back(p); // Push the process to the vector
        processes.pop(); // Remove the process from the queue
    }
    // Sort the processes by arrival time using sort() and a lambda function
    sort(tempVector.begin(), tempVector.end(), [](const Process& a, const Process& b)
        { return a.arrivalTime < b.arrivalTime; });
    // Add back the processes to the queue in sorted order
    for (int i = 0; i < tempVector.size(); i++) {
        processes.push(tempVector[i]);
    }

    queue<Process> tempQueue; // Temporary queue to store the updated processes

    while (!processes.empty()) {
        Process currentProcess = processes.front();
        time += currentProcess.burstTime;
        // Calculate the wait time for the current process using the formula:
        // Wait Time = Time Elapsed Since Process Arrived - Time it was executing
        currentProcess.waitTime = time - currentProcess.arrivalTime;
        currentProcess.remainingTime = 0;
        processes.pop();
        tempQueue.push(currentProcess); // Push the updated process to the temporary queue
    }

    processes = tempQueue; // Replace the original queue with the updated one
}

/*  Calculate the average wait time for the processes
    The processes queue is iterated through and the wait time for each process is added
    to the total wait time. The average wait time is then calculated and printed.
*/
void FirstComeFirstServedScheduler::calculateAverageWaitTime()
{
    int totalWaitTime = 0;
    queue<Process> tempQueue = processes; // Create a temporary queue to store the processes   

    while (!tempQueue.empty()) {
        Process currentProcess = tempQueue.front();
        totalWaitTime += currentProcess.waitTime;
        tempQueue.pop();
    }
    // Calculate the average wait time as a double and print it
    double averageWaitTime = static_cast<double>(totalWaitTime) / processes.size();
    printf("Average Wait Time: %.2f\n", averageWaitTime);
}

/*  Calculate the average turn around time for the processes
    The processes queue is iterated through and the total turn around time is calculated
    by adding the wait time and burst time for each process. The average turn around time
    is then calculated and printed.
*/
void FirstComeFirstServedScheduler::calculateAverageTurnAroundTime()
{
    int totalTurnAround = 0;
    queue<Process> tempQueue = processes; // Create a temporary queue to store the processes   

    while (!tempQueue.empty()) {
        Process currentProcess = tempQueue.front();
        totalTurnAround += currentProcess.waitTime + currentProcess.burstTime;
        tempQueue.pop();
    }
    // Calculate the average turn around time as a double and print it
    // Turnaround Time = Wait Time + Burst Time
    double averageTurnAround = static_cast<double>(totalTurnAround) / processes.size();
    printf("Average Turn Around Time: %.2f\n", averageTurnAround);
}