#include<x.h>
int bbb(void)
{
    int a[10] = {10, 2, 8, 22, 16, 4, 10, 6, 14, 20};
    int i, j, n, left, self, candy;
	n = 0;
    while(1)
    {
        n++;
        for(left = a[0]/2, i=0;i<10;left = self, i++)
        {
            candy = a[(i+1)%10];
            self = candy/2;
            candy = self + left;    //换过后，糖果数位原来数的一半加左边人的一半
            if(candy % 2 == 1)      //如果是奇数，再要一块
                candy++;
            a[(i+1)%10] = candy;
        }
 
        for(i=0;i<10;i++)           //输出一轮以后所有人的糖果数
			printf("%d块 ", a[i]);
        printf("\n");
 
        for(j=1;j<10;j++)
        {
            if(a[j] != a[0])
                break;
        }
 
        if(j==10)
            break;
    }
 
    printf("经过%d次，大家的糖都是%d块\n", n, a[0]);
 
    return 0;
}
