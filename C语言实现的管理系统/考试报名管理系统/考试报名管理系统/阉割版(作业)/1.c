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
void ListCreate(STU *L, int n);     //创建考生链表节点
void LIstSearch(STU *L);            //查找考生信息
void ListModify(STU *L);            //修改考生信息
void ListInsert(STU *L);            //插入考生信息
void ListDelete(STU *L);            //删除考生信息
void Input(STU *p,int i);           //输入考生信息
void Menu();                        //考试报名管理系统的菜单

//考生报名管理系统的主函数入口
int main()
{
    int item,n;                       //item用于接收输入的命令，n用于接收输入的考生人数      
    STU *L=NULL;                        //初始化一个头节点
    L=(STU *)malloc(sizeof(STU));       //为头节点开辟内存空间
    L->next=NULL;                       //将头节点的指针域置空4
    do
    {  
        Menu();                         //菜单
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d",&item);
        system("cls");
        switch(item)
        {
            case 1:
                printf("请输入您要录入的考生人数:");
                scanf("%d",&n);
                ListCreate(L,n);                      //创建考生链表节点
                getchar();
            	printf("\n请按任意键返回主菜单\n");
				getchar();
				system("cls");
                break;
            case 2:
                LIstSearch(L);                        //查找考生信息
                getchar();
            	printf("\n请按任意键返回主菜单\n");
				getchar();
				system("cls");
                break;                                             
            case 3:
                ListModify(L);                          //修改考生信息
                getchar();
            	printf("\n请按任意键返回主菜单\n");
				getchar();
				system("cls");
                break;
            case 4:
                ListDelete(L);                          //删除考生信息
                getchar();
                printf("\n请按任意键返回主菜单\n");
				getchar();
				system("cls");
                break;
            case 5:
                ListInsert(L);                          //插入考生信息
                getchar();
                printf("\n请按任意键返回主菜单\n");
				getchar();
				system("cls");
                break;
            case 0:                                     //退出考试报名管理系统
                printf("即将退出考生信息管理系统.....");
                exit(0);
            default:
                printf("您输入的指令不正确，请重新输入");
        }
        printf("\n\n");
    }while(item);
    return 0;
}

//创建链表，将新生成的节点插入到链表的表头
void ListCreate(STU *L, int n)
{
    int i; 
    for (i = 0; i<n; i++)
    {
        STU *p;
        //将新生成的节点插入到链表中
        p=NULL;
        p = (STU *)malloc(sizeof(STU));
        Input(p,i);
        p->next = L->next;
        L->next = p;
    }
}

//查找考生信息
void LIstSearch(STU *L)
{
    char n[40];
    STU *p=L->next;
    if (p == NULL)
        printf("数据为空，无法查找！");
    else
    {
        printf("请输入您要查找的考生姓名:");
        scanf("%s",n);
        while (strcmp(p->name, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("该考生的相关信息如下:\n");
        printf("姓名\t身份证号\t\t性别\t年龄\t电话号码\n");
        printf("%s\t",p->name);
        printf("%s",p->no);
        printf("\t%d",p->xb);
        printf("\t%d",p->age);
        printf("\t%s",p->tele);
        printf("\n");
    }
}

//修改考生信息
void ListModify(STU *L)
{
    int x,a,item;
    char nam[40],no[18],tel[20],n[40];
    STU *p=L->next;
    if (p == NULL)
        printf("数据为空，无法修改！");
    else
    {
        printf("请输入您要修改的考生姓名:");
        scanf("%s",n);
        while(strcmp(p->name, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("请选择您要修改的考生信息类型:\n");
        printf("1:姓名\t 2:身份证号\t 3:性别\t 4:年龄\t 5:电话号码\n");
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
            default:
                printf("您输入的指令不正确!\n");
        }
        printf("修改成功!");
    }
}

//删除考生信息
void ListDelete(STU *L)
{
    char n[40];
    STU *p=L->next,*pre=L;  //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    if(p==NULL)
        printf("数据为空，无法删除！");
    else
    {
        printf("请输入您要删除的考生姓名:");
        scanf("%s",n);
        while(strcmp(p->name,n)!=0)
        {
            pre=p;
            p=pre->next;
            if(p==NULL)
            {
                printf("没有找到相关信息，无法删除\n");
                return;
            }
        }
        pre->next=p->next;
        free(p);
        printf("删除成功");
    }
}

//插入考生信息
void ListInsert(STU *L)
{
    STU *s = NULL;              //生成一个新节点s
    s = (STU *)malloc(sizeof(STU));
    printf("请输入您要插入的考生的姓名:");
    scanf("%s",s->name);
    printf("请输入您要插入的考生的身份证号:");
    scanf("%s",s->no);
    printf("请输入您要插入的考生的性别（女性为0，男性为1）:");
    scanf("%d",&s->xb);
    printf("请输入您要插入的考生的年龄:");
    scanf("%d",&s->age);
    printf("请输入您要插入的考生的电话号码:");
    scanf("%s",s->tele);
    s->next = L->next;
    L->next = s;
}

//输入考生信息
void Input(STU *p,int i)
{
    printf("请输入第%d名考生的姓名:",i+1);
    scanf("%s",p->name);
    printf("请输入第%d名考生的身份证号:",i+1);
    scanf("%s",p->no);
    printf("请输入第%d名考生的性别（女性为0，男性为1）:",i+1);
    scanf("%d",&p->xb);
    printf("请输入第%d名考生的年龄:",i+1);
    scanf("%d",&p->age);
    printf("请输入第%d名考生的电话号码:",i+1);
    scanf("%s",p->tele);
}

//考生信息管理系统的菜单
void Menu()
{
    printf("\n\n");
	printf("\t\t\t===================考试报名管理系统==================\n");
	printf("\t\t\t* 作者:武新纪  班级:人工智能191  学号:3190707121    *\n");
	printf("\t\t\t*                                                   *\n");
	printf("\t\t\t*          1>. 录入考生信息                         *\n");
	printf("\t\t\t*          2>. 查找考生信息                         *\n");
	printf("\t\t\t*          3>. 修改考生信息                         *\n");
	printf("\t\t\t*          4>. 删除考生信息                         *\n");
	printf("\t\t\t*          5>. 插入考生信息                         *\n");
	printf("\t\t\t*          0>. 退出管理系统                         *\n");
	printf("\t\t\t*                                    欢迎使用本系统!*\n");
	printf("\t\t\t=====================================================\n");
	printf("\t\t\t输入选项，按回车进入选项:                             \n");
}
