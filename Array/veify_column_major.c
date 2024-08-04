#include<stdio.h>
#include<stdlib.h>

int main()
{
    int rows,cols;
    printf("Enter number of rows and columns: ");
    scanf("%d%d",&rows,&cols);
    //create a matrix dynamically
    int **matrix=(int**)malloc(rows*sizeof(int*));
    int i,j;
    //Enter elements to matrix
    printf("Enter elementsn to matrix\n");
    for(i=0;i<rows;i++)
    {
        matrix[i]=(int*)malloc(cols*sizeof(int));
        for(j=0;j<cols;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
    //initialise a 1D array
    int *array=(int*)malloc(rows*cols*sizeof(int));
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
           int index=j*rows+i;
           array[index]=matrix[i][j];
        }
    }

    //print 1D array
    printf("Print 1D array\n");
    for(i=0;i<rows*cols;i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");

    //treanspose matrix
    printf("Print transposed matrix\n");
    for(i=0;i<rows;i++)
    {
        for(j=i;j<cols;j++)
        {
           int temp=matrix[i][j];
           matrix[i][j]=matrix[j][i];
           matrix[j][i]=temp;
        }
        
    }

     printf("Print matrix\n");
      for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
           printf("%d ",matrix[i][j]);
        }
        
    }

}