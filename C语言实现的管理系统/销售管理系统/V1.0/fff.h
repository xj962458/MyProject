#include<x.h>
int fff(int a[],int n,int p,int fz)
{   
    int i,j,s;
    a[p+1]=n;
    a[p+2]=0;
    for(i=1,j=1;a[i];i++)
    {
        if(a[i]<=a[i-1])j=0;           //消除相同分母，即取消2/3=1/3+1/3
        j*=a[i];                       //获得公分母
    }
    for(i=1,s=0;a[i];i++)s+=j/a[i];
    if(s==fz)return 1;                 //找到埃及分数直接返回显示（公分子和等于fz）
    if(a[p]*a[p]>n)
		return 0;
    for(i=p>0?a[p]:2;i*i<=n;i++)
    {
        if(!(n%i))
        {
            a[++p]=i;                  //存储因数
            j=fff(a,n/i,p,fz);         //递归调用
            if (j)return 1;            //已经找到埃及分数，不再分解因式
            p--;
        }
    }
    return 0;
}

