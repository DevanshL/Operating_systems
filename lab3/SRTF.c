// L.DEVANSH CS21B2023

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int at;
    int bt;
    int rt;
    struct Process* next;
};

struct Queue {
    struct Process* front;
};

struct Process* createProcess(int id, int at, int bt) {
    struct Process* process = (struct Process*)malloc(sizeof(struct Process));
    process->id = id;
    process->at = at;
    process->bt = bt;
    process->rt = bt;
    process->next = NULL;
    return process;
}

void enqueue(struct Queue* queue, struct Process* process) {
    if (queue->front == NULL || process->rt < queue->front->rt) {
        process->next = queue->front;
        queue->front = process;
    } else {
        struct Process* temp = queue->front;
        while (temp->next != NULL && temp->next->rt <= process->rt) {
            temp = temp->next;
        }
        process->next = temp->next;
        temp->next = process;
    }
}

struct Process* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    struct Process* frontProcess = queue->front;
    queue->front = queue->front->next;
    return frontProcess;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Queue* processQueue = (struct Queue*)malloc(sizeof(struct Queue));
    processQueue->front = NULL;

    struct Process* processes[n];

    for (int i = 0; i < n; i++) {
        int id, at, bt;
        printf("Enter Process ID for process %d: ", i + 1);
        scanf("%d", &id);
        printf("Enter Arrival Time for process %d: ", i + 1);
        scanf("%d", &at);
        printf("Enter Burst Time for process %d: ", i + 1);
        scanf("%d", &bt);

        processes[i] = createProcess(id, at, bt);
    }

    int currentTime = 0;
    int completedProcesses = 0;
    int totalTAT = 0;
    int totalWT = 0;

    while (completedProcesses < n) {
        while (completedProcesses < n && processes[completedProcesses]->at <= currentTime) {
            enqueue(processQueue, processes[completedProcesses]);
            completedProcesses++;
        }

        if (processQueue->front == NULL) {
            currentTime++;
        } else {
            struct Process* currentProcess = dequeue(processQueue);
            currentProcess->rt--;

            if (currentProcess->rt == 0) {
                int turnaroundTime = currentTime - currentProcess->at + 1;
                int waitingTime = turnaroundTime - currentProcess->bt;
                totalTAT += turnaroundTime;
                totalWT += waitingTime;

                printf("Process %d: Completion Time: %d, Turnaround Time: %d, Waiting Time: %d\n",
                       currentProcess->id, currentTime, turnaroundTime, waitingTime);
            } else {
                enqueue(processQueue, currentProcess);
            }

            currentTime++;
        }
    }

    double avgTAT = (double)totalTAT / n;
    double avgWT = (double)totalWT / n;

    printf("Average Turnaround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);

    for (int i = 0; i < n; ++i) {
        free(processes[i]);
    }
    free(processQueue);

    return 0;
}
