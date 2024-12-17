#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;       // Process ID
    int burst;    // CPU Burst time
    int waiting;  // Waiting time
};

void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waiting = 0; // First process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        processes[i].waiting = processes[i - 1].waiting + processes[i - 1].burst;
    }
}

float calculateAverageWaitingTime(struct Process processes[], int n) {
    float totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waiting;
    }

    return totalWaitingTime / n;
}

void printGanttChart(struct Process processes[], int n) {
    printf("Gantt Chart:\n| ");
    for (int i = 0; i < n; i++) {
        printf("P%d | ", processes[i].id);
    }
    printf("\n0  ");
    for (int i = 0; i < n; i++) {
        int endTime = processes[i].waiting + processes[i].burst;
        printf(" %d ", endTime);
    }
    printf("\n");
}

int main() {
    int n;

    // Request number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = malloc(n * sizeof(struct Process));

    // Input the CPU burst times for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Assign process ID
        printf("Enter CPU Burst time for Process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst);
    }

    calculateWaitingTime(processes, n);
    float avgWaitingTime = calculateAverageWaitingTime(processes, n);

    printGanttChart(processes, n);

    // Display waiting times
    printf("Waiting times:\n");
    for (int i = 0; i < n; i++) {
        printf("Waiting time for P%d = %d\n", processes[i].id, processes[i].waiting);
    }

    printf("Average Waiting Time = %.2f\n", avgWaitingTime);

    // Free allocated memory
    free(processes);

return 0;
}

