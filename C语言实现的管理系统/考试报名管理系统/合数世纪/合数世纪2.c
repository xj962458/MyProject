#include<stdio.h>
#include<math.h>
int main()
{
   long a,b;
   int s,x,i;
   for(a=21;a<=20000;a++)
   {
      s=0;
      for(b=(a-1)*100+1;b<=a*100-1;b+=2) /*枚举a世纪奇数年号b*/
      {
         x=0;
         for(i=3;i<=sqrt(b);i+=2)
            if(b%i==0)
            {
               x=1;
               break;
            }
         if(x==0)  /*跳出循环进行下世纪的探求*/
            break;
         s=s+x;  /*年号b为合数时，x=1，s增1*/
      }
      if(s==50)   /*s=50，则此世纪是合数世纪*/
         break;
   }
   printf("第一个合数世纪为%ld世纪！\n",a);
}
