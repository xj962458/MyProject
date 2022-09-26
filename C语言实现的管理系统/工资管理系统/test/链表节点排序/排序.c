#include"stdio.h"
#include"stdlib.h"
#include"string.h"
struct student
{
	struct student *ahead;
	float grade[10];
	char name[10];
	char x[10];
	struct student *next;
}*head, *end, *New, *get, *stu;
int input(int N, char **G)//数据输入
//变量说明：“N”为考试的科目数量，此处**G为字符串指针数组，其中存储着考试科目。
{
	int i, c = 1, icount = 0, s[10], j, k, d;
	char r[10];
	for (j = 0; j < 10; j++)
		s[j] = 0;
	while (c)
	{
		New = (struct student *)malloc(sizeof(struct student));
		printf("\t\t输入该名学生姓名(结束请按‘0’):");
		scanf("%s", New->name);
		if (New->name[0] != 48)
		{
			printf("\t\t输入该名学生学号:");
			scanf("%s", r);
			icount++;
			strcpy(New->x, r);
			New->grade[N] = 0;
			for (i = 0; i < N; i++)
			{
				printf("\t\t%s成绩:", G[i]);
				scanf("%f", &New->grade[i]);
				if (New->grade[i] < 60)
					s[i]++;
				New->grade[N] = New->grade[N] + New->grade[i];
			}
			strcpy(New->mima, "1234");
			end->next = New;
			New->ahead = end;
			end = New;
			end->next = NULL;
		}
	}
	else
	{
		c = 0;
	}
}
int paixu(int N)//成绩排序
{
	int i;//在程序的后便会让用户选择升序还是降序排序，变量i的作用是根据i的值选择排序方式。若i为1则降序排列，0则升序排列
	struct student *min, *xunow, *uend;
	uend = (struct student *)malloc(sizeof(struct student));
	uend->grade[0] = -1;
	uend->next = NULL;
	uend->ahead = end;
	end->next = uend;

