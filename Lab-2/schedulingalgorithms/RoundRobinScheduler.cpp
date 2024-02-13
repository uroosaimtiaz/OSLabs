#include "RoundRobinScheduler.h"
#include <algorithm> // Added to use the sort function

RoundRobinScheduler::RoundRobinScheduler(queue<Process> processes, int quantum)
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

/*  Schedule the processes using Round Robin scheduling algorithm
    The processes are sorted by arrival time using the sort function from the
    algorithm library. The processes queue is then iterated through and the
    processes are executed for a time quantum. If the process is not completed,
    it will be pushed to the back of the queue. If the process is completed, the
    wait time will be calculated and the process will be removed from the queue.
    The time variable is used to keep track of the current time in the simulation,
    while the done variable is used to keep track of the number of processes completed
    which determines when the simulation ends.
*/
void RoundRobinScheduler::schedule()
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

    int numProcesses = processes.size(); // Total number of processes
    queue<Process> completedProcesses; // Create a separate queue to store the completed processes

    // Now, we will simulate the Round Robin scheduling algorithm
    while (!processes.empty()){
        Process currentProcess = processes.front();
        if (currentProcess.arrivalTime > time) { // If the process has not arrived yet
            // printf("Current Time: %d, No process in the queue.\n", time);
            time++; // Increment the time by minimum 1 unit
            continue;
        }
        else {
            // printf("Process %d is loaded at time %d and will start executing\n", currentProcess.id, time);
        }
        processes.pop();
        int executionTime = min(currentProcess.remainingTime, quantum);
        // printf("Process %d is executing at time %d for %d units\n", currentProcess.id, time, executionTime);
        time += executionTime;
        currentProcess.remainingTime -= executionTime;
        if (currentProcess.remainingTime == 0) { // Process completed
            // Wait time = Current time - Arrival time - Burst time
            currentProcess.waitTime = time - currentProcess.arrivalTime - currentProcess.burstTime;
            // printf("Process complete. Current Time: %d, Arrival Time: %d, Burst Time: %d, Wait Time %d\n", time, currentProcess.arrivalTime, currentProcess.burstTime, currentProcess.waitTime);
            currentProcess.remainingTime = 0;
            // Add the completed process to the completedProcesses queue
            completedProcesses.push(currentProcess);
        } else {
            //printf("Process %d is not complete. Remaining Time: %d\n", currentProcess.id, currentProcess.remainingTime);
            processes.push(currentProcess); // Push the updated process to the back of the queue
        }
    }

    // Add the completed processes back to the processes queue
    while (!completedProcesses.empty()) {
        processes.push(completedProcesses.front());
        completedProcesses.pop();
    }
}

/*  To calculate the average wait time, iterate through the  processes
    and calculate the total wait time. Then, divide the total wait time by
    the number of processes to get the average wait time.
*/
void RoundRobinScheduler::calculateAverageWaitTime()
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

/*  To calculate the average turn around time, iterate through the 
    processes queue and calculate the total turn around time by adding the
    wait time and burst time of each process. Then, divide the total turn 
    around time by the number of processes to get the average.
*/
void RoundRobinScheduler::calculateAverageTurnAroundTime()
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