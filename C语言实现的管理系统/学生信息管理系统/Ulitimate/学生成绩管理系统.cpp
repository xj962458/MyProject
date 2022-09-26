#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int temp, hh;
typedef struct
{
	char stu_name[40];	//姓名
	int stu_id;			//学号
	char stu_clas[40];	//班级
	double stu_cj1;		//成绩1
	double stu_cj2;		//成绩2
	double stu_cj3;		//成绩3
	double stu_cj4;		//成绩4
	double stu_cj5;		//成绩5
	double avg_grade;	//平均成绩
} student;
student all_stu[200], a[200];
int stu_number = 0;

int main()
{
	//system("color f0");
	void first();
	void secend();
	void third();
	void fourth();
	void fifth();
	void sixth();
	void seventh();
	void TC();
	void DQ();
	int option;
	do
	{
		printf("\n\n\n\n");
		printf("\t\t=====================学生成绩管理系统==================\n");
		printf("\t\t* 作者：***  班级：**** 学号：********      *\n");
		printf("\t\t*                                                     *\n");
		printf("\t\t*          1>. 输入学生成绩                           *\n");
		printf("\t\t*          2>. 显示学生成绩                           *\n");
		printf("\t\t*          3>. 查看学生成绩                           *\n");
		printf("\t\t*          4>. 删减学生成绩                           *\n");
		printf("\t\t*          5>. 修改学生成绩                           *\n");
		printf("\t\t*          6>. 保存学生信息                           *\n");
		printf("\t\t*          7>. 平均成绩排名                           *\n");
		printf("\t\t*          8>. 读取文档信息                           *\n");
		printf("\t\t*          0>. 退出管理系统                           *\n");
		printf("\t\t*                                    欢迎使用本系统！ *\n");
		printf("\t\t=======================================================\n");
		printf("\t\t输入选项，按回车进入选项: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			first();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 2:
			third();
			getchar();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 3:
			secend();
			getchar();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 4:
			fourth();
			getchar();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 5:
			fifth();
			getchar();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 6:
			sixth();
			printf("\n\n\n已将您输入的学生信息存档，亲，我很努力的记住了呦。");
			getchar();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 7:
			seventh();
			getchar();
			printf("\n\n\n===============================================================================");
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 8:
			DQ();
			printf("\n少年，请按任意键返回主菜单\n");
			getchar();
			system("cls");
			break;
		case 0:
			TC();
			printf("\n\n\n\n\n\n\n\n\t\t\t        感谢您的使用.\n\n\n\t     本系统作者：陈英杰  班级：Java(2) 学号：621413530204  \n\n    \t        若感觉本系统很好用，记得在心中默默给个赞呦！\n\n\t\t\t么么哒~~请按任意键退出。\n");
			getchar();
			exit(0);
			;
			break;
		}
	} while (option);

	return 0;
}

void first()
{
thefirst:
	system("cls");
	printf("********************************输入学生信息*********************************");
	printf("\n\n");
	int cw, cx, temp, hh;
	char op;
	printf("\n>>>>>>>>请输入姓名: ");
	scanf("%s", all_stu[stu_number].stu_name);
	printf("\n>>>>>>>>请输入学号: ");
	scanf("%d", &temp);
	all_stu[stu_number].stu_id = temp;
	getchar();
	for (cx = 0; cx < stu_number; cx++)
	{
		if (all_stu[stu_number].stu_id == all_stu[cx].stu_id)
		{
			printf("学号输入错误，如需重新输入请按(Y)退出请按(N)");
			cw = getchar();
			if (cw == 'y' || cw == 'Y')
				goto thefirst;
			else
				goto thefirstend;
		}
	}
	printf("\n>>>>>>>>请输入班级： ");
	scanf("%s", all_stu[stu_number].stu_clas);
	printf("\n>>>>>>>>请输入第一门成绩(小于等于100)： ");
	scanf("%lf", &all_stu[stu_number].stu_cj1);
	if (all_stu[stu_number].stu_cj1 > 100)
	{
		printf("输入有误，请输入正确的成绩信息，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefirst;
	}
	printf("\n>>>>>>>>请输入第二门成绩(小于等于100)： ");
	scanf("%lf", &all_stu[stu_number].stu_cj2);
	if (all_stu[stu_number].stu_cj2 > 100)
	{
		printf("输入有误，请输入正确的成绩信息，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefirst;
	}
	printf("\n>>>>>>>>请输入第三门成绩(小于等于100)： ");
	scanf("%lf", &all_stu[stu_number].stu_cj3);
	if (all_stu[stu_number].stu_cj3 > 100)
	{
		printf("输入有误，请请输入正确的成绩信息，按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefirst;
	}
	printf("\n>>>>>>>>请输入第四门成绩(小于等于100)： ");
	scanf("%lf", &all_stu[stu_number].stu_cj4);
	if (all_stu[stu_number].stu_cj4 > 100)
	{
		printf("输入有误，请输入正确的成绩信息，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefirst;
	}
	printf("\n>>>>>>>>请输入第五门成绩(小于等于100)： ");
	scanf("%lf", &all_stu[stu_number].stu_cj5);
	if (all_stu[stu_number].stu_cj5 > 100)
	{
		printf("输入有误，请输入正确的成绩信息，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefirst;
	}
	hh = (all_stu[stu_number].stu_cj1 + all_stu[stu_number].stu_cj2 + all_stu[stu_number].stu_cj3 + all_stu[stu_number].stu_cj4 + all_stu[stu_number].stu_cj5) / 5;
	all_stu[stu_number].avg_grade = hh;
	printf("\n>>>>>>>>>>平均值为__: ");
	printf("%.2lf", all_stu[stu_number].avg_grade);

	stu_number++;
thefirstone:
	printf("\n是否继续输入，如是请按(Y),否请按(N): ");
	getchar();
	scanf("%c", &op);
	if (op == 'y' || op == 'Y')
		goto thefirst;
	if (op == 'n' || op == 'N')
		goto thefirstend;
	else
		goto thefirstone;
	getchar();
thefirstend:;
	getchar();
}

void secend()
{
thesecend:
	system("cls");
	printf("\n\n**************************显示学生成绩*************************");
	int num, cw, cx, ai, i = 0;
	char op;
	printf("\n>>>>>>>>请输入要查找学生的学号: ");
	scanf("%d", &num);
	for (ai = 0; ai < stu_number; ai++)
	{
		if (num = all_stu[ai].stu_id)
		{
			i = 1;
			break;
		}
	}
	if (i == 0)
	{
		printf("未查找到此学号，亲输错了吧 = =..是否要重新输入呀，亲~~如需要请按(Y)，如不需要请按(N)将返回主菜单: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thesecend;
		if (cw == 'n' || cw == 'N')
			goto thesecendend;
	}
	else
	{

		printf("\n***************************************************************************");
		printf("\n*姓名___: ");
		printf("%s", all_stu[ai].stu_name);
		printf("\n*学号___: ");
		printf("%d", all_stu[ai].stu_id);
		printf("\n*班级___: ");
		printf("%s", all_stu[ai].stu_clas);
		printf("\n*成绩一_: ");
		printf("%.2lf", all_stu[ai].stu_cj1);
		printf("\n*成绩二_: ");
		printf("%.2lf", all_stu[ai].stu_cj2);
		printf("\n*成绩三_: ");
		printf("%.2lf", all_stu[ai].stu_cj3);
		printf("\n*成绩四_: ");
		printf("%.2lf", all_stu[ai].stu_cj4);
		printf("\n*成绩五_: ");
		printf("%.2lf", all_stu[ai].stu_cj5);
		printf("\n*平均成绩___: ");
		printf("%.2lf", all_stu[ai].avg_grade);
		printf("\n***************************************************************************");
	}
thesecendone:
	getchar();
	printf("\n\n亲~要查寻得成绩信息以显示，是否继续查阅？\n需要请安(Y),如不需要请安(N)，将返回主界面__: ");
	scanf("%c", &op);
	if (op == 'y' || op == 'Y')
		goto thesecend;
	if (op == 'n' || op == 'N')
		goto thesecendend;
	else
		goto thesecendone;
thesecendend:;
}

void third()
{
thethird:
	system("cls");
	printf("\n\n**************************显示学生信息*********************************");
	int n = 0;
	printf("\n\n>>姓名");
	printf("\t学号");
	printf("\t班级");
	printf("\t成绩一");
	printf("\t成绩二");
	printf("\t成绩三");
	printf("\t成绩四");
	printf("\t成绩五");
	printf("\t平均值");
	//for (n=0;n<stu_number;n++);
	do
	{
		printf("\n>>%s", all_stu[n].stu_name);
		printf("\t%d", all_stu[n].stu_id);
		printf("\t%s", all_stu[n].stu_clas);
		printf("\t%.2lf", all_stu[n].stu_cj1);
		printf("\t%.2lf", all_stu[n].stu_cj2);
		printf("\t%.2lf", all_stu[n].stu_cj3);
		printf("\t%.2lf", all_stu[n].stu_cj4);
		printf("\t%.2lf", all_stu[n].stu_cj5);
		printf("\t%.2lf", all_stu[n].avg_grade);
		n++;
	} while (n < stu_number);
}

void fourth()
{
thefourth:
	system("cls");
	printf("\n\n\n\n**************************删减学生成绩************************************");
	printf("\n\n");
	int num, cw, cx, ai, i = 0;
	char op;
	printf("\n>>>>>>>>请输入要查找学生的学号: ");
	scanf("%d", &num);
	for (ai = 0; ai < stu_number; ai++)
	{
		if (num == all_stu[ai].stu_id)
		{
			i = 1;
			break;
		}
	}
	if (i == 0)
	{
		printf("未查找到要删除的学生信息，是否要重新输入，亲~~如需要请按(Y)，如不需要请按(N)将返回主菜单: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefourth;
		if (cw == 'n' || cw == 'N')
			goto thefourthend;
	}
	else
	{
		stu_number--;
		for (; ai < stu_number; ai--)
		{
			all_stu[ai] = all_stu[ai + 1];
		}
	}
	printf("\n\n此学号的学生成绩信息已删除，谢谢使用本次功能，记得给赞哦.好人一生平安。");
	getchar();
thefourthone:
	getchar();
	printf("\n亲~要删除的成绩信息以删除，是否继续？\n需要请安(Y),如不需要请安(N)，将返回主界面__: ");
	scanf("%c", &op);
	if (op == 'y' || op == 'Y')
		goto thefourth;
	if (op == 'n' || op == 'N')
		goto thefourthend;
	else
		goto thefourthone;
thefourthend:;
}

void fifth()
{
thefifth:
	system("cls");
	printf("**************************修改学生成绩*************************");
	printf("\n\n");
	int num, cw, cx, ai, i = 0, cy, team;
	char op;
	printf("\n>>>>>>>>请输入要查找学生的学号: ");
	scanf("%d", &num);
	for (ai = 0; ai < stu_number; ai++)
	{
		if (num = all_stu[ai].stu_id)
		{
			i = 1;
			break;
		}
	}
	if (i == 0)
	{
		printf("未查找到要修改的学生信息，是否要重新输入，如需要请按(Y)，如不需要请按(N)将返回主菜单: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefifth;
		if (cw == 'n' || cw == 'N')
			goto thefifthend;
	}
	else
	{

		printf("***************************************************************************");
		printf("\n*姓名___: ");
		printf("%s", all_stu[ai].stu_name);
		printf("\n*学号___: ");
		printf("%d", all_stu[ai].stu_id);
		printf("\n*班级___: ");
		printf("%s", all_stu[ai].stu_clas);
		printf("\n*成绩一_: ");
		printf("%.2lf", all_stu[ai].stu_cj1);   
		printf("\n*成绩二_: ");
		printf("%.2lf", all_stu[ai].stu_cj2);
		printf("\n*成绩三_: ");
		printf("%.2lf", all_stu[ai].stu_cj3);
		printf("\n*成绩四_: ");
		printf("%.2lf", all_stu[ai].stu_cj4);
		printf("\n*成绩五_: ");
		printf("%.2lf", all_stu[ai].stu_cj5);
		printf("\n***************************************************************************");
	}
	getchar();
	printf("\n\n是否确认修改此学生成绩信息？(注：修改后将不可还原)如需修改请安(Y)，如不需修改学生信息请安(N)返回__: ");
thefifthone:
	cw = getchar();
	if (cw == 'y' || cw == 'Y')
		goto thefifthtwo;
	if (cw == 'n' || cw == 'N')
		goto thefifthend;
	else
		goto thefifthone;
thefifthtwo:
	system("cls");
	printf("\n>>>>>>>>请输入姓名: ");
	scanf("%s", all_stu[ai].stu_name);
	printf("\n>>>>>>>>请输入学号: ");
	scanf("%d", &temp);
	all_stu[ai].stu_id = temp;
	getchar();
	for (cy = 0; cy < ai; cy++)
	{
		if (all_stu[ai].stu_id == all_stu[cy].stu_id)
		{
			printf("学号输入错误，如需重新输入请按(Y)退出请按(N)");
			cw = getchar();
			if (cw == 'y' || cw == 'Y')
				goto thefifthtwo;
			else
				goto thefifthend;
		}
	}
	printf("\n>>>>>>>>请输入班级： ");
	scanf("%s", all_stu[ai].stu_clas);
	printf("\n>>>>>>>>请输入第一门成绩(小于100)： ");
	scanf("%lf", &all_stu[ai].stu_cj1);
	if (all_stu[ai].stu_cj1 > 100)
	{
		printf("输入有误，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefifthtwo;
	}
	printf("\n>>>>>>>>请输入第二门成绩(小于100)： ");
	scanf("%lf", &all_stu[ai].stu_cj2);
	if (all_stu[ai].stu_cj2 > 100)
	{
		printf("输入有误，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefifthtwo;
	}
	printf("\n>>>>>>>>请输入第三门成绩(小于100)： ");
	scanf("%lf", &all_stu[ai].stu_cj3);
	if (all_stu[ai].stu_cj3 > 100)
	{
		printf("输入有误，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefifthtwo;
	}
	printf("\n>>>>>>>>请输入第四门成绩(小于100)： ");
	scanf("%lf", &all_stu[ai].stu_cj4);
	if (all_stu[ai].stu_cj4 > 100)
	{
		printf("输入有误，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefifthtwo;
	}
	printf("\n>>>>>>>>请输入第五门成绩(小于100)： ");
	scanf("%lf", &all_stu[ai].stu_cj5);
	if (all_stu[ai].stu_cj5 > 100)
	{
		printf("输入有误，请按(Y)重新输入: ");
		getchar();
		cw = getchar();
		if (cw == 'y' || cw == 'Y')
			goto thefifthtwo;
	}
	hh = (all_stu[ai].stu_cj1 + all_stu[ai].stu_cj2 + all_stu[ai].stu_cj3 + all_stu[ai].stu_cj4 + all_stu[ai].stu_cj5) / 5;
	all_stu[ai].avg_grade = hh;
	printf("\n>>>>>>>>>>平均值为__: ");
	printf("%.2lf", all_stu[ai].avg_grade);
	getchar();
	printf("\n\n");
	printf("\n OK 此学生成绩信息已修改完成，感谢您的使用。");
thefifthfanhui:
	getchar();
	printf("\n亲~要修改的成绩信息已修改，是否继续？\n需要请安(Y),如不需要请安(N)，将返回主界面__: ");
	scanf("%c", &op);
	if (op == 'y' || op == 'Y')
		goto thefifth;
	if (op == 'n' || op == 'N')
		goto thefifthend;
	else
		goto thefifthfanhui;
thefifthend:;
}

void sixth()
{
thesixth:
	system("cls");
	printf("\n\n\n\t**************************保存输入的资料*************************");
	int i = 0;
	FILE *fp;
	if ((fp = fopen("stu_dat.txt", "wb")) == NULL)
	{
		printf("无法打开的操作!");
		return;
	}

	//for(i=0;i<stu_number;i++)
	do
	{
		printf("\n\n本次操作将为您把您输入的所有学生成绩信息存档。\n\n请按任意键进行存档，我会努力记住的！！");
		getchar();
		fprintf(fp, "%s", all_stu[i].stu_name);
		fprintf(fp, "%d", all_stu[i].stu_id);
		fprintf(fp, "%s", all_stu[i].stu_clas);
		fprintf(fp, "%lf", all_stu[i].stu_cj1);
		fprintf(fp, "%lf", all_stu[i].stu_cj2);
		fprintf(fp, "%lf", all_stu[i].stu_cj3);
		fprintf(fp, "%lf", all_stu[i].stu_cj4);
		fprintf(fp, "%lf", all_stu[i].stu_cj5);
		fprintf(fp, "%lf", all_stu[i].avg_grade);
		i++;
	} while (i < stu_number);
	fclose(fp);
	fflush(stdin);
	getchar();
}

void seventh()
{
theseventh:
	system("cls");
	printf("\n\n**************************查看学生平均成绩排名*********************************");
	int i;
	int t = 1;
	int j;
	printf("%d", stu_number);
	for (i = stu_number - 1; i > 0; i--)
		for (j = 0; j < i; j++)
		{
			if (all_stu[j].avg_grade > all_stu[j + 1].avg_grade)
			{
				a[t] = all_stu[j];
				all_stu[j] = all_stu[j + 1];
				all_stu[j + 1] = a[t];
			}
		}
	printf("\n\n>>姓名");
	printf("\t学号");
	printf("\t班级");
	printf("\t成绩一");
	printf("\t成绩二");
	printf("\t成绩三");
	printf("\t成绩四");
	printf("\t成绩五");
	printf("\t平均值");
	for (i = 0; i < stu_number; i++)
	//do
	{
		printf("\n>>%s", all_stu[i].stu_name);
		printf("%d", all_stu[i].stu_id);
		printf("%s", all_stu[i].stu_clas);
		printf("%.2lf", all_stu[i].stu_cj1);
		printf("%.2lf", all_stu[i].stu_cj2);
		printf("%.2lf", all_stu[i].stu_cj3);
		printf("%.2lf", all_stu[i].stu_cj4);
		printf("%.2lf", all_stu[i].stu_cj5);
		printf("%.2lf", all_stu[i].avg_grade);
		//i++;
	} //while(i<stu_number);

	// printf(">>%s \t %d \t %s\t  %.2f\t  %.2f\t  %.2f\t %.2f\t  %.2f\t  %.2f \n",a[i].stu_name,a[i].stu_id,a[i].stu_clas,a[i].stu_cj1,a[i].stu_cj2,a[i].stu_cj3,a[i].stu_cj4,a[i].stu_cj5,a[i].avg_grade);

theseventhend:;
}

void TC()
{
	system("cls");
	getchar();
}

void DQ()
{
	system("cls");
	printf("\n\n**************************读取文档信息*********************************");
	getchar();
	student a[200], p;
	int n, i = 0;
	FILE *fp;
	if ((fp = fopen("stu_dat.txt", "rb")) == NULL)
	{
		printf("打开文件失败，请查看文件名是否正确！\n");
		getchar();
		goto theDQend;
	}
	for (n = 0; !feof(fp); n++)
	//do
	{
		fscanf(fp, "%s", a[n].stu_name);
		fscanf(fp, "%d", a[n].stu_id);
		fscanf(fp, "%s", a[n].stu_clas);
		fscanf(fp, "%f", a[n].stu_cj1);
		fscanf(fp, "%f", a[n].stu_cj2);
		fscanf(fp, "%f", a[n].stu_cj3);
		fscanf(fp, "%f", a[n].stu_cj4);
		fscanf(fp, "%f", a[n].stu_cj5);
		fscanf(fp, "%f", a[n].avg_grade);
		//n++;
	} //while(!feof(fp));
	fclose(fp);
	printf("\t学号");
	printf("\t班级");
	printf("\t成绩一");
	printf("\t成绩二");
	printf("\t成绩三");
	printf("\t成绩四");
	printf("\t成绩五");
	printf("\t平均值");
	for (i = 0; i < n; i++)
	//do
	{
		printf("\n%s", a[i].stu_name);
		printf("%d", a[i].stu_id);
		printf("%s", a[i].stu_clas);
		printf("%10.2f", a[i].stu_cj1);
		printf("%10.2f", a[i].stu_cj2);
		printf("%10.2f", a[i].stu_cj3);
		printf("%10.2f", a[i].stu_cj4);
		printf("%10.2f", a[i].stu_cj5);
		printf("%.2f", a[i].avg_grade);
		//i++;
	} //while(i<n);
theDQend:;
}

