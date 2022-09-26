#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//定义一个考生结构体
typedef struct student
{
    char name[40];
    char no[18];
    int xb;
    int age;
    char tele[20];
    struct student *next;
}STU;

//函数声明放在这里
STU *LIstInit(STU *L);
STU *ListCreate(STU *L, int n);
void ListInsert(STU *L);
void ListDelete(STU *L,char n[40]);
void LIstSearch(STU *L,char n[]);
void input(STU *p,int i);
void output(STU *L);
void menu();

//创建表头，初始化链表
STU *LIstInit(STU *L)
{
    STU *head=NULL;
    head=(STU *)malloc(sizeof(STU));
    head->next=NULL;
    L = head;
    return L;
}

//创建链表，将新生成的节点插入到链表的表头
STU *ListCreate(STU *L, int n)
{
    int i; 
    for (i = 0; i<n; i++)
    {
        STU *p;
        //将新生成的节点插入到链表中
        p=NULL;
        p = (STU *)malloc(sizeof(STU));
        input(p,i);
        p->next = L->next;
        L->next = p;
    }
    return L;
}

//对链表进行节点的插入操作
void ListInsert(STU *L)
{
    STU *s = NULL;
    //生成一个新节点s
    s = (STU *)malloc(sizeof(STU));
    printf("请输入您要插入的考生的姓名:");
    scanf("%s",&s->name);
    printf("请输入您要插入的考生的身份证号:");
    scanf("%s",&s->no);
    printf("请输入您要插入的考生的性别（女性为0，男性为1）:");
    scanf("%d",&s->xb);
    printf("请输入您要插入的考生的年龄:");
    scanf("%d",&s->age);
    printf("请输入您要插入的考生的电话号码:");
    scanf("%s",&s->tele);
    s->next = L->next;
    L->next = s;
}

//对链表的进行节点的删除操作
void ListDelete(STU *L,char n[])
{
    int i;
    STU *p=L->next,*pre=L;  //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    while(p!=NULL)      //若未到链表结尾，就一直遍历下去
    {                       
        if(strcmp(p->name,n)==0)      //若节点的姓名和要删除的节点一样，则删除该节点，并接着遍历
        {
            pre->next=p->next;
            free(p);
            printf("删除成功！");
            p=pre->next;
        }
        else               //若节点的姓名不满足要删除的节点的姓名，则p，和pre接着遍历，直到链表尾
        {
            pre=p;
            p=p->next;
        }
    }
}

void LIstSearch(STU *L,char n[])
{
    STU *p=L->next;
    while(p!=NULL)
    {
        if(strcmp(p->name,n)==0)
        {
            printf("该考生的信息如下:\n");
            printf("%s\t",p->name);
            printf("\t%s",p->no);
            printf("\t%d",p->xb);
            printf("\t%d",p->age);
            printf("\t%s",p->tele);
            printf("\n");
            p=p->next;
        }
        else
            p=p->next;
    }
}

void ListModify(STU *L,char na[])
{
    int x,a,item;
    char nam[40],no[18],tel[20];
    STU *p=L->next;
    while(p!=NULL)
    {
        if(strcmp(p->name,na)==0)
        {
            printf("请选择您要修改的考生信息类型:\n");
            printf("1、姓名\n2、身份证号\n3、性别\n4、年龄\n5、电话号码\n");
            scanf("%d",&item);
            switch(item)
            {
                case 1:
                    printf("请输入您修改后的姓名:");
                    scanf("%s",nam);
                    strcpy(p->name,nam);
                    break;
                case 2:
                    printf("请输入您修改后的身份证号:");
                    scanf("%s",no);
                    strcpy(p->no,no);
                    break;
                case 3:
                    printf("请输入您修改后的性别:");
                    scanf("%d",&x);
                    p->xb=x;
                    break;
                case 4:
                    printf("请输入您修改后的年龄:");
                    scanf("%d",&a);
                    p->age=a;
                    break;
                case 5:
                    printf("请输入您修改后的电话号码:");
                    scanf("%s",tel);
                    strcpy(p->tele,tel);
                    break;
            }
        }
        p=p->next;
    }
}

void input(STU *p,int i)
{
    printf("请输入第%d名考生的姓名:",i+1);
    scanf("%s",&p->name);
    printf("请输入第%d名考生的身份证号:",i+1);
    scanf("%s",&p->no);
    printf("请输入第%d名考生的性别（女性为0，男性为1）:",i+1);
    scanf("%d",&p->xb);
    printf("请输入第%d名考生的年龄:",i+1);
    scanf("%d",&p->age);
    printf("请输入第%d名考生的电话号码:",i+1);
    scanf("%s",&p->tele);
}

void output(STU *L)
{
    STU *p=L->next;
    while(p!=NULL)
    {
        printf("%s\t",p->name);
        printf("\t%s",p->no);
        printf("\t%d",p->xb);
        printf("\t%d",p->age);
        printf("\t%s",p->tele);
        printf("\n");
        p=p->next;
    }
}

void menu()
{
    printf("\n\n\n\n");
	printf("\t\t\t===================学生成绩管理系统==================\n");
	printf("\t\t\t* 作者:武新纪  班级:人工智能191  学号:3190707121    *\n");
	printf("\t\t\t*                                                   *\n");
	printf("\t\t\t*          1>. 录入考生信息                         *\n");
	printf("\t\t\t*          2>. 全部考生信息                         *\n");
	printf("\t\t\t*          3>. 查看考生信息                         *\n");
	printf("\t\t\t*          4>. 修改考生信息                         *\n");
	printf("\t\t\t*          5>. 删除考生信息                         *\n");
	printf("\t\t\t*          6>. 插入考生信息                         *\n");
	printf("\t\t\t*          7>. 读取学生信息                         *\n");
	printf("\t\t\t*          8>. 保存学生信息                         *\n");
	printf("\t\t\t*          0>. 退出管理系统                         *\n");
	printf("\t\t\t*                                    欢迎使用本系统!*\n");
	printf("\t\t\t=====================================================\n");
	printf("\t\t\t输入选项，按回车进入选项:                             \n");
}

int main()
{
    int item,n,m;         //item用于接收输入的命令，n用于接收输入的考生人数
    char nam[30];         
    STU *L=NULL;
    L=LIstInit(L);
    do
    { 
        menu();
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d",&item);
        switch(item)
        {
            case 1:
                printf("请输入您要录入的考生数目:");
                scanf("%d",&n);
                L=ListCreate(L,n);
                break;
            case 2:
                printf("全部考生信息如下:\n");
                printf("姓名\t\t身份证号\t\t性别\t年龄\t电话号码\n");
                output(L);
                break;
            case 3:
                printf("请输入您要查找的考生姓名:");
                scanf("%s",nam);
                LIstSearch(L,nam);
                break;                                             
            case 4:
                printf("请输入您要修改的学生姓名:");
                scanf("%s",nam);
                ListModify(L,nam);
                break;
            case 5:
                printf("请输入您要删除的学生的姓名:");
                scanf("%s",nam);
                ListDelete(L,nam);
                break;
            case 6:
                ListInsert(L);
                break;
            case 0:
                printf("即将退出考生信息管理系统.....");
                exit(0);
        }
    }while(item);
    return 0;
}
