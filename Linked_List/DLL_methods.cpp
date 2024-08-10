#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
} Node;

Node *create(Node *head, Node *tail, int n)
{
    srand(time(NULL));

    if (n == 0)
    {
        head = NULL;
        return head;
    }

    for (int i = 0; i < n; i++)
    {
        Node *t = (Node *)malloc(sizeof(Node));
        t->prev = t->next = NULL;
        t->data = (int)rand() % 10;

        if (head == NULL)
        {
            head = tail = t;
        }
        else
        {
            t->next = tail->next; // store tail's next address to t
            tail->next = t;       // link tail to t
            t->prev = tail;       // link t to tail
            tail = t;             // point tail to t (new last node)
        }
    }
    return head;
}

void display(Node *head)
{
    Node *p = head;
    if (head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("List: ");
        while (p != NULL)
        {
            // printf("Node Address: %u, ", &p);
            // printf("Prev: %u, ", p->prev);
            // printf("Data: %d,  ", p->data);
            // printf("Next: %u  ->  \n", p->next);

            printf("%d -> ", p->data);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int count(Node *head)
{
    Node *p = head;
    int c = 0;

    if (head == NULL)
    {
        return c = 0;
    }
    else
    {
        while (p != NULL)
        {
            c++;
            p = p->next;
        }
    }
    return c;
}

Node *insert_begin(Node *head, int x)
{
    Node *t = (Node *)malloc(sizeof(Node));
    t->prev = NULL;
    t->data = x;
    t->next = head;
    head = t;

    return head;
}

Node *insert_n(Node *head, int x, int index)
{
    if (index <= 0 || index > count(head) + 1)
    {
        printf("Error: Index out of bounds\n");
        return head;
    }
    else
    {
        Node *t = (Node *)malloc(sizeof(Node));
        t->data = x;
        t->prev = t->next = NULL;

        if (index == 1)
        {
            // empty list
            if (head == NULL)
            {
                head = t;
            }
            else
            {
                t->next = head;
                head->prev = t;
                head = t;
            }
        }
        else
        {
            Node *p = head;
            for (int i = 1; i < index - 1; i++)
                p = p->next;
            // first do linking from t to the nodes
            t->next = p->next;
            t->prev = p;

            // if next node to p exists then
            if (p->next)
                p->next->prev = t; // Note you have to do this step first to not lose p->next
            p->next = t;
        }
    }
    return head;
}

Node *Delete(Node *head, int index)
{
    Node *p = head;

    if (index < 1 || index > count(head))
    {
        printf("Invalid Index Error\n");
        return head;
    }
    else
    {
        if (index == 1)
        {
            // Base case: empty list
            if (head == NULL)
            {
                printf("You cannot delete an empty list!!!!\n");
                return head;
            }
            else
            {
                // delete at first node
                p = head;
                head = head->next;
                printf("%d is deleted\n", p->data);
                if (head != NULL) // only if head in not NULL, then (we have already checked this condition, but still double check)
                    head->prev = NULL;
                free(p);
            }
        }
        else
        {
            // deletion at nth node
            for (int i = 0; i < index - 1; i++) // move p to nth node
                p = p->next;

            // link (n-1)th node to (n+1)th node
            p->prev->next = p->next;

            // if (n+1)th node exists, then link (n+1)th node to (n-1)th node
            if (p->next != NULL)
                p->next->prev = p->prev;

            printf("%d is deleted\n", p->data);
            free(p);
        }
    }
    return head;
}

Node *reverse(Node *head)
{
    Node *p = head;

    if (head == NULL)
    {
        printf("Error: You cannot reverse empty list");
        return head;
    }
    else
    {
        while (p != NULL)
        {
            Node *temp = p->next;
            p->next = p->prev;
            p->prev = temp;

            p = p->prev;
            if (p != NULL && p->next == NULL)
                head = p;
        }
    }
    return head;
}

int main(int argc, char **argv)
{
    int n, value, index, key;

    Node *head = NULL;
    Node *tail = NULL;

    printf("Enter no. of elem: ");
    scanf("%d", &n);
    head = create(head, tail, n);
    display(head);

    // insertion at n
    // printf("Enter value and index: ");
    // scanf("%d %d", &value, &index);
    // head = insert_n(head, value, index);
    // display(head);

    // deletion at n
    // printf("Enter index to delete: ");
    // scanf("%d", &index);
    // head = Delete(head, index);
    // display(head);

    head = reverse(head);
    printf("Reversed ");
    display(head);
    return 0;
}