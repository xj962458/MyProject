#include<stdio.h>
#include<math.h>
int num[1000];  //存放不超过1993的全部素数
int fun(int i);//声明，判断是否为素数
void main()
{
    int i,j,count=0;
    printf("在第一行中以下素数满足要求:\n");
    for(j=0,i=3;i<=1993;i+=2)       //求出不超过1993的全部素数
        if(fun(i))
            num[j++]=i;
    for(j--;num[j]>1898;j--)        //从最大素数开始向1898搜索
    {
        for(i=0;num[j]-num[i]>1898;i++);
        if(num[j]-num[i]==1898)         //若两个素数的差为1898，则输出
            printf("(%d).%3d,......,%d\n",++count,num[i],num[j]);
    }
}
int fun(int i)//定义
{
    int j;
    if(i<=1) 
        return 0;
    if(i==2) 
        return 1;
    if(!(i%2)) 
        return 0;
    for(j=3;j<=(int)sqrt((double)i+1);j+=2)
        if(!(i%j)) 
            return 0;
    return 1;
}
