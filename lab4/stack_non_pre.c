#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int at;
    int priority;
    int bt;
};

struct Stack {
    struct Process* data;
    int top;
    int capacity;
};

struct Process* createProcess(int id, int at, int priority, int bt) {
    struct Process* process = (struct Process*)malloc(sizeof(struct Process));
    process->id = id;
    process->at = at;
    process->priority = priority;
    process->bt = bt;
    return process;
}

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->data = (struct Process*)malloc(capacity * sizeof(struct Process));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(struct Stack* stack, struct Process* process) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = *process;
}

struct Process* pop(struct Stack* stack) {
    if (stack->top == -1) {
        return NULL;
    }
    return &stack->data[stack->top--];
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Stack* processStack = createStack(n);

    struct Process* processes[n];

    for (int i = 0; i < n; i++) {
        int id, at, priority, bt;
        printf("Enter Process ID for process %d: ", i + 1);
        scanf("%d", &id);
        printf("Enter Arrival Time for process %d: ", i + 1);
        scanf("%d", &at);
        printf("Enter Priority for process %d: ", i + 1);
        scanf("%d", &priority);
        printf("Enter Burst Time for process %d: ", i + 1);
        scanf("%d", &bt);

        processes[i] = createProcess(id, at, priority, bt);
    }

    int currentTime = 0;
    int totalTAT = 0;
    int totalWT = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        while (completedProcesses < n && processes[completedProcesses]->at <= currentTime) {
            push(processStack, processes[completedProcesses]);
            completedProcesses++;
        }

        if (processStack->top == -1) {
            currentTime++;
        } else {
            struct Process* currentProcess = pop(processStack);
            int turnaroundTime = currentTime + currentProcess->bt - currentProcess->at;
            int waitingTime = turnaroundTime - currentProcess->bt;
            totalTAT += turnaroundTime;
            totalWT += waitingTime;

            printf("Process %d: Completion Time: %d, Turnaround Time: %d, Waiting Time: %d\n",
                   currentProcess->id, currentTime + currentProcess->bt, turnaroundTime, waitingTime);

            currentTime += currentProcess->bt;
        }
    }

    double avgTAT = (double)totalTAT / n;
    double avgWT = (double)totalWT / n;

    printf("Average Turnaround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);

    for (int i = 0; i < n; ++i) {
        free(processes[i]);
    }
    free(processStack->data);
    free(processStack);

    return 0;
}
