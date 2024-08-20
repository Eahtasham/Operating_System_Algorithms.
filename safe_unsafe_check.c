#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int p, int r) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

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
            return false;
        }
    }

    return true;
}

bool request_resources(int processes[], int avail[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int p, int r, int request[], int process_index) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need, max, allocation, p, r);

    // Step 1: Check if request <= need
    for (int i = 0; i < r; i++) {
        if (request[i] > need[process_index][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Step 2: Check if request <= available
    for (int i = 0; i < r; i++) {
        if (request[i] > avail[i]) {
            printf("Process %d must wait; resources are not available.\n", process_index);
            return false;
        }
    }

    // Step 3: Pretend the request is granted
    int temp_avail[MAX_RESOURCES];
    int temp_allocation[MAX_PROCESSES][MAX_RESOURCES];
    int temp_need[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < r; i++) {
        temp_avail[i] = avail[i] - request[i];
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            temp_allocation[i][j] = allocation[i][j];
            temp_need[i][j] = need[i][j];
        }
    }

    for (int j = 0; j < r; j++) {
        temp_allocation[process_index][j] += request[j];
        temp_need[process_index][j] -= request[j];
    }

    // Check if the system is in a safe state with the modified state
    return is_safe(processes, temp_avail, max, temp_allocation, p, r);
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

    // Request 1
    int request1[MAX_RESOURCES];
    printf("Enter the request vector for REQ1 (P0):\n");
    for (int i = 0; i < r; i++) {
        scanf("%d", &request1[i]);
    }

    if (request_resources(processes, avail, max, allocation, p, r, request1, 0)) {
        printf("REQ1 can be granted. The system remains in a safe state.\n");
    } else {
        printf("REQ1 cannot be granted. The system is not in a safe state.\n");
    }

    // Request 2
    int request2[MAX_RESOURCES];
    printf("Enter the request vector for REQ2 (P1):\n");
    for (int i = 0; i < r; i++) {
        scanf("%d", &request2[i]);
    }

    if (request_resources(processes, avail, max, allocation, p, r, request2, 1)) {
        printf("REQ2 can be granted. The system remains in a safe state.\n");
    } else {
        printf("REQ2 cannot be granted. The system is not in a safe state.\n");
    }

    return 0;
}
