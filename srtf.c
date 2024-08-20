#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitTime;
    int turnaroundTime;
    int completionTime;
} Process;

void sortProcessesByArrivalTime(Process proc[], int n)
{
    int i, j;
    Process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (proc[i].arrivalTime > proc[j].arrivalTime)
            {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

int findNextProcess(Process proc[], int n, int currentTime, bool isCompleted[])
{
    int minRemainingTime = __INT_MAX__;
    int minIndex = -1;
    int i;
    for (i = 0; i < n; i++)
    {
        if (!isCompleted[i] && proc[i].arrivalTime <= currentTime && proc[i].remainingTime < minRemainingTime)
        {
            minRemainingTime = proc[i].remainingTime;
            minIndex = i;
        }
    }
    return minIndex;
}

void calculateCompletionTime(Process proc[], int n, int ganttChart[], int *ganttSize)
{
    int time = 0;
    int completed = 0;
    bool isCompleted[n];
    int previousPid = -1;
    int i;

    for (i = 0; i < n; i++)
    {
        isCompleted[i] = false;
        proc[i].remainingTime = proc[i].burstTime;
    }

    while (completed != n)
    {
        int minIndex = findNextProcess(proc, n, time, isCompleted);

        if (minIndex != -1)
        {
            if (previousPid != proc[minIndex].pid)
            {
                ganttChart[*ganttSize] = proc[minIndex].pid;
                (*ganttSize)++;
                previousPid = proc[minIndex].pid;
            }

            proc[minIndex].remainingTime--;
            time++;

            if (proc[minIndex].remainingTime == 0)
            {
                proc[minIndex].completionTime = time;
                proc[minIndex].turnaroundTime = proc[minIndex].completionTime - proc[minIndex].arrivalTime;
                proc[minIndex].waitTime = proc[minIndex].turnaroundTime - proc[minIndex].burstTime;
                isCompleted[minIndex] = true;
                completed++;
            }
        }
        else
        {
            time++;
        }
    }
}

void printProcesses(Process proc[], int n)
{
    int i;
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].waitTime, proc[i].turnaroundTime);
    }
}

void calculateAndPrintAverages(Process proc[], int n)
{
    int i;
    float totalWaitTime = 0;
    float totalTurnaroundTime = 0;

    for (i = 0; i < n; i++)
    {
        totalWaitTime += proc[i].waitTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }

    printf("Average Wait Time: %.2f\n", totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

void printGanttChart(int ganttChart[], int ganttSize)
{
    int i;
    printf("Gantt Chart:\n|");
    for (i = 0; i < ganttSize; i++)
    {
        printf(" P%d |", ganttChart[i]);
    }
    printf("\n");
}

int main()
{
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    int ganttChart[100]; 
    int ganttSize = 0;

    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    sortProcessesByArrivalTime(proc, n);
    calculateCompletionTime(proc, n, ganttChart, &ganttSize);
    printProcesses(proc, n);
    calculateAndPrintAverages(proc, n);
    printGanttChart(ganttChart, ganttSize);

    return 0;
}

