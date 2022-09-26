//输入各销售员的相关数据
#include<x.h>
void Write(LinkList head, int n)
{
	printf("输入销售员序号，姓名及销售额\n");
    LinkList p;
    int i;
    for(i=0;i<n;i++)
	{
		printf("第%d位:",i+1);
        p=(LinkList)malloc(sizeof(Node));
        scanf("%s%s%f",p->no,p->name,&p->sales);
        p->link=head->link;
        head->link=p;
    }
}
