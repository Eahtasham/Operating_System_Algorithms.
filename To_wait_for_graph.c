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

void display_graph(GraphNode graph[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d: ", graph[i].name);
        Node* temp = graph[i].head;
        while (temp) {
            printf("%d ", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

void convert_to_wait_for_graph(GraphNode wait_for_graph[]) {
    for (int i = 0; i < process_count; i++) {
        wait_for_graph[i].name = processes[i].name;
        wait_for_graph[i].head = NULL;
    }

    for (int i = 0; i < resource_count; i++) {
        Node* temp = resources[i].head;
        while (temp) {
            int process = temp->name;
            Node* request = resources[i].head;
            while (request) {
                if (request->name != process) {
                    Node* newNode = (Node*)malloc(sizeof(Node));
                    newNode->name = request->name;
                    newNode->next = NULL;

                    for (int j = 0; j < process_count; j++) {
                        if (wait_for_graph[j].name == process) {
                            newNode->next = wait_for_graph[j].head;
                            wait_for_graph[j].head = newNode;
                            break;
                        }
                    }
                }
                request = request->next;
            }
            temp = temp->next;
        }
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

    printf("\nResource Allocation Graph (RAG):\n");
    printf("Processes:\n");
    display_graph(processes, process_count);
    printf("Resources:\n");
    display_graph(resources, resource_count);

    GraphNode wait_for_graph[MAX];
    convert_to_wait_for_graph(wait_for_graph);

    printf("\nWait-For Graph (WFG):\n");
    display_graph(wait_for_graph, process_count);

    return 0;
}
