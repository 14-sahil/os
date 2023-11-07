#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int processID; // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime; // Burst time of the process
    int remainingTime; // Remaining burst time of the process
    int waitingTime; // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
    int isCompleted; // Flag to indicate whether the process is completed or not
};

// Function to perform Shortest Job First (Preemptive) scheduling
void shortestJobFirst(struct Process processes[], int n) {
    int currentTime = 0; // Current time
    int completedProcesses = 0; // Number of completed processes

    while (completedProcesses < n) {
        int shortestJobIndex = -1; // Index of the process with the shortest remaining burst time

        // Find the process with the shortest remaining burst time among the arrived processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].isCompleted == 0) {
                if (shortestJobIndex == -1 || processes[i].remainingTime < processes[shortestJobIndex].remainingTime) {
                    shortestJobIndex = i;
                }
            }
        }

        // If a process is found
        if (shortestJobIndex != -1) {
            // Update current time and process information
            currentTime += 1;
            processes[shortestJobIndex].remainingTime -= 1;

            // If the process is completed
            if (processes[shortestJobIndex].remainingTime == 0) {
                completedProcesses += 1;
                processes[shortestJobIndex].isCompleted = 1;
                processes[shortestJobIndex].turnaroundTime = currentTime - processes[shortestJobIndex].arrivalTime;
                processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
            }
        }
        // If no process is available, move to the next time unit
        else {
            currentTime += 1;
        }
    }
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n]; // Array to store processes

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].processID = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = 0;
    }

    // Perform Shortest Job First (Preemptive) scheduling
    shortestJobFirst(processes, n);

    // Output the turnaround time and waiting time for each process
    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].processID, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    return 0;
}

//4
// 0 5
// 1 3
// 2 4
// 4 1