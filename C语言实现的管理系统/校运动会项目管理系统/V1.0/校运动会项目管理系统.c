#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//定义一个结构体
typedef struct project
{
    char xiangmu[40];               //比赛项目名称
    char name[10][40];              //学院名称
    float score[10];                //单项成绩
    int no[10];                     //单项名次
    struct project* next;           //指向下一节点的指针
}Proj;

//函数声明放在这里
void ListCreate(Proj* L, int n);     //创建链表节点
void LIstSearch(Proj* L);            //查找某个运动会项目信息
void ListModify(Proj* L);            //修改某个运动会项目信息
void ListDelete(Proj* L);            //删除某个运动会项目信息 
void Input(Proj* p, int i);          //输入运动会项目信息
void Menu();                        //校运动会项目管理系统的菜单

//考生报名管理系统的主函数入口
int main()
{
    int item, n;                           //item用于接收输入的命令，n用于接收输入的项目数      
    Proj* L = NULL;                        //初始化一个头节点
    L = (Proj*)malloc(sizeof(Proj));       //为头节点开辟内存空间
    L->next = NULL;                        //将头节点的指针域置空
    do
    {
        Menu();                         //菜单
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        system("cls");
        switch (item)
        {
        case 1:
            printf("请输入您要录入的项目数目:");
            scanf("%d", &n);
            ListCreate(L, n);                      //创建项目链表节点
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 2:
            LIstSearch(L);                        //查找项目的相关信息
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
            ListDelete(L);                          //删除项目的相关信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 5:
            printf("功能完善中!");
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 6:
            printf("功能完善中!");
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 0:                                     //退出校运动会项目管理系统
            printf("即将退出校运动会项目管理系统.....");
            exit(0);
        default:
            printf("您输入的指令不正确，请重新输入");
        }
        printf("\n\n");
    } while (item);
    return 0;
}

//创建链表，将新生成的节点插入到链表的表头
void ListCreate(Proj* L, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        Proj* p;
        //将新生成的节点插入到链表中
        p = NULL;
        p = (Proj*)malloc(sizeof(Proj));
        Input(p, i);
        p->next = L->next;
        L->next = p;
    }
}

//查找项目信息
void LIstSearch(Proj* L)
{
    int k;
    char n[40];
    Proj* p = L->next;
    if (p == NULL)
        printf("数据为空，无法查找！");
    else
    {
        printf("请输入您要查找的项目名称:");
        scanf("%s", n);
        while (strcmp(p->xiangmu, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("该项目的相关信息如下:\n");
        printf("学院名称\t单项成绩\t单项名次\n\n");
        for (k = 0; k < 10; k++)
        {
            printf("%s\t\t", *((p->name)+k));
            printf("%.2f\t\t", *((p->score)+k));
            printf("%d\t", *((p->no)+k));
            printf("\n");
        }
    }
}

//修改项目的相关信息
void ListModify(Proj* L)
{
    int item,k;
    char n[40], m[40];
    Proj* p = L->next;
    if (p == NULL)
        printf("数据为空，无法修改！");
    else
    {
        printf("请输入您要修改的项目名称:");
        scanf("%s", n);
        while (strcmp(p->xiangmu,n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("请选择您要修改的学院名称:\n");
        scanf("%s", m);
        for (k = 0; k < 10; k++)
        {
            if (strcmp(p->name[k], n) == 0)
            {
                printf("请输入你要修改的项目信息类型:\n");
                printf("1、学院名称\n2、该学院该项目的成绩\n3、该学院该项目的名次\n");
                scanf("%d", &item);
                switch(item)
                {
                case 1:
                    printf("请输入修改后的学院名称:");
                    scanf("%s", m);
                    strcpy(p->name[k], m);
                    break;
                case 2:
                    printf("请输入您修改后的该学院该项目的成绩:");
                    scanf("%f", p->score);
                    break;
                case 3:
                    printf("请输入您修改后的该学院该项目的名次:");
                    scanf("%d", p->no);
                default:
                    printf("您输入的指令错误!");
                }
            }
        }
    }
}

//删除项目的相关信息
void ListDelete(Proj* L)
{
    char n[40];
    Proj* p = L->next, * pre = L;  //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    if (p == NULL)
        printf("数据为空，无法删除！");
    else
    {
        printf("请输入您要删除的项目名称:");
        scanf("%s", n);
        while (strcmp(p->xiangmu, n) != 0)
        {
            pre = p;
            p = pre->next;
            if (p == NULL)
            {
                printf("没有找到相关信息，无法删除\n");
                return;
            }
        }
        pre->next = p->next;
        free(p);
        printf("删除成功");
    }
}

//输入项目的相关信息
void Input(Proj* p, int i)
{
    int j;
    printf("请输入第%d个比赛项目名称:", i + 1);
    scanf("%s", p->xiangmu);
    for (j = 0; j < 10; j++)
    {
        printf("请输入第%d个学院的名称:", j + 1);
        scanf("%s", (p->name)+j);
        printf("请输入该学院的该项目的成绩:");
        scanf("%f", (p->score)+j);
        printf("请输入该学院的该项目的名次:");
        scanf("%d", (p->no)+j);
    }
}

//校运动会项目管理系统的菜单
void Menu()
{
    printf("\n\n");
    printf("\t\t\t===================校运动会项目管理系统==================\n");
    printf("\t\t\t* 作者:XXX  班级:人工智能191  学号:XXXXXXXXX            *\n");
    printf("\t\t\t*                                                       *\n");
    printf("\t\t\t*          1>. 录入运动会项目信息                       *\n");
    printf("\t\t\t*          2>. 查找某个运动会项目信息                   *\n");
    printf("\t\t\t*          3>. 修改某个运动会项目信息                   *\n");
    printf("\t\t\t*          4>. 删除某个运动会醒目信息                   *\n");
    printf("\t\t\t*          5>. 每个运动会项目的学院成绩排名             *\n");
    printf("\t\t\t*          6>. 所有项目每个学院的总成绩和排名           *\n");
    printf("\t\t\t*          0>. 退出管理系统                             *\n");
    printf("\t\t\t*                                        欢迎使用本系统!*\n");
    printf("\t\t\t=========================================================\n");
    printf("\t\t\t输入选项，按回车进入选项:                                \n");
}
