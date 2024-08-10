#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int i;
    int j;
    int x;
} Element;

typedef struct Sparse
{
    int m;
    int n;
    int nnz;
    Element *ele;
} Sparse;

int **create_mat(int r, int c)
{
    int i;
    int **a = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
    {
        a[i] = (int *)malloc(c * sizeof(int));
    }
    return a;
}

void insert_mat(int **arr, int r, int c)
{
    int i, j;
    printf("Enter all the values of matrix: \n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void print_mat(int **arr, int r, int c)
{
    int i, j;
    printf("Input Matrix: \n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int NNZ(int **arr, int r, int c)
{
    int size = 0, i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            if (arr[i][j] != 0)
                size++;

    return size;
}

void insert_sparse(int **mat, Sparse *s, int r, int c)
{
    int i, j, k = 0;

    // Insert the dimensions and NNZ of struct Sparse
    s->m = r;
    s->n = c;
    s->nnz = NNZ(mat, r, c);

    s->ele = (Element *)malloc(s->nnz * sizeof(Element));

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (mat[i][j] != 0)
            {
                s->ele[k].i = i;
                s->ele[k].j = j;
                s->ele[k].x = mat[i][j];
                k++;
            }
        }
    }
}

void display_sparse(Sparse s)
{
    int i, j, k = 0;
    printf("Sparse Representation: \n");
    printf("%d %d %d\n", s.m, s.n, s.nnz);
    for (i = 0; i < s.m; i++)
    {
        int c = 0;
        for (j = 0; j < s.n; j++)
        {
            if (i == s.ele[k].i && j == s.ele[k].j)
            {
                if (c > 0) // to make sure a newline is printed for elems in same row
                    printf("\n");
                printf("%d %d %d", s.ele[k].i, s.ele[k].j, s.ele[k].x);
                k++;
                c++;
            }
        }
        printf("\n");
    }
}

void display_in_matrix(Sparse s)
{
    int i, j, k = 0;
    for (i = 0; i < s.m; i++)
    {
        for (j = 0; j < s.n; j++)
        {
            if (i == s.ele[k].i && j == s.ele[k].j)
            {
                printf("%d ", s.ele[k++].x);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void transpose(Sparse *A, Sparse *T)
{
    int i, j, k;
    T->m = A->n;
    T->n = A->m;
    T->nnz = A->nnz;

    T->ele = (Element *)malloc(T->nnz * sizeof(Element));

    // Count occurences of column in
    int *num_col = (int *)calloc(T->m, sizeof(int));

    // Count the no. of elements in each column of A
    for (i = 0; i < A->nnz; i++)
    {
        num_col[A->ele[i].j]++;
    }

    int *index = (int *)calloc(T->m, sizeof(int));

    // Calculate the stating index of each j in T
    index[0] = 0;
    for (i = 1; i < T->m; i++)
    {
        index[i] = index[i - 1] + num_col[i - 1];
    }

    for (i = 0; i < A->nnz; i++)
    {
        j = A->ele[i].j;
        k = index[j];
        T->ele[k].i = A->ele[i].j;
        T->ele[k].j = A->ele[i].i;
        T->ele[k].x = A->ele[i].x;
        index[j]++;
    }
    free(num_col);
    free(index);
}

Sparse *add(Sparse *s1, Sparse *s2)
{

    if (s1->m != s2->m || s1->n != s2->n)
        return 0;
    Sparse *sum = (Sparse *)malloc(sizeof(Sparse));
    sum->m = s1->m;
    sum->n = s1->n;
    sum->ele = (Element *)calloc((s1->nnz + s2->nnz), sizeof(Element));

    int i = 0, j = 0, k = 0;
    while (i < s1->nnz && j < s2->nnz)
    {
        if (s1->ele[i].i < s2->ele[j].i)
            sum->ele[k++] = s1->ele[i++];
        else if (s1->ele[i].i > s2->ele[j].i)
            sum->ele[k++] = s2->ele[j++];
        else
        {
            if (s1->ele[i].j < s2->ele[j].j)
                sum->ele[k++] = s1->ele[i++];
            else if (s1->ele[i].j > s2->ele[j].j)
                sum->ele[k++] = s2->ele[j++];
            else
            {
                sum->ele[k] = s1->ele[i++];
                sum->ele[k++].x += s2->ele[j++].x;
            }
        }
    }
    for (; i < s1->nnz; i++)
        sum->ele[k++] = s1->ele[i];
    for (; j < s2->nnz; j++)
        sum->ele[k++] = s2->ele[j];
    sum->nnz = k;
    return sum;
}

int main()
{
    int m, n;
    struct Sparse s, t, *sum;

    // Matrix
    printf("Enter dimensions of Matrix: ");
    scanf("%d %d", &m, &n);
    int **mat = create_mat(m, n);
    insert_mat(mat, m, n);
    // print_mat(mat, m, n);

    insert_sparse(mat, &s, m, n);
    display_sparse(s);

    transpose(&s, &t);
    printf("Transposed Sparse Representation: \n");
    display_sparse(t);
    printf("In Matrix Form: \n");
    display_in_matrix(t);

    sum = add(&s, &t);
    printf("Added Matrix: \n");
    display_sparse(*sum);
    printf("In Matrix Form: \n");
    display_in_matrix(*sum);

    return 0;
}