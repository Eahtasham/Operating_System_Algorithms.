#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int name;
    struct Node* next;
} Node;

typedef struct {
    int name;
    Node* head;
} GraphNode;

GraphNode processes[MAX];
GraphNode resources[MAX];
int process_count = 0;
int resource_count = 0;

void add_process(int name) {
    processes[process_count].name = name;
    processes[process_count].head = NULL;
    process_count++;
}

void add_resource(int name) {
    resources[resource_count].name = name;
    resources[resource_count].head = NULL;
    resource_count++;
}

void add_request_edge(int process, int resource) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->name = resource;
    newNode->next = NULL;

    for (int i = 0; i < process_count; i++) {
        if (processes[i].name == process) {
            newNode->next = processes[i].head;
            processes[i].head = newNode;
            break;
        }
    }
}

void add_allocation_edge(int resource, int process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->name = process;
    newNode->next = NULL;

    for (int i = 0; i < resource_count; i++) {
        if (resources[i].name == resource) {
            newNode->next = resources[i].head;
            resources[i].head = newNode;
            break;
        }
    }
}

void display_graph() {
    printf("Processes:\n");
    for (int i = 0; i < process_count; i++) {
        printf("  %d\n", processes[i].name);
    }

    printf("\nResources:\n");
    for (int i = 0; i < resource_count; i++) {
        printf("  %d\n", resources[i].name);
    }

    printf("\nRequest Edges:\n");
    for (int i = 0; i < process_count; i++) {
        Node* temp = processes[i].head;
        while (temp) {
            printf("  %d -> %d\n", processes[i].name, temp->name);
            temp = temp->next;
        }
    }

    printf("\nAllocation Edges:\n");
    for (int i = 0; i < resource_count; i++) {
        Node* temp = resources[i].head;
        while (temp) {
            printf("  %d -> %d\n", resources[i].name, temp->name);
            temp = temp->next;
        }
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < process_count; i++) {
        printf("  %d: ", processes[i].name);
        Node* temp = processes[i].head;
        while (temp) {
            printf("%d ", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
    for (int i = 0; i < resource_count; i++) {
        printf("  %d: ", resources[i].name);
        Node* temp = resources[i].head;
        while (temp) {
            printf("%d ", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int p, r, e;
    printf("Enter the number of processes, resources, and edges: ");
    scanf("%d %d %d", &p, &r, &e);

    for (int i = 0; i < p; i++) {
        add_process(i);
    }

    for (int i = 0; i < r; i++) {
        add_resource(100 + i);
    }

    printf("Enter the edges (resource allocation and request) in the format u v:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 100) {
            add_allocation_edge(u, v);
        } else {
            add_request_edge(u, v);
        }
    }

    display_graph();

    return 0;
}
