#include<stdio.h>
void main()
{
    int i,a,b;  //a为世纪区间变量，b为a世纪的50个奇数年号
    for(a=21;a<20000;a++)
    {
        for(b=(a-1)*100+1;b<a*100;b+=2)
        {
            for(i=3;i*i<b;i+=2)
            {
                if(b%i==0)
                    break;
            }
            if(i*i>=b)
                break;
        }
        if(b>=a*100)
        {
            printf("第一个合数世纪是%d世纪",a);
        }
    }
}
