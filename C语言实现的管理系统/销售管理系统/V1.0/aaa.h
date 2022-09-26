#include<x.h>
void aaa()
{
    int a[100],fz,fm,i,j;
	printf("请输入一个真分数的分子和分母\n");
    scanf("%d%d",&fz,&fm);
    for(i=2;i<=10000;i++)
    {
        a[0]=1;
        if(fff(a,fm*i,0,fz*i))
        {
            printf("%d/%d=",fz,fm);
            for(j=1;a[j];j++)
            {
                printf("1/%d",a[j]);
                if(a[j+1])
					printf("+");
            }
            printf("\n");
            break;
        }
    }
}
