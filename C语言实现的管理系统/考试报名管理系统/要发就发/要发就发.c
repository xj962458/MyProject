#include <stdio.h>
void main()
{
    int i,j,k,m,n=0;
    int a[1000];
    for(i=2;i<=1993;i++)
    {
        for(j=2;j<=i/2;j++)
        {
         if (i%j==0)
            break;
        }
        if (j==i/2+1)
        {
            a[n]=i;
            n++;
        }
    }
    for (m=0;a[m]<=95;m++)
    {
        for (k=n-1;a[k]>=1898;k--)
        {
            if(a[k]-a[m]==1898)
                printf("这两个素数可以为%d和%d\n",a[m],a[k]);
        }
    }
}
