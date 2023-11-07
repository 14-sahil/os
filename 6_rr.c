#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int processID; // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime; // Burst time of the process
    int remainingBurstTime; // Remaining burst time of the process
    int waitingTime; // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

// Function to perform Round Robin scheduling
void roundRobin(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0; // Current time
    int completedProcesses = 0; // Number of completed processes

    // Iterate until all processes are completed
    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and has remaining burst time
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0) {
                // Process the current time quantum or remaining burst time, whichever is smaller
                int executeTime = (processes[i].remainingBurstTime < timeQuantum) ? processes[i].remainingBurstTime : timeQuantum;
                currentTime += executeTime; // Update current time
                processes[i].remainingBurstTime -= executeTime; // Update remaining burst time

                // If the process is completed
                if (processes[i].remainingBurstTime == 0) {
                    completedProcesses += 1;
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                }
            }
        }
    }
}

int main() {
    int n, timeQuantum; // Number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    struct Process processes[n]; // Array to store processes

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].processID = i + 1;
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    // Perform Round Robin scheduling
    roundRobin(processes, n, timeQuantum);

    // Output the turnaround time and waiting time for each process
    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].processID, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    return 0;
}

//4
//2
//0 5
//1 4
//2 2
//4 1