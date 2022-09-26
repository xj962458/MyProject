#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
	char no[12];
	char name[40];
	float sales;
	struct node *link;
}Node,*LinkList;

void aaa();
int bbb(void);
void ccc();
int fff(int a[],int n,int p,int fz);
void Sort(LinkList head, int n);
void Write(LinkList head, int n);
