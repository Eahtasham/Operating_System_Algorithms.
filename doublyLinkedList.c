#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert n elements in the linked list
void insertNElements(struct Node **head, int n)
{
    struct Node *temp = *head;
    int data;
    for (int i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        struct Node *newNode = createNode(data);
        if (*head == NULL)
        {
            *head = newNode;
            temp = *head;
        }
        else
        {
            temp->next = newNode;
            newNode->prev = temp;
            temp = temp->next;
        }
    }
}

// Function to delete the first element from the list
void deleteFirst(struct Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct Node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free(temp);
    printf("First element deleted successfully.\n");
}

// Function to print the frequency of each element in the list
void printFrequency(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *current = head;
    while (current != NULL)
    {
        int count = 1;
        struct Node *temp = current->next;
        while (temp != NULL)
        {
            if (temp->data == current->data)
            {
                count++;
            }
            temp = temp->next;
        }
        printf("Frequency of %d: %d\n", current->data, count);
        current = current->next;
        while (current != NULL && current->data == current->prev->data)
        {
            current = current->next;
        }
    }
}

// Function to insert a new element at the third position in the list
void insertAtThird(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else if ((*head)->next == NULL)
    {
        (*head)->next = newNode;
        newNode->prev = *head;
    }
    else
    {
        struct Node *current = *head;
        for (int i = 0; i < 2; i++)
        {
            current = current->next;
            if (current == NULL)
            {
                printf("List does not have enough elements to insert at third position.\n");
                return;
            }
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL)
        {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }
    printf("Element inserted at third position successfully.\n");
}
void printLinkedList(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to display the menu
void displayMenu()
{
    printf("\nDoubly Linked List Menu:\n");
    printf("1. Insert n elements\n");
    printf("2. Delete first element\n");
    printf("3. Print frequency of each element\n");
    printf("4. Insert element at third position\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    struct Node *head = NULL;
    int choice, n, data;

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter number of elements to insert: ");
            scanf("%d", &n);
            insertNElements(&head, n);
            printLinkedList(head);
            break;
        case 2:
            deleteFirst(&head);
            printLinkedList(head);
            break;
        case 3:
            printFrequency(head);
            break;
        case 4:
            printf("Enter element to insert at third position: ");
            scanf("%d", &data);
            insertAtThird(&head, data);
            printLinkedList(head);
            break;
        case 5:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
