#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


// 职工信息结构体
struct employee_Info
{
	char num;
	char name[20];
	char sex[20];
	int age;
	char xueli[30];
	int wage;
	char tel[20];
};
typedef struct employee_Info EMP;

// 链表结构体节点
struct message_Info
{
	EMP employee_data;
	struct message_Info *next;
};
typedef struct message_Info MES;

// 录入数据模块
void Creat_linklist(MES * head)
{
	MES *tail, *pnew;
	int i, m;
	printf("请输入需要创建信息的职工人数：");
	scanf("%d", &m);

	tail = head;

	printf("请输入职工信工信息：\n");
	for (i = 0; i < m; i++)
	{

		pnew = (MES *) malloc(sizeof(MES));
		if (head == NULL)
		{
			printf("no enough memory!\n");
			exit(0);
		}
		printf("请输入职工号：");
		scanf("%d", &pnew->employee_data.num);
		printf("请输入姓名：");
		scanf("%s", &pnew->employee_data.name);
		printf("请输入性别：");
		scanf("%s", &pnew->employee_data.sex);
		printf("请输入年龄：");
		scanf("%d", &pnew->employee_data.age);
		printf("请输入学历：");
		scanf("%s", &pnew->employee_data.xueli);
		printf("请输入工资：");
		scanf("%d", &pnew->employee_data.wage);
		printf("请输入电话：");
		scanf("%s", &pnew->employee_data.tel);
		pnew->next = NULL;

		tail->next = pnew;
		tail = pnew;
	}
}


// 浏览数据
void Display_Linklist(MES * head)
{
	MES *p;
	for (p = head->next; p != NULL; p = p->next)
	{
		printf("职工号：%d\n", p->employee_data.num);
		printf("姓名：%s\n", p->employee_data.name);
		printf("性别：%s\n", p->employee_data.sex);
		printf("年龄：%d\n", p->employee_data.age);
		printf("学历：%s\n", p->employee_data.xueli);
		printf("工资：%d\n", p->employee_data.wage);
		printf("电话：%s\n", p->employee_data.tel);
	}
	printf("\n");
}


// 删除数据
void Delete_Linklist(MES * head)
{
	MES *p, *q;
	int i, j;

	printf("请输入你想要删除的职工号：");
	scanf("%d", &i);
	if (i == 0)
		return;

	p = head;
	for (j = 1; j < i && p->next != NULL; j++)
		p = p->next;
	if (p->next == NULL)
	{
		printf("查无此职工号！");
		exit(0);
	}

	q = p->next;
	p->next = q->next;
	free(q);
}

// 添加数据
void Insert_Linklist(MES * head)
{
	MES *p, *pnew;

	p = head;
	pnew = (MES *) malloc(sizeof(MES));
	if (pnew == NULL)
	{
		printf("no enough memory!\n");
		exit(0);
	}

	printf("请输入职工号：");
	scanf("%d", &pnew->employee_data.num);
	printf("请输入姓名：");
	scanf("%s", &pnew->employee_data.name);
	printf("请输入性别：");
	scanf("%s", &pnew->employee_data.sex);
	printf("请输入年龄：");
	scanf("%d", &pnew->employee_data.age);
	printf("请输入学历：");
	scanf("%s", &pnew->employee_data.xueli);
	printf("请输入工资：");
	scanf("%d", &pnew->employee_data.wage);
	printf("请输入电话：");
	scanf("%s", &pnew->employee_data.tel);
	pnew->next = NULL;

	pnew->next = p->next;
	p->next = pnew;
}


// 修改数据
void Modify(MES * head)
{
	MES *p;
	int a;
	printf("请输入你想修改的职工号：");
	scanf("%d", &a);

	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->employee_data.num == a)
		{
			printf("已找到职工信息：\n");
			printf("原职工号：%d,现职工号：", p->employee_data.num);
			scanf("%d", &p->employee_data.num);
			printf("原职工姓名：%s,现职工姓名：",
				   p->employee_data.name);
			scanf("%s", &p->employee_data.name);
			printf("原职性别：%s,现职性别：", p->employee_data.sex);
			scanf("%s", &p->employee_data.sex);
			printf("原职工年龄：%d,现职工年龄：",
				   p->employee_data.age);
			scanf("%d", &p->employee_data.age);
			printf("原职工学历：%s,现职工学历：",
				   p->employee_data.xueli);
			scanf("%s", &p->employee_data.xueli);
			printf("原职工工资：%d,现职工工资：",
				   p->employee_data.wage);
			scanf("%d", &p->employee_data.wage);
			printf("原职工电话：%s,现职工电话：",
				   p->employee_data.tel);
			scanf("%s", &p->employee_data.tel);
		}
		if (p == NULL)
			printf("对不起，您需要修改的信息不存在！");
	}
}



// 按工号查找数据
void Search_num(MES * head)
{
	MES *p;
	int a;
	printf("请输入你要查询的职工号：");
	scanf("%d", &a);

	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->employee_data.num == a)
			printf("已找到，其记录为：\n");
		printf("工号：%d\n", p->employee_data.num);
		printf("姓名：%s\n", p->employee_data.name);
		printf("性别：%s\n", p->employee_data.sex);
		printf("年龄：%d\n", p->employee_data.age);
		printf("学历：%s\n", p->employee_data.xueli);
		printf("工资：%d\n", p->employee_data.wage);
		printf("电话：%s\n", p->employee_data.tel);
	}

	if (p == NULL)
		printf("对不起，查无此人！");

}


// 按姓名查找数据
void Search_name(MES * head)
{
	MES *p;
	char name[20];
	printf("请输入你要查询的职工姓名：");
	scanf("%s", &name);

	for (p = head->next; p != NULL; p = p->next)
	{
		if (p->employee_data.num == name)
			printf("已找到，其记录为：\n");
		printf("工号：%d\n", p->employee_data.num);
		printf("姓名：%s\n", p->employee_data.name);
		printf("性别：%s\n", p->employee_data.sex);
		printf("年龄：%d\n", p->employee_data.age);
		printf("学历：%s\n", p->employee_data.xueli);
		printf("工资：%d\n", p->employee_data.wage);
		printf("电话：%s\n", p->employee_data.tel);
	}

	if (p == NULL)
		printf("对不起，查无此人！");

}





// 写入文件
void Write_file(MES * head)
{
	MES *p;
	FILE *fp;

	if ((fp = fopen("职工管理系统.dat", "wb")) == NULL)
	{
		printf("无法打开文件！");
		exit(0);
	}

	for (p = head->next; p != NULL; p = p->next)
	{
		fprintf(fp, "%d,%s,%s,%d,%s,%d,%s", p->employee_data.num,
				p->employee_data.name, p->employee_data.sex,
				p->employee_data.age, p->employee_data.xueli,
				p->employee_data.wage, p->employee_data.tel);

	}
	fclose(fp);
}

// 显示数据
void Read_file(MES * head)
{
	MES *p;
	FILE *fp;

	if ((fp = fopen("职工管理系统.dat", "rb")) == NULL)
	{
		printf("无法打开文件！");
		exit(0);
	}

	for (p = head->next; p != NULL; p = p->next)
		fscanf(fp, "%d,%s,%s,%d,%s,%d,%s", &p->employee_data.num,
			   p->employee_data.name, p->employee_data.sex,
			  &p->employee_data.age, p->employee_data.xueli,
			   &p->employee_data.wage, p->employee_data.tel);

	if (p = NULL)
		fscanf(fp, "%d,%s,%s,%d,%s,%d,%s", &p->employee_data.num,
			   p->employee_data.name, p->employee_data.sex,
			  &p->employee_data.age, p->employee_data.xueli,
			   &p->employee_data.wage, p->employee_data.tel);

	fclose(fp);

	for (p = head->next; p != NULL; p = p->next)
	{
		printf("工号：%d\n", p->employee_data.num);
		printf("姓名：%s\n", p->employee_data.name);
		printf("性别：%s\n", p->employee_data.sex);
		printf("年龄：%d\n", p->employee_data.age);
		printf("学历：%s\n", p->employee_data.xueli);
		printf("工资：%d\n", p->employee_data.wage);
		printf("电话：%s\n", p->employee_data.tel);
	}
}






// 主函数
int main()
{
	MES *head;
	int n;

	head = (MES *) malloc(sizeof(MES));
	if (head == NULL)
	{
		printf("no enough memory!\n");
		exit(0);
	}
	head->next = NULL;

	while (1)
	{
		printf
			("◤▔▔▔▔▔欢迎进入职工信息管理系统▔▔▔▔▔◥\n");
		printf("              1.录入职工信息\n");
		printf("              2.浏览职工信息\n");
		printf("              3.删除职工信息\n");
		printf("              4.添加职工信息\n");
		printf("              5.修改职工信息\n");
		printf("              6.按工号查询职工信息\n");
		printf("              7.按姓名查询职工信息\n");
		printf("              8.退出\n");
		printf("              9.文件显示职工信息\n");
		printf
			("◣▁▁▁▁▁▁▁▁▁谢谢使用▁▁▁▁▁▁▁▁▁◢\n");


		printf("请输入你想要执行的功能代号：");
		scanf("%d", &n);

		switch (n)
		{
		case 1:
			Creat_linklist(head);
			Write_file(head);
			break;
		case 2:
			Display_Linklist(head);
			break;
		case 3:
			Delete_Linklist(head);
			break;
		case 4:
			Insert_Linklist(head);
			break;
		case 5:
			Modify(head);
			break;
		case 6:
			Search_num(head);
			break;
		case 7:
			Search_name(head);
			break;
		case 8:
			printf("谢谢使用！");
			break;
		case 9:
			Read_file(head);
			break;
		}

	}
	return 0;
}


