#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
//一个节点包含了一个学生的所有信息
typedef struct list
{
	int number;                //学号
	char name[20];             //姓名
	char brithday[20];		   //生日
	short major;			   //学院
	int grade1;				   //课程1的成绩(必修课)
	int grade2;				   //课程2的成绩(选修课)
	int grade3;				   //课程3的成绩(限选课)
	struct list *last;
	struct list *next;
}list,*lt;

//需要用到的函数
lt add(lt H);					//在末尾添加(此函数返回值是链表原来的头结点)
void check(lt H);				//查询个人
void checkall(lt H);			//查询所有
void change(lt H);				//修改
void putin(lt H);				//从中间插入
lt dele(lt H);					//删除(此函数返回值是新的头结点)
void ruin(lt H);				//销毁
void daima();					//专业代码对照表
//#######初始化信息（张三和小明）
lt start()				
{
	lt T;
//张三的基本信息
	T=(list *)malloc(sizeof(list));
	strcpy(T->brithday,"1994,12,15");
	T->grade1=80;
	T->grade2=85;
	T->grade3=95;
	T->major=10;
	strcpy(T->name,"张三");
	T->number=10;
//名单开头的last必须指向NULL
	T->last=NULL;
//下一个
	T->next=    (list *)    malloc(sizeof(list));
	T->next->last=T;
	T=T->next;
//小明的基本信息
	strcpy(T->brithday,"1995,10,03");
	T->grade1=89;
	T->grade2=88;
	T->grade3=87;
	T->major=21;
	strcpy(T->name,"小明");
	T->number=11;
//名单末尾的next必须指向NULL
	T->next=NULL;
//返回T指向的是张三
	T=T->last;
	return T;
}
//此函数用于显示菜单
void menu()
{
	system("cls");
	printf("欢迎使用学籍管理系统V1.0\n\n");
	printf("请选择操作：\n");
	printf("1、在末尾添加信息     2、在中间插入信息      3、修改信息    \n4、查询个人信息       ");
	printf("5、查询所有信息     \n6、删除一个同学       7、销毁整个名单        8、查看专业代码对照表\n");
}
int main()
{
	srand(time(NULL));
	menu();
	lt H;	H=start();		//链表头（张三）
	int c;
	while(scanf("%d",&c)||scanf("%c",&c))//如果不小心输入了字母之类的也不影响
	{
		switch (c)
		{
			case 1: H=add(H);		break;
			case 2: putin(H);		break;
			case 3: change(H);		break;
			case 4: check(H);		break;
			case 5: checkall(H);	break;
			case 6: H=dele(H);		break;
			case 7: ruin(H);H=NULL; break;
			case 8: daima();
			default :break;
		}
	}
}
//输入新加入的同学的信息
void xin(lt T)
{
	printf("请输入新加入同学的学号\n");
	scanf("%d",&T->number);
	printf("请输入新加入同学的姓名\n");
	scanf("%s",&T->name);
	printf("请输入新加入同学的生日，格式是：年，月，日\n");
	scanf("%s",&T->brithday);
	printf("请输入新加入同学的院系，详情请看专业代码对照表\n");
	scanf("%d",&T->major);
	printf("基本信息输入完毕，为减少输入环节，系统将随机生成该同学的成绩\n");
	T->grade1=50+rand()%50;
	printf("必修课成绩：%d\n",T->grade1);
	T->grade2=50+rand()%50;
	printf("选修课成绩：%d\n",T->grade2);
	T->grade3=50+rand()%50;
	printf("任选课成绩：%d\n",T->grade3);
	printf("成绩生成完毕,按任意键返回菜单\n");
	getch();
}
//在链表的末尾加入新的数据
lt add(lt T)
{
	lt Z;//记录一开始头结点的位置
	Z=T;
	if(T!=NULL)//如果名单里本来有人
	{
		while(T->next!=NULL)
		{T=T->next;}
		T->next=(list *)malloc(sizeof(list));
		T->next->last=T;
		T=T->next;
		T->next=NULL;
		//输入信息	
		xin(T);
		menu();
		return Z;
	}
	else//如果名单是空的
	{
		T=(list *)malloc(sizeof(list));
		T->next=NULL;
		T->last=NULL;
		//输入信息	
		xin(T);
		menu();
		return T;
	}
}
//输出学生信息，在查询函数中使用
void output(lt T)
{
	printf("学号：%d\n",T->number);
	printf("姓名：%s\n",T->name);
	printf("生日：%s\n",T->brithday);
	printf("院系：");
	if(T->major/10==1)
	{
		printf("通信学院，");
		switch(T->major-10)
		{
			case 0:printf("电信专业");break;
			case 1:printf("销售专业");break;
			default:printf("通信大类");
		}
		printf("\n");
	}
	else if(T->major/10==2)
	{
		printf("软件学院,");
		switch(T->major-20)
		{
			case 0:printf("电脑软件专业");break;
			case 1:printf("手机软件专业");break;
			default:printf("服务器软件专业");
		}
		printf("\n");
	}
	else
		{printf("暂无数据\n");}
	printf("必修课成绩:%d\n",T->grade1);
	printf("选修课成绩:%d\n",T->grade2);
	printf("限选课成绩:%d\n",T->grade3);
	printf("\n");
}
//查询个人信息
void check(lt T)
{
	int k;
	printf("请输入要查询的同学的学号：");
	scanf("%d",&k);
	while(T!=NULL)
	{
		if(T->number==k)
		{
			printf("\n查到信息如下:\n");
			output(T);
			printf("以上是该同学信息，按任意键返回\n");
			getch();
			menu();
			return;
		}
		else {T=T->next;}
	}
	if(T==NULL)
		printf("\n查无此人，按任意键返回菜单");
	getch();
	menu();
}
//查询所有信息
void checkall(lt T)
{
	printf("\n所有信息如下:\n");
	while(T!=NULL)
	{
		output(T);
		T=T->next;
	}
	printf("以上是所有信息，按任意键返回菜单\n");
	getch();
	menu();
}
void gai(lt T)
{
	//输入信息	
	printf("请输入改变之后的学号     ");
	scanf("%d",&T->number);
	printf("请输入改变之后的姓名     ");
	scanf("%s",&T->name);
	printf("请输入改变之后的生日     ");
	scanf("%s",&T->brithday);
	printf("请输入改变之后的院系，详情请看专业代码对照表\n");
	scanf("%d",&T->major);
	printf("请输入改变之后的必修课成绩：     ");
	scanf("%d",&T->grade1);
	printf("请输入改变之后的选修课成绩：     ");
	scanf("%d",&T->grade2);
	printf("请输入改变之后的任选课成绩：     ");
	scanf("%d",&T->grade3);
	printf("修改完成，按任意键返回\n");
	getch();
	menu();
}
//修改学生信息，先查询要修改的人的学号，再修改他的信息，修改的函数在上面
void change(lt T)
{
	int k;
	printf("请输入要修改的同学的学号：");
	scanf("%d",&k);
	while(T!=NULL)
	{
		if(T->number==k)
		{
			printf("已找到此人，可以修改他的信息\n");
			gai(T);
			return;
		}
		else {T=T->next;}
	}
	if(T==NULL)
		printf("\n查无此人，按任意键返回菜单");
	getch();
	menu();
}
//从中间插入同学的信息，调用了xin()函数
void putin(lt T)
{
	int k;
	lt F;
	printf("请输入要在后面加入新的同学的同学的学号：");
	scanf("%d",&k);
	while(T!=NULL)
	{	
		if(T->number==k)
		{
			printf("已找到插入位置，请输入插入同学的信息\n");
			if(T->next!=NULL)//如果要插入的同学后面有人
			{
				F=(list*)malloc(sizeof(list));
				F->next=T->next;
				T->next->last=F;
				F->last=T;
				T->next=F;
			}
			else if(T->next==NULL)//如果要插入的同学后面没人
			{
				F=(list*)malloc(sizeof(list));
				T->next=F;
				F->last=T;			
				F->next=NULL;
			}
			xin(F);
			menu();
			return;
		}
		else {T=T->next;}
	}
	if(T==NULL)
		printf("\n查无此人，无法添加新同学，按任意键返回菜单");
	getch();
	menu();
}
//删除一个指定的同学，在删除前调用了output()来展示该同学的信息
lt dele(lt T)
{
	int k;
	char z;
	lt N;		//在删除节点时暂时存储新的头结点的位置
	N=T;
	printf("请输入要删除的同学的学号：");
	scanf("%d",&k);
	while(T!=NULL)
	{
		if(T->number==k)
		{
			printf("已找到该同学，他的信息如下:\n");
			output(T);
			printf("是否删除他？Y/N\n");
			while(scanf("%c",&z))
			{
				if(z=='Y'||z=='y')
				{
						if(T->last!=NULL&&T->next!=NULL)//如果要删除的同学前后都有人
						{
							T->last->next=T->next;
							T->next->last=T->last;
							free(T);
						}
						else if(T->last==NULL&&T->next==NULL)//如果此时名单中只有一个人
						{
							N=NULL;
							free(T);
						}
						else if(T->last==NULL)//如果要删除的同学是名单中第一个人
						{
							T->next->last=NULL;
							N=T->next;
							free(T);
						}
						else if(T->next==NULL)//如果要删除的同学是名单中最后一个人
						{							
							T->last->next=NULL;
							free(T);
						}
					printf("该同学已删除，按任意键返回菜单\n");
					getch();
					menu();
					return N;
				}
				else if(z=='n'||z=='N')
				{
					printf("不删除该同学，按任意键返回菜单\n");
					getch();
					menu();
					return T;
				}
			}
		}
		else {T=T->next;}
	}
	if(T==NULL)
		printf("\n查无此人，按任意键返回菜单");
	getch();
	menu();
	return T;
}
//删除整个名单
void ruin(lt T)
{
	printf("确定要销毁整个名单吗？Y/N\n");
	char z;
	while(scanf("%c",&z))
	{
		if(z=='Y'||z=='y')
		{
			if(T!=NULL)//如果名单里有人
			{
				while(T->next!=NULL)
				{	
					T=T->next;
					free(T->last);
				}	
			}
			else{}//如果名单已经是空的
			printf("名单已销毁，按任意键返回菜单\n");
			getch();
			menu();
			return;
		}
		else if(z=='n'||z=='N')
		{	printf("不销毁名单，按任意键返回菜单\n");
			getch();
			menu();
			return;
		}
	}
}
//专业代码对照表(纯输出字)
void daima()
{
	printf("专业代码对照表如下：\n\n");
	printf("10----通信学院，电信专业\n");
	printf("11----通信学院，销售专业\n");
	printf("12----通信学院，通信大类\n\n");
	printf("20----软件学院，电脑软件专业\n");
	printf("21----软件学院，手机软件专业\n");
	printf("22----软件学院，服务器软件专业\n\n");
	printf("说明：如果个位数不是0或1或2，系统会将其视为2来处理\n");
	printf("      如果格式有其他不规范的情况，系统将视为暂无数据\n");
	printf("      如果出现学号重复的情况，系统在查询时将只会找到名单中最靠前的有此学号的同学\n\n");
	printf("按任意键返回菜单\n");
	getch();
	menu();
	return;
}
