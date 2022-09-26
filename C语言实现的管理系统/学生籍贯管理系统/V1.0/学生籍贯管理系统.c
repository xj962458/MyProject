#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//定义一个学生结构体
typedef struct student
{
    char no[12];            //学号
    char name[40];          //姓名
    char tele[20];          //电话号码
    int D[18];              //电话号码码
    char jg[60];            //籍贯
    char addr[80];          //通讯地址
    struct student* next;   //指向下一节点的指针
}STU;

//函数声明放在这里
STU* LIstInit(STU* L);
STU* ListCreate(STU* L, int n);
void ListInsert(STU* L);
void ListDelete(STU* L, char n[40]);
void LIstSearch(STU* L, char n[]);
void input(STU* p, int i);
void output(STU* L);
void menu();

//创建表头，初始化链表
STU* LIstInit(STU* L)
{
    STU* head = NULL;
    head = (STU*)malloc(sizeof(STU));
    head->next = NULL;
    L = head;
    return L;
}

//创建链表，将新生成的节点插入到链表的表头
STU* ListCreate(STU* L, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        STU* p;
        //将新生成的节点插入到链表中
        p = NULL;
        p = (STU*)malloc(sizeof(STU));
        input(p, i);
        p->next = L->next;
        L->next = p;
    }
    return L;
}

//对链表进行节点的插入操作
void ListInsert(STU* L)
{
    STU* s = NULL;
    //生成一个新节点s
    s = (STU*)malloc(sizeof(STU));
    printf("请输入您要插入的学生的学号:");
    scanf("%s", &s->no);
    printf("请输入您要插入的学生的姓名:");
    scanf("%s", &s->name);
    printf("请输入您要插入的学生的电话号码:");
    scanf("%s", &s->tele);
    printf("请输入您要插入的学生的身份证号码:");
    scanf("%s", &s->D);
    printf("请输入您要插入的学生的籍贯:");
    scanf("%s", &s->jg);
    printf("请输入您要插入的学生的通讯地址:");
    scanf("%s", &s->addr);
    s->next = L->next;
    L->next = s;
}

//对链表的进行节点的删除操作
void ListDelete(STU* L, char n[])
{
    STU* p = L->next, * pre = L;  //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    if (p == NULL)
        printf("数据为空，无法删除！");
    else
    {
        while (strcmp(p->name, n) != 0)
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

void LIstSearch(STU* L, char n[])
{
    STU* p = L->next;
    if (p == NULL)
        printf("数据为空，无法查找！");
    else
    {
        while (strcmp(p->name, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("该学生的籍贯为:\n");
        printf("\t%s\n", p->jg);
    }
}

void ListModify(STU* L, char na[])
{
    char JG[60];
    STU* p = L->next;
    while (p != NULL)
    {
        if (strcmp(p->name, na) == 0)
        {
            printf("请选择您修改后的学生籍贯:\n");
            scanf("%s", &JG);
            strcpy(p->jg, JG);
            break;
        }
        p = p->next;
    }
}

void input(STU* p, int i)
{
    printf("请输入第%d名学生的学号:", i + 1);
    scanf("%s", &p->no);
    printf("请输入第%d名学生的姓名:", i + 1);
    scanf("%s", &p->name);
    printf("请输入第%d名学生的电话号码:", i + 1);
    scanf("%s", &p->tele);
    printf("请输入第%d名学生的身份证号码:", i + 1);
    scanf("%s", &p->D);
    printf("请输入第%d名学生的籍贯:", i + 1);
    scanf("%s", &p->jg);
    printf("请输入第%d名学生的通讯地址:", i + 1);
    scanf("%s", &p->addr);
}

void output(STU* L)
{
    STU* p = L->next;
    while (p != NULL)
    {
        printf("%s\t", p->no);
        printf("%s\t", p->name);
        printf("\t%s", p->tele);
        printf("\t\t%s", p->D);
        printf("\t%s", p->jg);
        printf("\t%s", p->addr);
        printf("\n");
        p = p->next;
    }
}

void PrintFile(STU* L)
{
    STU* p = L->next;
    FILE* fp;
    fp = fopen("student.txt", "w");
    fprintf(fp, "学号\t\t姓名\t\t电话号码\t\t身份证号码\t\t籍贯\t\t通讯地址\n");
    while (p != NULL)
    {
        fprintf(fp, "%s\t", p->no);
        fprintf(fp, "%s\t", p->name);
        fprintf(fp, "\t%s", p->tele);
        fprintf(fp, "\t%s", p->D);
        fprintf(fp, "\t%s", p->jg);
        fprintf(fp, "\t\t%s", p->addr);
        fprintf(fp, "\n");
        p = p->next;
    }
    printf("保存成功，请到当前目录下的student.txt文件中查看");
    fclose(fp);
}

void menu()
{
    printf("\n\n");
    printf("\t\t\t===================学试报名管理系统===================\n");
    printf("\t\t\t* 作者:武新纪  班级:人工智能191  学号:3190707121      *\n");
    printf("\t\t\t*                                                   *\n");
    printf("\t\t\t*          1>. 录入学生的相关信息                    *\n");
    printf("\t\t\t*          2>. 全部学生的相关信息                    *\n");
    printf("\t\t\t*          3>. 查找某个就学生的籍贯                  *\n");
    printf("\t\t\t*          4>. 修改某个学生的籍贯                    *\n");
    printf("\t\t\t*          5>. 删除某个学生的相关信息                *\n");
    printf("\t\t\t*          6>. 插入某个学生的相关信息                *\n");
    printf("\t\t\t*          7>. 保存学生信息                         *\n");
    printf("\t\t\t*          0>. 退出管理系统                         *\n");
    printf("\t\t\t*                                    欢迎使用本系统!*\n");
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t输入选项，按回车进入选项:                             \n");
}

int main()
{
    int item, n;         //item用于接收输入的命令，n用于接收输入的学生人数
    char nam[30];
    STU* L = NULL;
    L = LIstInit(L);
    do
    {
        menu();
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        switch (item)
        {
        case 1:
            printf("请输入您要录入的学生人数:");
            scanf("%d", &n);
            L = ListCreate(L, n);
            break;
        case 2:
            printf("全部学生信息如下:\n");
            printf("学号\t\t姓名\t\t电话号码\t\t身份证号码\t\t籍贯\t\t通讯地址\n");
            output(L);
            break;
        case 3:
            printf("请输入您要查找的学生姓名:");
            scanf("%s", nam);
            LIstSearch(L, nam);
            break;
        case 4:
            printf("请输入您要修改的学生姓名:");
            scanf("%s", nam);
            ListModify(L, nam);
            break;
        case 5:
            printf("请输入您要删除的学生的姓名:");
            scanf("%s", nam);
            ListDelete(L, nam);
            break;
        case 6:
            ListInsert(L);
            break;
        case 7:
            PrintFile(L);
            break;
        case 0:
            printf("即将退出学生籍贯管理系统.....");
            exit(0);
        default:
            break;
        }
        printf("\n\n\n\n");
    } while (item);
    return 0;
}
