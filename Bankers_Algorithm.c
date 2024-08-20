#include <stdio.h>
#include <stdbool.h>

#define N 5 // Number of processes
#define M 4 // Number of resource types

bool isSafeState(int n, int m, int Available[],
                 int Max[][M], int Allocation[][M])
{
    int Need[N][M];
    bool Finish[N];
    int Work[M];
    int i, j;
    bool foundProcess;
    bool canAllocate;

    // Initialize the Finish array and Work vector
    for (i = 0; i < n; ++i)
    {
        Finish[i] = false;
    }
    for (j = 0; j < m; ++j)
    {
        Work[j] = Available[j];
    }

    // Calculate the Need matrix
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Safety algorithm
    while (true)
    {
        foundProcess = false;
        for (i = 0; i < n; ++i)
        {
            if (!Finish[i])
            {
                // Check if Need[i] <= Work
                canAllocate = true;
                for (j = 0; j < m; ++j)
                {
                    if (Need[i][j] > Work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                // If a process can be allocated resources
                if (canAllocate)
                {
                    // Simulate the allocation
                    for (j = 0; j < m; ++j)
                    {
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = true;
                    foundProcess = true;
                }
            }
        }

        // If no process was found in this iteration, break the loop
        if (!foundProcess)
        {
            break;
        }
    }

    // Check if all processes have been finished
    for (i = 0; i < n; ++i)
    {
        if (!Finish[i])
        {
            return false; // Not in a safe state
        }
    }
    return true; // In a safe state
}

int main()
{
    int n = N; // Number of processes
    int m = M; // Number of resource types

    // Arbitrary Available array (number of available instances of each resource)
    int Available[M] = {3, 2, 1, 1};

    // Arbitrary Max matrix (maximum demand of each process)
    int Max[N][M] = {
        {6, 0, 1, 2},
        {2, 7, 5, 0},
        {2, 3, 5, 6},
        {1, 6, 5, 3},
        {1, 6, 5, 6}};

    // Arbitrary Allocation matrix (currently allocated resources to each process)
    int Allocation[N][M] = {
        {4, 0, 0, 1},
        {1, 1, 0, 0},
        {1, 2, 5, 4},
        {0, 6, 3, 3},
        {0, 2, 1, 2}};

    if (isSafeState(n, m, Available, Max, Allocation))
    {
        printf("The system is in a safe state.\n");
    }
    else
    {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}

