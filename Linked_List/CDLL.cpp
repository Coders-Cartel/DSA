#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef struct Node
{
    Node *prev;
    int data;
    Node *next;
} Node;

void display(Node *head)
{
    Node *p = head;
    printf("\nList: ");
    if (head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        do
        {
            printf("%d -> ", p->data);
            p = p->next;
        } while (p != head);
        printf("\n");
    }
}

// Note: to modify the list, use Node **head i.e address of the head itself,
//  deref will give the address of first node
// using the address of first node, we can access the member vars to first node

void create(Node **head, Node **tail, int n)
{
    srand(time(NULL));

    if (n == 0)
    {
        *head = NULL;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        Node *t = (Node *)malloc(sizeof(Node));
        t->data = (int)rand() % 10;

        // base case :  empty list
        if (*head == NULL)
        {
            *head = *tail = t;
            t->next = *head;
        }
        else
        {
            // link t to head and vice versa
            t->next = *head;
            (*head)->prev = t;

            // link tail to t and vice versa
            (*tail)->next = t;
            t->prev = *tail;

            // point tail to new last node
            *tail = t;
        }
    }
}

void insert_begin(Node **head, int x)
{
    Node *t = (Node *)malloc(sizeof(Node));
    t->data = x;
    t->prev = t->next = NULL;

    if (head == NULL)
    {
        *head = t;
        t->next = *head;
        t->prev = *head;
    }
    else
    {
        t->next = *head;
        t->prev = (*head)->prev; // point to last node

        (*head)->prev->next = t;
        (*head)->prev = t;

        // point head to new node
        *head = t;
    }
}

void insert_end(Node **head, int x)
{
    Node *t = (Node *)malloc(sizeof(Node));
    t->data = x;
    t->prev = t->next = NULL;

    if (head == NULL)
    {
        *head = t;
        t->next = *head;
        t->prev = *head;
    }
    else
    {
        t->next = *head;
        t->prev = (*head)->prev; // point to last node

        (*head)->prev->next = t;
        (*head)->prev = t;
    }
}

void Delete(Node **head, Node *p)
{
    if (*head == NULL) // empty list
    {
        printf("You cannot delete empty list");
        return;
    }
    else
    {
        if (p->next == p) // 1 node in list
        {
            *head = NULL;
            printf("%d is deleted\n", p->data);
            free(p);
            return;
        }

        // deleting the second node
        if (p->next == *head)
        {
            p->next->next->prev = p;
            Node *q = *head;
            *head = (*head)->next;
            p->next = *head;

            printf("%d is deleted", q->data);
            free(q);
            return;
        }
        else
        {
            Node *q = p->next;
            q->next->prev = p;
            p->next = q->next;
            printf("%d is deleted", q->data);
            free(q);
            return;
        }
    }
}

int main(int argc, char **argv)
{
    int n, value;
    Node *head = NULL;
    Node *tail = NULL;

    printf("Enter no of nodes: ");
    scanf("%d", &n);
    create(&head, &tail, n);
    display(head);

    // insert at beginning
    // printf("Enter value to insert at begining: ");
    // scanf("%d", &value);
    // insert_begin(&head, value);
    // display(head);

    // insert at end
    // printf("Enter value to insert at begining: ");
    // scanf("%d", &value);
    // insert_end(&head, value);
    // display(head);

    // delete at p node
    Node *temp = (head)->next->next;
    Delete(&head, temp);
    display(head);

    return 0;
}