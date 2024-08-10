#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    Node *next;
} Node;

void display(Node *head)
{
    Node *p = head;
    // we have used do while as first time only p points to head
    // so first print it, then check

    if (head == NULL)
    {
        printf("EMPTY LIST");
    }
    else
    {
        printf("List : ");
        do
        {
            printf("%d ", p->data);
            p = p->next;
        } while (p != head);
        printf("\n");
    }
}
void display_recurse(Node *head)
{
    static int flag = 0; // to see if p is traversing for first time
                         // static to keep only 1 record of flag
    Node *p = head;
    if (p != head || flag == 0)
    {
        flag = 1;
        printf("%d", p->data);
        display_recurse(p->next);
    }
}

int count(Node *head)
{
    Node *p = head;
    int c = 0;
    if (head == NULL)
    {
        c = 0;
        return c;
    }
    else
    {
        do
        {
            c++;
            p = p->next;
        } while (p != head);
    }
    return c;
}

Node *create(Node *head, Node *last)
{
    int n, i;
    srand(time(NULL));
    printf("Enter how many elements to enter: ");
    scanf("%d", &n);

    if (n == 0)
    {
        head = NULL;
        return head;
    }
    for (i = 0; i < n; i++)
    {
        Node *t = (Node *)malloc(sizeof(Node));
        // scanf("%d", &t->data);
        t->data = (int)rand() % 10;

        if (head == NULL)
        {
            head = last = t;
            t->next = head;
        }
        else
        {
            t->next = last->next;
            last->next = t;
            last = t;
        }
    }
    return head;
}

Node *insert_begin(Node *head, int x)
{
    Node *p = head;
    Node *t = (Node *)malloc(sizeof(Node));
    t->data = x;
    t->next = NULL;

    // base condn: empty list
    if (head == NULL)
    {
        head = t;
        t->next = head; // point to itself
    }
    else
    {
        t->next = head;         // first node exists
        while (p->next != head) // traverse to last node
            p = p->next;
        p->next = t;
        head = t; //  <------ this line
    }
    return head;
}

// insert last is basically insert first, but head does not change
Node *insert_last(Node *head, int x)
{
    Node *p = head;
    Node *t = (Node *)malloc(sizeof(Node));
    t->data = x;
    t->next = NULL;

    if (head == NULL)
    {
        head = t;
        t->next = head;
    }
    else
    {
        t->next = head;
        while (p->next != head)
            p = p->next;
        p->next = t;
    }
    return head;
}

Node *insert(Node *head, int x, int index)
{
    Node *p = head;
    Node *t = (Node *)malloc(sizeof(Node));
    t->data = x;
    t->next = NULL;

    if (index <= 0 || index > count(head) + 1) // count+1 to add node at end
    {
        printf("Index Error: Index Out of Bounds");
        return head; // no need to change head, return whatever it is
    }
    else
    {
        if (index == 1)
        {
            // base case: empty list
            if (head == NULL)
            {
                head = t;
                t->next = head;
            }
            else
            {
                // insertion at beginning
                t->next = head;
                // traverse till p reaches last node
                while (p->next != head)
                    p = p->next;

                // link last node to new node and head to the node
                p->next = t;
                head = t;
            }
        }
        else
        {
            p = head;
            // insert at index
            for (int i = 1; i < index - 1; i++)
            {
                p = p->next;
            }
            t->next = p->next;
            p->next = t;
        }
    }
    return head;
}

Node *delete_n(Node *head, int index)
{
    int x;
    Node *p = head;

    if (count(head) == 0)
    {
        printf("You cannot delete in empty list");
        return head; // head is NULL here
    }
    if (index <= 0 || index > count(head))
    {
        printf("Invalid Index Error: Index out of Bounds\n");
        return head;
    }
    else
    {
        if (index == 1)
        {
            while (p->next != head)
                p = p->next;
            x = head->data;

            if (p == head)
            {
                // delete the one and only node of linked list
                free(head);
                head = NULL;
            }
            else
            {
                // no. of nodes > 1
                p->next = head->next;
                free(head);
                head = p->next;

                printf("%d is deleted\n", x);
            }
        }
        else
        {
            Node *q;
            p = head;
            for (int i = 1; i < index - 1; i++)
                p = p->next;
            q = p->next; // q is the nth index node to be deleted
            x = q->data;
            p->next = q->next;
            free(q);

            printf("%d is deleted\n", x);
        }
    }
    return head;
}

int main()
{
    int index, value;
    Node *head = NULL;
    Node *last = NULL;

    head = create(head, last);
    display(head);

    int flag = 1;

    while (flag)
    {

        printf("Menu: ");
        printf("\tEnter 1 to insert a new node\n");
        printf("\tEnter 2 to insert a node beginning \n");
        printf("\tEnter 3 to insert a node at end\n");
        printf("\tEnter 4 to delete a node\n");
        printf("\tEnter 5 to count no of nodes\n");
        printf("\tEnter 0 to quit\n");

        int choice = 0;
        printf("Enter operation: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            flag = 0; // to terminate the loop
            break;
        case 1:
            printf("Enter value and index for insertion: ");
            scanf("%d %d", &value, &index);
            head = insert(head, value, index);
            break;
        case 2:
            printf("Enter value for insertion: ");
            scanf("%d", &value);
            head = insert_begin(head, value);
            break;
        case 3:
            printf("Enter value for insertion: ");
            scanf("%d", &value);
            head = insert_last(head, value);

            break;
        case 4:
            printf("Enter index of node to be deleted : ");
            scanf("%d", &index);
            head = delete_n(head, index);

            break;
        case 5:
            printf("No. of nodes: %d\n", count(head));
            break;
        default:
            printf("INVALID OPTION");
        }
        display(head);
    }
    return 0;
}