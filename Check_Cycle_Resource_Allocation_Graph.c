#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20

// Function to perform Depth First Search
int dfs(int adjList[MAX_NODES][MAX_NODES], int u, int visited[MAX_NODES], int n)
{
	int v;
    visited[u] = 0; // visiting
    for (v = 0; v < n; v++)
    {
        if (adjList[u][v])
        {
            if (visited[v] == -1 && dfs(adjList, v, visited, n))
            {
                return 1;
            }
            else if (visited[v] == 0)
            {
                return 1;
            }
        }
    }
    visited[u] = 1; // visited all adjacent nodes
    return 0;
}

// Function to check if the graph has a cycle
int isCyclic(int adjList[MAX_NODES][MAX_NODES], int n)
{
	int i,u;
    int visited[MAX_NODES];
    for (i = 0; i < n; i++)
    {
        visited[i] = -1;
    }

    for (u = 0; u < n; u++)
    {
        if (visited[u] == -1 && dfs(adjList, u, visited, n))
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if adding an edge creates a cycle
int willCreateCycle(int adjList[MAX_NODES][MAX_NODES], int from, int to, int n)
{
    adjList[from][to] = 1;            // Temporarily add the claim edge
    int hasCycle = isCyclic(adjList, n); // Check for a cycle
    adjList[from][to] = 0;            // Revert the graph back to its original state
    return hasCycle;
}

int main()
{
    int numProcesses, numResources, numEdges;
    int p0 = 0;   // first process id
    int r0 = 100; // first resource id
    int i, from, to;

    printf("INPUT:\n");
    printf("Enter no. of processes, no. of resources, no. of edges separated by space: ");
    scanf("%d %d %d", &numProcesses, &numResources, &numEdges);

    int N = (p0 + numProcesses > r0 + numResources) ? p0 + numProcesses : r0 + numResources;
    N++;

    int adjList[MAX_NODES][MAX_NODES] = {0};

    printf("Enter the edge list of the graph:\n");
    for (i = 0; i < numEdges; ++i)
    {
        scanf("%d %d", &from, &to);
        adjList[from][to] = 1;
    }

    // Check for cycles (deadlock detection)
    printf("\nOUTPUT:\n");
    if (isCyclic(adjList, N))
    {
        printf("Deadlocked\n");
    }
    else
    {
        printf("Not deadlocked\n");

        // Check if adding a claim edge will create a cycle
        printf("Enter the claim edge (from to): ");
        scanf("%d %d", &from, &to);

        if (willCreateCycle(adjList, from, to, N))
        {
            printf("Adding this claim edge will create a deadlock\n");
        }
        else
        {
            printf("Adding this claim edge will NOT create a deadlock\n");
        }
    }

    return 0;
}

