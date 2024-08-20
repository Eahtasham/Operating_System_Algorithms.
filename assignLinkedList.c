#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *createNode(int data)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct node *insertNode(struct node *head, int data)
{
    if (head == NULL)
    {
        return createNode(data);
    }
    else
    {
        struct node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = createNode(data);
    }
    return head;
}
void printLL(struct node *head)
{
    printf(" The elements in the LL is ");
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
struct node *insertFunction(struct node *head)
{
    int n;
    printf("Enter the number of element to add ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\n Enter the %d Number ", i + 1);
        int num;
        scanf("%d", &num);
        head = insertNode(head, num);
    }
    return head;
}
void secondLast(struct node *head)
{
    struct node *p = head;
    struct node *q = NULL;
    struct node *r = NULL;
    while (p->next != NULL)
    {
        r = q;
        q = p;
        p = p->next;
    }
    r->next = p;
    free(q);
}
struct node *reverseLL(struct node *head)
{
    struct node *p = head;
    struct node *q = NULL;
    struct node *r = NULL;
    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    head = q;
    return head;
}
void midElement(struct node *head)
{
    int arr[100];
    struct node *temp = head;
    int i = 0;
    while (temp != 0)
    {
        arr[i++] = temp->data;
        temp = temp->next;
    }
    printf("The mid elemtnt is %d \n", arr[i / 2]);
}
int main()
{
    struct node *head = NULL;
    // head=insertFunction(head);
    // printLL(head);
    // secondLast(head);
    // head=reverseLL(head);
    // printLL(head);
    // midElement(head);

    while (1)
    {
        int ch;
        printf("1.Insert Elements \n");
        printf("2.Remove Second Last Element \n");
        printf("3.Reverse the Linked List \n");
        printf("4.Mid Element of Linked List \n");
        printf("0.Exit \n");
        printf("Enter the choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            head = insertFunction(head);
            printLL(head);
            break;
        case 2:
            secondLast(head);
            printLL(head);
            break;
        case 3:
            head = reverseLL(head);
            printLL(head);
            break;
        case 4:
            midElement(head);
            break;
        default:
            exit(0);
        }
    }

    return 0;
}