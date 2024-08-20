#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

// Function to calculate the need matrix
void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int p, int r) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool is_safe(int processes[], int avail[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int p, int r) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need, max, allocation, p, r);

    bool finished[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    for (int i = 0; i < r; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < p) {
        bool found = false;
        for (int i = 0; i < p; i++) {
            if (!finished[i]) {
                int j;
                for (j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == r) {
                    for (int k = 0; k < r; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = processes[i];
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int p, r;
    printf("Enter the number of processes: ");
    scanf("%d", &p);
    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int processes[MAX_PROCESSES];
    for (int i = 0; i < p; i++) {
        processes[i] = i;
    }

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < r; i++) {
        scanf("%d", &avail[i]);
    }

    is_safe(processes, avail, max, allocation, p, r);

    return 0;
}
