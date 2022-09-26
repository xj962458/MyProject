#include <stdio.h>
#include <string.h>
#include <process.h>
struct
{
	char name[20];
	double tel;
} person[200];
int N = 1;
void Built()
{
	int flag;
	for (; N < 200;)
	{
		printf("\t请输入第%d个联系人姓名和电话号码（以回车键作为间隔）:\n", N);
		scanf("%s", person[N].name);
		scanf("%lf", &person[N].tel);
		N = N + 1;
		printf("\t若添加完成请输入“0”,继续添加请输入其它任意数字:");
		scanf("%d", &flag);
		if (flag == 0)
			break;
	}
	printf("\n\t*******联系人创建成功********\n");
}
void Alter()
{
	int i;
	printf("请输入修改联系人的序号:");
	scanf("%d", &i);
	if (person[i].tel == 0)
		printf("\n\t**********无此联系人!**********\n");
	else
	{
		printf("请输入修改后的此联系人姓名和电话号码（以回车键作为间隔）:\n");
		scanf("%s", person[i].name);
		scanf("%lf", &person[i].tel);
		printf("\n\t*******联系人修改成功********\n");
	}
}

void Delete()
{
	int i, j;
	printf("请输入删除联系人的序号:");
	scanf("%d", &i);
	if (N == 1 || person[i].tel == 0)
		printf("\n\t**********无此联系人!**********\n");
	else
	{
		N = N - 1;
		for (; i <= N; i++)
			for (j = 0; j < 20; j++)
			{
				person[i].name[j] = person[i + 1].name[j];
				person[i].tel = person[i + 1].tel;
			}
		printf("\n\t*******联系人删除成功********\n");
	}
}
void Num_Inquire()
{
	int i, flag = 0;
	double x;
	printf("请输入查询的电话号码:");
	scanf("%lf", &x);
	for (i = 1; i < N; i++)
	{
		if (x == person[i].tel)
		{
			flag = 1;
			printf("----%d. %-20s\t%.0lf\n", i, person[i].name, person[i].tel);
		}
	}
	if (N == 1 || flag == 0)
		printf("\n\t**********无此联系人!**********\n");
}
void Name_Inquire()
{
	int i, flag = 0;
	char x[20];
	printf("请输入查询的联系人姓名:");
	scanf("%s", x);
	for (i = 1; i < N; i++)
	{
		if (strcmp(person[i].name, x) == 0)
		{
			flag = 1;
			printf("----%d. %-20s\t%.0lf\n", i, person[i].name, person[i].tel);
		}
	}
	if (N == 1 || flag == 0)
		printf("\n\t**********无此联系人!**********\n");
}
void Show()
{
	int i;
	if (N == 0 || N == 1)
	{
		printf("\n\t**********未建联系人,通讯录为空!**********\n");
	}
	if (N != 1)
	{
		printf("\t____________________________________________________\n");
		printf("\t│序号│      联系人        │       电话号码      │\n");
		printf("\t____________________________________________________\n");
		for (i = 1; i < N; i++)
		{
			printf("\t│　%d.│%-20s│%-20.0lf │\n", i, person[i].name, person[i].tel);
			printf("\t____________________________________________________\n");
		}
	}
}
void start(int i)
{
	int flag = 2;
	switch (i)
	{
	case 1:
		Built();
		break;
	case 2:
		Alter();
		break;
	case 3:
		Delete();
		break;
	case 4:
		Num_Inquire();
		break;
	case 5:
		Name_Inquire();
		break;
	case 6:
		Show();
		;
		break;
	case 7:
		if (N == 1)
			printf("\n\t**********未建联系人,无需清空!**********\n");
		else
		{
			printf("\t***确定清空通讯录？***\n\t1.确定\t2.否\t*** 请选择:");
			scanf("%d", &flag);
			if (flag == 1)
				N = 1, printf("\n\t**********通讯录已清空!**********\n");
			else if (flag == 2)
				;
			else
				printf("选择错误!\n"), start(7);
		}
		break;
	default:
		printf("选择有误,");
		break;
	};
}
int main()
{
	int i;
	FILE *fp;
	printf("\n\t**********************欢迎使用200人通讯录**********************\n\n");
	printf("***警告:*.电话号码最好不要超过16位且不能为“0”，且开头不能有一个以\n");
	printf("\t  上的“0”，否则系统;将出现问题；\n");
	printf("\t*.若电话号码开头只有一个“0”，则输入时用“-”代替“0”，且\n");
	printf("\t  系统以此方式显示。\n\n");
	printf("***菜单:\n");
	printf("\t1.新建联系人信息;\n");
	printf("\t2.修改通讯录;\n");
	printf("\t3.删除通讯录中联系人信息;\n");
	printf("\t4.根据电话号码查询;\n");
	printf("\t5.根据姓名查询;\n");
	printf("\t6.显示通讯录;\n");
	printf("\t7.清空通讯录;\n");
	printf("\t8.将通讯录保存成文档并退出系统.\n");
	printf("请选择菜单:");
	while (1)
	{
		scanf("%d", &i);
		if (i == 8)
		{
			if ((fp = fopen("D:/通讯录.txt", "w+")) == NULL)
			{
				printf("文件打开错误!\n");
				exit(1);
			}
			else
			{
				if (N == 1)
					printf("\n\t******************无联系人,保存失败!*********************\n");
				if (N != 1)
				{
					fprintf(fp, "\t____________________________________________________\n");
					fprintf(fp, "\t│序号│      联系人        │       电话号码      │\n");
					fprintf(fp, "\t————————————————————————————————————————————————————\n");
					for (i = 1; i < N; i++)
					{
						fprintf(fp, "\t│　%d.│%-20s│%-20.0lf │\n", i, person[i].name, person[i].tel);
						fprintf(fp, "\t——————————————————————————————————————————————————\n");
					}
					printf("\n\t**********通讯录已保存在D盘的“通讯录.txt”文档中。************\n");
				}
				fclose(fp);
				printf("\n\t\t************退出成功,谢谢使用!************\n\n");
				break;
			}
		}
		start(i);
		printf("可继续选择菜单:");
	}
}
