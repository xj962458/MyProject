#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STU_NUM 40 //最多学生人数
#define COURSE_NUM 3 //最多课程门数
#define NAME_LEN 15 //最长姓名包含的字符数目
//所有函数的原型声明放在此处
//功能 1:输入学生信息
void InputStuInfor(long sno[], char sname[][NAME_LEN],float score[][COURSE_NUM],int m, int n);
//功能 2:按姓名查询学生信息
void QueryByName(long sno[], char sname[][NAME_LEN],float score[][COURSE_NUM],float tscore[],int m,int n);
//功能 3:计算学生的总成绩
void StuTotalScore(float score[][COURSE_NUM],float tscore[],int m,int n);
//功能 4:计算各门课程的平均分
void CourseAverageScore(float score[][COURSE_NUM], float avecourse[], int m, int n);
//功能 5:按学生总成绩由高到低排序
void SortbyTotalScore(long sno[],char sname[][NAME_LEN],float score[][COURSE_NUM], float tscore[],int m,int n);
//功能 6:输出学生信息
void DisplayStuInfor(long sno[],char sname[][NAME_LEN],float score[][COURSE_NUM],float tscore[],int m,int n);
//菜单函数:显示菜单,，获取并返回用户选择的功能项编号
int Menu(void);

void main()
{
	long sno[STU_NUM];//sno数组存储学生学号
	char sname[STU_NUM][NAME_LEN];//sname数组存储学生姓名
	float score[STU_NUM][COURSE_NUM];//score数组存储学生成绩
	float avecourse[COURSE_NUM]={0};//avercourse数组存储课程平均分
	float tscore[STU_NUM]={0};/*tscore数组存储每位学生成绩的总分，
								其中tscore的初值设定为0，可以作为是否计算总成绩操作的标志*/

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
			InputStuInfor(sno,sname,score,m,n);
			getchar(); //输入学生信息
			getchar();
			break;
		case 2:
			QueryByName(sno,sname,score,tscore,m,n); //按姓名查询学生信息
			getchar();
			getchar();
			break;
		case 3:
			StuTotalScore(score,tscore,m,n); //计算学生的总成绩
			getchar(); getchar();
			break;
		case 4:
			CourseAverageScore(score,avecourse,m,n); // 计算各门课程的平均分
			getchar();getchar();
			break;
		case 5:
			SortbyTotalScore(sno,sname,score,tscore,m,n); //按总成绩降序排
			getchar();getchar();
			break;
		case 6:
			DisplayStuInfor(sno,sname,score,tscore,m,n); //输出学生信息
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
void InputStuInfor(long sno[],char sname[][NAME_LEN],float score[][COURSE_NUM],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		printf("请输入第%d位学生的学号、姓名和各门课程成绩\n",i+1);
		printf("学 号:");
		scanf("%ld",&sno[i]);
		getchar(); //过滤掉回车键
		printf("姓 名:");
		gets(sname[i]);
		for(j=0;j<n;j++)
		{
			printf("课程%d成绩:",j+1);
			scanf("%f",&score[i][j]);
		}
	}
}

//功能 2:按姓名查询学生信息
void QueryByName(long sno[],char sname[][NAME_LEN],float score[][COURSE_NUM],float tscore[],int m,int n)
{
	printf("函数实现中!!\n");
}
//功能 3;计算学生的总成绩
void StuTotalScore(float score[][COURSE_NUM],float tscore[],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		tscore[i]=0;
		for(j=0;j<n;j++)
			tscore[i]+=score[i][j];
	}
	printf("各个学生的总成绩计算完毕!\n");
}
//功能 4:计算各门课程的平均分
void CourseAverageScore(float score[][COURSE_NUM],float avecourse[], int m,int n)
{
	printf("函数实现中!\n");
}
//功能 5：按学生总成绩由高到低排序
void SortbyTotalScore(long sno[],char sname[][NAME_LEN],float score[][COURSE_NUM],float tscore[],int m,int n)
{
	printf("函数实现中!!\n");
}
//功能 6:输出学生信息
void DisplayStuInfor (long sno[],char sname[][NAME_LEN],float score[][COURSE_NUM],float tscore[],int m,int n)
{
	int i,j;
	if(tscore[0]==0)//若还没有计算学生的总成绩，则调用 StuTotalScore( )函数进行计算
		StuTotalScore(score,tscore,m,n);
	printf("\t学号\t姓名\t\t课程1\t课程2\t课程3\t总成绩\n");
	for(i=0;i<m;i++)
	{ 
		printf("\t%ld%-8s",sno[i],sname[i]);//输出学号与姓名
		for(j=0;j<m;j++)//输出n门课程的成绩
			printf("\t%.1f",score[i][j]);
		printf("\t%.1f\n",tscore[i]);//输出总成绩
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


