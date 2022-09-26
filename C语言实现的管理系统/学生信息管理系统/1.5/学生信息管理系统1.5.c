#include<stdio.h>
#include<stdlib.h>
void main()
{
	char sno1,sno2;
	float score11,score12,score13,score21,score22,score23;	/*score开头的变量分别储存为2为学生的3门课程的成绩*/ 
	float tscore1=0,tscore2=0;	/*tscore开头的变量分别存储2位学生各门课程的总分*/ 
	int m=2,n=3;	//m为实际学生数；n为实际课程数。这里事先设定
	int i,j;
	int item;
	while(1)
	{
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
		scanf("%d",&item);
		//根据用户的选择，完成相应的操作（本节只完成输入、输出，计算总分和退出操作）
		switch(item)
		{
			case 1:/*输入学生信息*/
				printf("请输入第一位学生的学号和三门课程的成绩:\n");
				scanf("%ld%f%f%f",&sno1,&score11,&score12,&score13);
				printf("请输入第二位学生的学号和三门课程的成绩:\n");
				scanf("%ld%f%f%f",&sno2,&score21,&score22,&score23);
				getchar();
				getchar();
				break;
			case 2:/*按姓名查询学生信息*/
				printf("功能完善中\n");
				getchar();
				getchar();
				break;
			case 3:/* 计算学生的总成绩*/
				tscore1=score11+score12+score13;
				tscore2=score21+score22+score23;
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
				if(tscore1==0||tscore2==0)//若还没有计算学生的总成绩，则计算
				{
					tscore1=score11+score12+score13;
					tscore2=score21+score22+score23;
			    }
				printf("\t学号\t课程1\t课程2\t课程3\t总成绩\n");
				printf("\t%ld\t%.lf\t%.lf%\t%.lf\t%.lf\n",sno1,score11,score12,score13,tscore1);
				printf("\t%ld\t%.lf\t%.lf%\t%.lf\t%.lf\n",sno2,score21,score22,score23,tscore2);
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
	
			 
		 
