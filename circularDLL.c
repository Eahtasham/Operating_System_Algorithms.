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

// Function to insert an element at the end of the circular doubly linked list
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        (*head)->next = *head;
        (*head)->prev = *head;
    }
    else
    {
        struct Node *last = (*head)->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

// Function to display the circular doubly linked list
void displayList(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *current = head;
    do
    {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

int main()
{
    struct Node *head = NULL;
    int choice, data;

    while (1)
    {
        printf("\nCircular Doubly Linked List Menu:\n");
        printf("1. Insert an element at the end\n");
        printf("2. Display the list\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the element to insert: ");
            scanf("%d", &data);
            insertAtEnd(&head, data);
            printf("Element inserted successfully.\n");
            break;
        case 2:
            printf("The circular doubly linked list is: ");
            displayList(head);
            break;
        case 3:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }
    }

    return 0;
}
