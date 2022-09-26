#include<stdio.h>
#include<math.h>
int main()
{
   long a,b,k;
   int m,n,s,x;
   printf("探究第n个合数世纪，请输入n:");
   scanf("%d",&n);
   a=1;
   m=0;
   while(1)
   {
      a++;    /*检验a世纪*/
      s=0;
      for(b=a*100-99;b<=a*100-1;b+=2) /*枚举a世纪奇数年号b*/
      {
         x=0;
         for(k=3;k<=sqrt(b);k+=2)
            if(b%k==0)
            {
               x=1;
               break;
            }
         if(x==0)  /*跳出循环进行下世纪的探求*/
            break;
         s=s+x;  /*年号b为合数时，x=1，s增1*/
      }
      if(s==50)   /*s=50，合数世纪数m增1*/
         m++;
      if(m==n)
         break;
   }
   printf("第%d个合数世纪为%ld世纪！\n",n,a);
   printf("该世纪的年号%ld--%ld全为合数！\n",a*100-99,a*100);
}
