#include <stdio.h>

int main()
{
    int i,j,k,n;
    printf("enter the height : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        for(k=0;k<n-i-1;k++)
        {
            printf(" ");
        }
        for(j=0;j<(2*i)+1;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    for(i=0;i<n;i++)
    {
        for(k=0;k<i;k++)
        {
            printf(" ");
        }
        for(j=0;j<(2*n)-1-(2*i);j++)
        {
            printf("*");
        }
        printf("\n");
    }
    for(i=0;i<n;i++)
    {
        if((i==0) || (i==(n-1)))
        {
            for(k=0;k<n;k++)
            {
                printf("* ");
            }
        }
        else
        {
            printf("*");
            for(j=0;j<(2*(n-2))+1;j++)
            {
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
    return 0;
}