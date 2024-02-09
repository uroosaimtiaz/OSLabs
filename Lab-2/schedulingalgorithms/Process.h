
struct Process
{
    int id;        // Process ID
    int burstTime; // CPU Burst Time
    int arrivalTime;
    int waitTime;
    int remainingTime;

    Process(int id, int burstTime) : id(id), burstTime(burstTime) {}
    Process(int id, int burstTime, int arrivalTime) : id(id), burstTime(burstTime), arrivalTime(arrivalTime) {}
};