// L Devansh CS21B2023

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
    struct Process* rear;
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

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, struct Process* process) {
    if (queue->rear == NULL) {
        queue->front = queue->rear = process;
    } else {
        queue->rear->next = process;
        queue->rear = process;
    }
}

struct Process* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    struct Process* frontProcess = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return frontProcess;
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Queue* processQueue = createQueue();
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
        enqueue(processQueue, processes[i]);
    }

    int currentTime = 0;
    int totalTAT = 0;
    int totalWT = 0;

    while (processQueue->front != NULL) {
        struct Process* currentProcess = dequeue(processQueue);

        if (currentProcess->rt > quantum) {
            currentProcess->rt -= quantum;
            currentTime += quantum;
            enqueue(processQueue, currentProcess);
        } else {
            currentTime += currentProcess->rt;
            currentProcess->rt = 0;
            int turnaroundTime = currentTime - currentProcess->at;
            int waitingTime = turnaroundTime - currentProcess->bt;
            totalTAT += turnaroundTime;
            totalWT += waitingTime;

            printf("Process %d: Completion Time: %d, Turnaround Time: %d, Waiting Time: %d\n",
                   currentProcess->id, currentTime, turnaroundTime, waitingTime);
        }

        while (processQueue->front != NULL && processQueue->front->at <= currentTime) {
            enqueue(processQueue, dequeue(processQueue));
        }

        if (currentProcess->rt > 0) {
            enqueue(processQueue, currentProcess);
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
