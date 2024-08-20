#include <stdio.h>
#include <stdbool.h>

#define N 3 // Number of processes
#define M 3 // Number of resource types (X, Y, Z)

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

bool requestResources(int n, int m, int Available[], int Max[][M],
                      int Allocation[][M], int Request[], int processId)
{
    int Need[N][M];
    int i, j;

    // Calculate the Need matrix
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Step 1: Check if Request <= Need
    for (j = 0; j < m; ++j)
    {
        if (Request[j] > Need[processId][j])
        {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Step 2: Check if Request <= Available
    for (j = 0; j < m; ++j)
    {
        if (Request[j] > Available[j])
        {
            printf("Process %d must wait: Resources are not available.\n", processId);
            return false;
        }
    }

    // Step 3: Pretend to allocate requested resources
    for (j = 0; j < m; ++j)
    {
        Available[j] -= Request[j];
        Allocation[processId][j] += Request[j];
        Need[processId][j] -= Request[j];
    }

    // Check if the system is in a safe state
    if (isSafeState(n, m, Available, Max, Allocation))
    {
        printf("The system remains in a safe state after the request by process %d.\n", processId);
        return true;
    }
    else
    {
        // Rollback allocation
        for (j = 0; j < m; ++j)
        {
            Available[j] += Request[j];
            Allocation[processId][j] -= Request[j];
            Need[processId][j] += Request[j];
        }
        printf("The system would be unsafe after the request by process %d. Request denied.\n", processId);
        return false;
    }
}

int main()
{
    int n = N; // Number of processes
    int m = M; // Number of resource types (X, Y, Z)

    // Arbitrary Available vector (number of available instances of each resource)
    int Available[M] = {3, 3, 2};

    // Arbitrary Max matrix (maximum demand of each process)
    int Max[N][M] = {
        {8, 4, 3}, // P0
        {6, 2, 0}, // P1
        {3, 3, 3}  // P2
    };

    // Arbitrary Allocation matrix (currently allocated resources to each process)
    int Allocation[N][M] = {
        {0, 0, 1}, // P0
        {3, 2, 0}, // P1
        {2, 1, 1}  // P2
    };

    // Requests
    int REQ1[M] = {0, 0, 2}; // P0 requests 0 units of X, 0 units of Y, and 2 units of Z
    int REQ2[M] = {2, 0, 0}; // P1 requests 2 units of X, 0 units of Y, and 0 units of Z

    // Check for REQ1
    printf("Checking REQ1 (P0 requests 0 units of X, 0 units of Y, and 2 units of Z):\n");
    requestResources(n, m, Available, Max, Allocation, REQ1, 0);

    // Check for REQ2
    printf("\nChecking REQ2 (P1 requests 2 units of X, 0 units of Y, and 0 units of Z):\n");
    requestResources(n, m, Available, Max, Allocation, REQ2, 1);

    return 0;
}

