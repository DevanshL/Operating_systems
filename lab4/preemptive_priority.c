#include <stdio.h>
#include <stdlib.h>

struct priority {
    int id;
    int at;
    int pr;
    int bt;
    int rt;
};

struct Queue {
    int front, rear;
    int capacity;
    struct priority** array;
};

struct priority* createProcess(int id, int at, int priority, int bt) {
    struct priority* process = (struct priority*)malloc(sizeof(struct priority));
    process->id = id;
    process->at = at;
    process->pr = priority;
    process->bt = bt;
    process->rt = bt;
    return process;
}

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (struct priority**)malloc(capacity * sizeof(struct priority*));
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, struct priority* process) {
    if (queue->rear == queue->capacity - 1) {
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->array[++queue->rear] = process;
}

struct priority* dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return NULL;
    struct priority* process = queue->array[queue->front++];
    if (queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return process;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p_id[100];
    int arrival_time[100];
    int priority[100];
    int burst_time[100];
    
    for (int i = 0; i < n; i++) {
        printf("Enter p_id %d : ", i + 1);
        scanf("%d", &p_id[i]);
        printf("Enter arrival_time %d : ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter priority %d : ", i + 1);
        scanf("%d", &priority[i]);
        printf("Enter burst_time %d : ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    struct priority* processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i] = createProcess(p_id[i], arrival_time[i], priority[i], burst_time[i]);
    }

    struct Queue* processQueue = createQueue(n);

    int currentTime = 0;
    int completedProcesses = 0;
    int total_tat = 0;
    int total_wt = 0;
    int total_rt = 0;

    while (completedProcesses < n) {
        int selectedProcess = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i]->at <= currentTime && processes[i]->rt > 0) {
                if (selectedProcess == -1 || processes[i]->pr < processes[selectedProcess]->pr) {
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess == -1) {
            currentTime++;
        } else {
            struct priority* currentProcess = processes[selectedProcess];
            currentProcess->rt--;
            currentTime++;

            if (currentProcess->rt == currentProcess->bt - 1) {
                total_rt += currentTime - currentProcess->at;
            }

            if (currentProcess->rt == 0) {
                completedProcesses++;
                total_tat += currentTime - currentProcess->at;
                total_wt += currentTime - currentProcess->at - currentProcess->bt;
                printf("Process %d: Completion Time: %d, Turnaround Time: %d, Waiting Time: %d, Response Time: %d\n",
                       currentProcess->id, currentTime,
                       currentTime - currentProcess->at,
                       currentTime - currentProcess->at - currentProcess->bt,
                       currentTime - currentProcess->at - currentProcess->bt);
            } else {
                enqueue(processQueue, currentProcess);
            }
        }
    }

    double avg_tat = (double)total_tat / n;
    double avg_wt = (double)total_wt / n;
    double avg_rt = (double)total_rt / n;

    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Response Time: %.2f\n", avg_rt);

    for (int i = 0; i < n; ++i) {
        free(processes[i]);
    }
    free(processQueue->array);
    free(processQueue);

    return 0;
}
