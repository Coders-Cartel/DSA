#include<stdio.h>
typedef struct poly
{
	float coeff;
	int exp;
}poly;

poly term[100];

int main()
{
	int i=0,j=0,k,m,numOfPoly,numOfTerms;
	printf("How many polynomials you want to add? ");
    scanf("%d",&numOfPoly);
    printf("\n");
    while(numOfPoly)
    {
        printf("How many terms? ");
        scanf("%d",&numOfTerms);
        printf("\nEnter the coeffi and exps\n");
        k=0;
        while(numOfTerms)
        {
            scanf("%f %d",&term[i].coeff,&term[i].exp);
            i++;
            k++;
            numOfTerms--;
        }
        j++;
        k--;
        printf("%d-th term is: ",j);
        for(m=i-1;m>=i-k-1;m--)
        {
            if(term[m].exp!=0)
            {
                printf("%.2fx^%d",term[m].coeff,term[m].exp);
                if(m>i-k-1) printf(" + ");
            }
            else{
                printf("%.2f",term[m].coeff);
                if(m>i-k-1) printf(" + ");
            }

        }
        printf("\n");
        numOfPoly--;
    }
    i--;
    for(j=0;j<i;j++)
    {
        for(k=j+1;k<=i;k++)
        {
           
            if(term[j].exp==term[k].exp)
            {
                term[j].coeff+=term[k].coeff;
                term[k].coeff=0;
            }
        }
    }
    printf("\nThe added polynomial is: ");
    int printedTerms=0;
    for(j=0;j<=i;j++)
    {
       // if(term[j].coeff>0)
       if(term[j].coeff!=0)
       {
            if(printedTerms>0) printf("+");
            printf(" %.2fdx^%d  ",term[j].coeff,term[j].exp);
            printedTerms++;
       }
       
    }
    if(printedTerms==0) printf("0");
    
    return 0;
}
    

	
