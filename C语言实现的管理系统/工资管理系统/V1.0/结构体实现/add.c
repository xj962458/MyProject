//add.c
/*增加记录*/
#pragma once
#include "preProcess.h"
void disp(ZGGZ tp[],int n);
void wrong();
void stringinput(char *t,int lens,char *notice);/*输入字符串，并进行长度验证明，长度必须小于lens，*/
float numberinput(char *notice);/*输入数值浮点数，对数值检验后返回该值，数值必须大于等于0*/
int add(ZGGZ tp[],int n){
	char ch,num[10];
	int i,flag=0;
	system("cls");	/*清屏*/
	disp(tp,n);		/*显示已有员工工资信息*/
	while(1){		/*一次可输入多条记录，直到输入编号为0的记录才结束添加*/
		while(1){		/*输入员工编号，保证该编号没有被使用，若输入编号为0 ，则退出添加操作*/
			stringinput(num,10,"input number(press '0' return menu):");/*格式化输入编号并检验*/
			flag=0;
			if (strcmp(num,"0")==0)	/*输入为0，则退出添加操作，返回主界面*/
			{
				/* code */
				return n;
			}
			i=0;
			while(i<n){		/*查询该编号是否已经存在，若存在，则重新输入一个未被占用的编号*/
				if (strcmp(tp[i].num,num)==0)
				{
					/* code */
					flag=1;
					break;
				}
				i++;
			}
			if (flag==1)	/*提示用户是否重新输入*/
			{
				/* code */
				getchar();
				printf("======>The number %s is existing,try again?(y/n):", num);
				scanf("%c",&ch);
				if (ch=='y'||ch=='Y')
				{
					/* code */
					continue;
				}
				else
					return n;
			}
			else
				break;
		}
		strcpy(tp[n].num,num);		/*将字符串num复制到tp[n].num中*/
		stringinput(tp[n].name,15,"Name:");		
		tp[n].jbgz=numberinput("jbgz:");			/*输入并校验基本工资*/
		tp[n].jj=numberinput("jiangjin:");		/*输入并检验奖金*/
		tp[n].kk=numberinput("koukuan:");		/*输入并检验扣款*/
		tp[n].yfgz=tp[n].jbgz+tp[n].jj-tp[n].kk;	/*计算应发工资*/
		tp[n].sk=tp[n].yfgz*0.12l;		/*计算税金，假定取应发工资的12%*/
		tp[n].sfgz=tp[n].yfgz-tp[n].sk;			/*计算实发工资*/
		n++;
	}
	return n;
}
