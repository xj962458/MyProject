#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>

#define STU_NUM 40 //最多学生人数
#define COURSE_NUM 3 //最多课程门数
#define NAME_LEN 15 //最长姓名包含的字符数目


//定义学生结构体类型，表示学生记录应具有的形式
struct student
{
	long sno;		/*学号*/
	char sname[NAME_LEN];	/*姓名*/
	float score[COURSE_NUM];	/*各门课程成绩*/
	float total;	/*总分*/
	//struct student *next;		/*单链表结构使用；结构体数组则不用此语句*/
};

int flag=0;	//作为总成绩是否计算的一个标志，flag为0时表示没有计算

//所有函数的原型声明放在此处
//功能 1:输入学生信息
void InputStuInfor(struct student stu[],int m, int n);
//功能 2:按姓名查询学生信息
void QueryByName(struct student stu[],int m,int n);
//功能 3:计算学生的总成绩
void StuTotalScore(struct student stu[],int m,int n);
//功能 4:计算各门课程的平均分
void CourseAverageScore(struct student stu[],float avecourse[],int m, int n);
//功能 5:按学生总成绩由高到低排序
void SortbyTotalScore(struct student stu[],int m,int n);
//功能 6:输出学生信息
void DisplayStuInfor(struct student stu[],int m,int n);
//菜单函数:显示菜单,，获取并返回用户选择的功能项编号
int Menu(void);

int main()
{
	struct student stu[STU_NUM];		//定义学生记录，最多只有STU_NUM个同学
	float avecourse[COURSE_NUM]={0};	 //avecourse 数组存储每门课程的平均分


	int m=2,n=3;	//m为实际学生数；n为实际课程数。这里事先设定n=3
	int i,j;
	int item;


	printf("请输入学生的总人数");
	scanf("%d",&m);
	while(1)
	{
		item=Menu();//菜单显示，并获取用户选择的菜单功能项编号
	

		//根据用户的选择，完成相应的操作（本节只完成输入、输出，计算总分和退出操作）
		switch(item)
		{
		case 1:
			InputStuInfor(stu,m,n);
			getchar(); //输入学生信息
			getchar();
			break;
		case 2:
			QueryByName(stu,m,n); //按姓名查询学生信息
			getchar();
			getchar();
			break;
		case 3:
			StuTotalScore(stu,m,n); //计算学生的总成绩
			flag=1;
			getchar(); getchar();
			break;
		case 4:
			CourseAverageScore(stu,avecourse,m,n); // 计算各门课程的平均分
			getchar();getchar();
			break;
		case 5:
			SortbyTotalScore(stu,m,n); //按总成绩降序排
			getchar();getchar();
			break;
		case 6:
			DisplayStuInfor(stu,m,n); //输出学生信息
			getchar();getchar();
			break;
		case 0:/*退出*/
			exit(0);
			printf("程序结束\n");
			getchar();getchar();
			break;
		default:
			printf("\n\n输入的命令不对,请重新输入!!\n");
			getchar();getchar();
			break;
		}
	}
}




//下面是所有函数的具体实现
//功能1:输入学生信息
void InputStuInfor(struct student stu[],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		printf("请输入第%d位学生的学号、姓名和各门课程成绩\n",i+1);
		printf("学 号:");
		scanf("%ld",&stu[i].sno);
		getchar();		 //过滤掉回车键
		printf("姓 名:");
		gets(stu[i].sname);
		for(j=0;j<n;j++)
		{
			printf("课程%d成绩:",j+1);
			scanf("%f",&stu[i].score[j]);
		}
	}
}

//功能 2:按姓名查询学生信息
void QueryByName(struct student stu[],int m,int n)
{
	printf("函数实现中!!\n");
}
//功能 3;计算学生的总成绩
void StuTotalScore(struct student stu[],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		stu[i].total=0;
		for(j=0;j<n;j++)
			stu[i].total+=stu[i].score[i];
	}
	printf("各个学生的总成绩计算完毕!\n");
}
//功能 4:计算各门课程的平均分
void CourseAverageScore(struct student stu[],float avecourse[],int m,int n)
{
	printf("函数实现中!\n");
}
//功能 5：按学生总成绩由高到低排序
void SortbyTotalScore(struct student stu[],int m,int n)
{
	printf("函数实现中!!\n");
}
//功能 6:输出学生信息
void DisplayStuInfor (struct student stu[],int m,int n)
{
	int i,j;
	if(flag==0)//若还没有计算学生的总成绩，则调用 StuTotalScore( )函数进行计算
		StuTotalScore(stu,m,n);
	printf("\t学号\t姓名\t\t课程1\t课程2\t课程3\t总成绩\n");
	for(i=0;i<m;i++)
	{ 
		printf("\t%ld%-8s",stu[i].sno,stu[i].sname);//输出学号与姓名
		for(j=0;j<m;j++)//输出n门课程的成绩
			printf("\t%.1f",stu[i].score[j]);
		printf("\t%.1f\n",stu[i].total);//输出总成绩
	}
}
//菜单函数；显示菜单，获取并返回用户选择的功能项袖号。
int Menu(void)
{ //用户菜单
	int item;
	system("cls");/*清屏操作*/
	printf("\n\t这是班级管理系统，请选择你要的操作:\n\n");
	printf("\t\t1:输入学生信息\n");
	printf("\t\t2:按姓名查询学生信息\n");
	printf("\t\t3:计算学生的总成绩\n");
	printf("\t\t4:计算各门课程的平均分\n");
	printf("\t\t5:按学生总成绩由高到低排序\n");
	printf("\t\t6:输出学生信息\n");
	printf("\t\t0:退出\n");


	printf("\n\n请输入命令:");
	scanf("%d",&item); /*读用户选择的命令*/
	return item;
}


