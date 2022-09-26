#include<stdio.h>
#include<stdlib.h>

#define STU_NUM 40 //最多学生人数
#define COURSE_NUM 3 //最多课程门数
#define NAME_LEN 15 //最长姓名包含的字符数目
void main()
{
	long sno[STU_NUM];//sno数组存储学生学号
	char sname[STU_NUM][NAME_LEN];//sname数组存储学生姓名
	float score[STU_NUM][COURSE_NUM];//score数组存储学生成绩
	float avecourse[COURSE_NUM]={0};//avercourse数组存储课程平均分
	float tscore[STU_NUM]={0};/*tscore数组存储每位学生成绩的总分，
								其中tscore的初值设定为0，可以作为是否计算总成绩操作的标志*/

	int m=2,n=3;	//m为实际学生数；n为实际课程数。这里事先设定
	int i,j;
	int item;
	printf("请输入学生的总人数");
	scanf("%d",&m);
	while(1)
	{
		//先输出菜单
		system("cls");/*清屏操作*/
		printf("\n\t这是班级管理系统，请选择你要的操作:\n\n");
		printf("\t\t1:输入学生信息\n");
		printf("\t\t2:按姓名查询学生信息\n");
		printf("\t\t3:计算学生的总成绩\n");
		printf("\t\t4:计算各门课程的平均分\n");
		printf("\t\t5:按学生总成绩由高到低排序\n");
		printf("\t\t6:输出学生信息\n");
		printf("\t\t0:退出\n");

		//提示用户选择菜单，并接受用户选择
		printf("\n\n请输入命令:");
		scanf("%d",&item);/*输入选择命令*/
		//根据用户的选择，完成相应的操作（本节只完成输入、输出，计算总分和退出操作）
		switch(item)
		{
			case 1:/*输入学生信息*/
				for(i=0;i<m;i++)
				{
					printf("请输入第%d位学生的学号、姓名和各门课程的成绩:\n",i+1);
					printf("学号");
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
					getchar();
					getchar();
					break;
			case 2:/*按姓名查询学生信息*/
				printf("功能完善中\n");
				getchar();
				getchar();
				break;
			case 3:/* 计算学生的总成绩*/
				for(i=0;i<m;i++)
				{
					tscore[i]=0;
					for(j=0;j<n;j++)
						tscore[i]+=score[i][j];
				}
				printf("各个学生的总成绩计算完毕!\n");
				getchar();getchar();
				break;
			case 4:/*计算各门课程的平均分*/
				printf("功能完善中\n");
				getchar();getchar();
				break;
			case 5:/*按学生总成绩由高到低排序*/
			 	printf("功能完善中\n");
				getchar();getchar();
				break;
			case 6:/*输入学生信息*/
				if(tscore[0]=0)//若还没有计算学生的总成绩，则计算
				{
					for(i=0;i<m;i++)
					{
						tscore[i]=0;
						for(j=0;j<n;j++)
							tscore[i]+=score[i][j];
					}
			    }
				printf("\t学号\t课程1\t课程2\t课程3\t总成绩\n");
				for(i=0;i<m;i++)
				{
					printf("\t%ld%-8s",sno[i],sname[i]);//输出学号与姓名
					for(j=0;j<n;j++)//输出n门课程的成绩
						printf("\t%.1f\n",tscore[i]);
					printf("\t%.1f\n",tscore[i]);//输出总成绩
				}
				getchar();getchar(); 
				break;
			case 0:/*退出*/
				exit(0);
				printf("程序结束\n");
				getchar();getchar();
				break;
			default:
				printf("\n\n输入的命令不对，请重新输入!!\n");
				getchar();getchar();
				break;
			
		}
	}
}
	
			 
		 
