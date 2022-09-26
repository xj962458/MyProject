#include<x.h>
//比较，得最值及和
void Sort(LinkList head, int n)
{
	float sum;
	sum=0;
	int i;
    LinkList p=head->link;
    LinkList max=head->link;
    LinkList min=head->link;
    for(i=0;i<n;i++)
	{
    	sum+=(p->sales);
        if((max->sales)<=(p->sales)) max=p;
		if((min->sales)>=(p->sales)) min=p; 
        p=p->link;
    }
    printf("销售额最高者:\n编号:%s  姓名:%s  销售额:%f\n",max->no,max->name,max->sales);
    printf("销售额最低者:\n编号:%s  姓名:%s  销售额:%f\n",min->no,min->name,min->sales);
    printf("总销售额:%f\n",sum);
}

