//insert.c
#pragma once
#include "preProcess.h"
 
void printheader();
void PRINTdata(ZGGZ pp);
void disp(ZGGZ tp[],int n);
void wrong();
void nofind();
void stringinput(char *t,int lens,char *notice);/*输入字符串，并进行长度验证明，长度必须小于lens，*/
float numberinput(char *notice);/*输入数值浮点数，对数值检验后返回该值，数值必须大于等于0*/
extern int saveflag;				/*需要存盘的标志变量*/
/*插入记录*/
int insert(ZGGZ tp[],int n){
	char ch,num[10],s[10];	/*s数组保存插入点之前的编号，num数组保存输入的新记录编号*/
	ZGGZ newinfo;
	int flag=0,i=0,kkk=0;
	system("cls");
	disp(tp,n);
	while(1){
		stringinput(s,10,"Please input insert location after the Number:");
		flag=0;i=0;
		while(i<n){			/*查询，flag=1为表示该编号存在*/
			if (strcmp(tp[i].num,s)==0)
			{
				/* code */
				kkk=i;
				flag=1;
				break;
			}
			i++;
		}
		if (flag==1)
		{
			/* code */
			break;			/* 若编号存在，则进行插入之前的新记录输入操作*/
		}
		else{
			getchar();
			printf("\n=====>The Number %s is not existing,try again?(y/n):",s);
			scanf("%c",&ch);
			if (ch=='y'||ch=='Y')
			{
				/* code */
				continue;
			}
			else
				return n;
		}
	}
	/*以下新记录的插入操作与add()相同*/
	while(1){
		stringinput(num,10,"input new employee Number:");
		i=0;flag=0;
		while(i<n){				/*查询，flag为1时表示该编号存在*/
			if (strcmp(tp[i].num,num)==0)
			{
				/* code */
				flag=1;break;
			}
			i++;
		}
		if (flag==1)
		{
			/* code */
			getchar();
			printf("\n====>Sorry,The number %s is existing,try again(y/n)",num);
			scanf("%c",&ch);
			if (ch=='y'||ch=='Y')
			{
				/* code */
				continue;
			}else
				return n;
		}else
			break;
	}
	strcpy(newinfo.num,num);		/*将字符串num复制到newinfo.num中*/
	stringinput(newinfo.name,15,"Name:");
	newinfo.jbgz=numberinput("jbgz:");		/* 输入并校验基本工资*/
	newinfo.jj=numberinput("jiangjin");		/*输入并梭验jiangjing */
	newinfo.kk=numberinput("koukuan:");		/*输入并检验koukuan*/
	newinfo.yfgz=newinfo.jbgz+newinfo.jj-newinfo.kk;
	newinfo.sk=newinfo.yfgz*0.12;
	newinfo.sfgz=newinfo.yfgz-newinfo.sk;
	saveflag=1;			/*在main()中有对该全局变量的判断，若为1则存盘*/
	for(i=n-1;i>kkk;i--){
		strcpy(tp[i+1].num,tp[i].num);
		strcpy(tp[i+1].name,tp[i].name);
		tp[i+1].jbgz=tp[i].jbgz;
		tp[i+1].jj=tp[i].jj;
		tp[i+1].kk=tp[i].kk;
		tp[i+1].yfgz=tp[i].yfgz;
		tp[i+1].sk=tp[i].sk;
		tp[i+1].sfgz=tp[i].sfgz;
	}
	strcpy(tp[kkk+1].num,newinfo.num);/*在tp[kkk]元素位置后插入新记录*/
	strcpy(tp[kkk+1].name,newinfo.name);
	tp[kkk+1].jbgz=newinfo.jbgz;
	tp[kkk+1].jj=newinfo.jj;
	tp[kkk+1].kk=newinfo.kk;
	tp[kkk+1].yfgz=newinfo.yfgz;
	tp[kkk+1].sk=newinfo.sk;
	tp[kkk+1].sfgz=newinfo.sfgz;
	n++;
	disp(tp,n);
	printf("\n\n");
	getchar();
	return n;
}
