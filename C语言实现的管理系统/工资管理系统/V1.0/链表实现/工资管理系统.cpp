#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct worker
{
    char no[12];         //职工工号
    char name[40];       //姓名
    int month[12];       //月份
    float gz[12];        //月工资
    float total;         //年度总工资
    struct worker *next; //指向下一节点的指针
} Worker;

//相关的函数声明
Worker *InitList(Worker *L);                        //初始化链表，用于创造头节点
Worker *CreateList(Worker *L);                      //根据输入的职工人数，批量创建节点
void DeleteList(Worker *L, char n[]);               //删除节点
void LIstSearch(Worker *L, char n[]);               //查找职工工资信息
void InsertInfo(Worker *L);                         //插入职工工资信息
void SearchMonthSalary(Worker *L, char n[], int m); //查找某个职工的某个月的工资
void input(Worker *p, int i);                       //为节点的数据域赋值
void output(Worker *L);                             //输出整个链表的数据
void Modify(Worker *L, char n[], int m[]);          //修改某个职工的工资
void menu();                                        //工资管理系统的菜单
void Save(Worker *L);                               //将职工的工资信息保存至文件

//初始化链表，用于创造头节点
Worker *InitList(Worker *L)
{
    Worker *head = NULL;
    head = (Worker *)malloc(sizeof(Worker));
    head->next = NULL;
    L = head;
    return L;
}

//根据输入的职工人数，批量创建节点
Worker *CreateList(Worker *L, int n) //n为输入的职工人数
{
    int i;
    for (i = 0; i < n; i++)
    {
        Worker *p;
        //将新生成的节点插入到链表中
        p = NULL;
        p = (Worker *)malloc(sizeof(Worker));
        input(p, i); //为节点的数据域赋值
        p->next = L->next;
        L->next = p;
    }
    return L;
}

void DeleteList(Worker *L, char n[]) //按姓名删除职工信息
{
    int i;
    Worker *p = L->next, *pre = L; //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
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

//向链表中插入职工工资信息
void InsertInfo(Worker *L)
{
    int j, k;
    Worker *p = NULL;
    p = (Worker *)malloc(sizeof(Worker)); //生成一个新节点p
    p->total = 0;
    printf("请输入要插入的职工的职工工号:");
    scanf("%s", &p->no);
    printf("请输入要插入的职工的姓名:");
    scanf("%s", &p->name);
    for (k = 0, j = 1; j <= 12, k < 12; j++, k++)
        p->month[k] = j;
    printf("请输入要插入的职工的月工资(用空格隔开):");
    for (j = 0; j < 12; j++)
    {
        scanf("%f", &p->gz[j]); //输入每个月的工资
        p->total += p->gz[j];   //计算总工资
    }
    p->next = L->next;
    L->next = p;
    printf("插入成功!");
}

void LIstSearch(Worker *L, char n[])
{
    int i;
    Worker *p = L->next;
    while (p != NULL)
    {
        if (strcmp(p->name, n) == 0)
        {
            printf("\n该职工的工资的信息如下:\n");
            printf("职工编号:");
            printf("%s\t\n", p->no);
            printf("姓名:");
            printf("%s\n", p->name);
            printf("该职工12个月的月工资如下:");
            for (i = 0; i < 12; i++)
                printf("%.2f ", p->gz[i]);
            printf("\n该职工的年度总工资为:");
            printf("%.2f", p->total);
            printf("\n\n");
            printf("\n");
            p = p->next;
        }
        else
            p = p->next;
    }
}

void SearchMonthSalary(Worker *L, char n[], int m)
{
    int i;
    Worker *p = L->next;
    while (p != NULL)
    {
        if (strcmp(p->name, n) == 0)
        {
            switch (m)
            {
            case 1:
                printf("该职工%d月的工资为%.2f", p->month[0], p->gz[0]);
                break;
            case 2:
                printf("该职工%d月的工资为%.2f", p->month[1], p->gz[1]);
                break;
            case 3:
                printf("该职工%d月的工资为%.2f", p->month[2], p->gz[2]);
                break;
            case 4:
                printf("该职工%d月的工资为%.2f", p->month[3], p->gz[3]);
                break;
            case 5:
                printf("该职工%d月的工资为%.2f", p->month[4], p->gz[4]);
                break;
            case 6:
                printf("该职工%d月的工资为%.2f", p->month[5], p->gz[5]);
                break;
            case 7:
                printf("该职工%d月的工资为%.2f", p->month[6], p->gz[6]);
                break;
            case 8:
                printf("该职工%d月的工资为%.2f", p->month[7], p->gz[7]);
                break;
            case 9:
                printf("该职工%d月的工资为%.2f", p->month[8], p->gz[8]);
                break;
            case 10:
                printf("该职工%d月的工资为%.2f", p->month[9], p->gz[9]);
                break;
            case 11:
                printf("该职工%d月的工资为%.2f", p->month[10], p->gz[10]);
                break;
            case 12:
                printf("该职工%d月的工资为%.2f", p->month[11], p->gz[11]);
                break;
            default:
                break;
            }
            p = p->next;
        }
        else
            p = p->next;
    }
}

void Modify(Worker *L, char n[], int m, float s)
{
    int i;
    Worker *p = L->next;
    while (p != NULL)
    {
        if (strcmp(p->name, n) == 0)
        {
            switch (m)
            {
            case 1:
                p->gz[0] = s;
                break;
            case 2:
                p->gz[1] = s;
                break;
            case 3:
                p->gz[2] = s;
                break;
            case 4:
                p->gz[3] = s;
                break;
            case 5:
                p->gz[4] = s;
                break;
            case 6:
                p->gz[5] = s;
                break;
            case 7:
                p->gz[6] = s;
                break;
            case 8:
                p->gz[7] = s;
                break;
            case 9:
                p->gz[8] = s;
                break;
            case 10:
                p->gz[9] = s;
                break;
            case 11:
                p->gz[10] = s;
                break;
            case 12:
                p->gz[11] = s;
                break;
            default:
                break;
            }
            p = p->next;
        }
        else
            p = p->next;
    }
    printf("修改成功!");
}
void input(Worker *p, int i)
{
    int j, k;
    p->total = 0;
    printf("请输入第%d名职工的职工工号:", i + 1);
    scanf("%s", &p->no);
    printf("请输入第%d名职工的姓名:", i + 1);
    scanf("%s", &p->name);
    for (k = 0, j = 1; j <= 12, k < 12; j++, k++)
        p->month[k] = j;
    printf("请输入第%d名职工的月工资(用空格隔开):", i + 1);
    for (j = 0; j < 12; j++)
    {
        scanf("%f", &p->gz[j]); //输入每个月的工资
        p->total += p->gz[j];   //计算总工资
    }
}

void output(Worker *L)
{
    int i;
    Worker *p = L->next;
    while (p != NULL)
    {
        printf("职工编号:");
        printf("%s\t\n", p->no);
        printf("姓名:");
        printf("%s\n", p->name);
        printf("该职工12个月的月工资如下:");
        for (i = 0; i < 12; i++)
            printf("%.2f ", p->gz[i]);
        printf("\n该职工的年度总工资为:");
        printf("%.2f", p->total);
        printf("\n\n");
        p = p->next;
    }
}

void Save(Worker *L)
{
    int i;
    Worker *p = L->next;
    FILE *fp = fopen("WorkerSalaryInfo.txt", "w");
    while (p != NULL)
    {
        fprintf(fp, "职工编号:");
        fprintf(fp, "%s\t\n", p->no);
        fprintf(fp, "姓名:");
        fprintf(fp, "%s\n", p->name);
        fprintf(fp, "该职工12个月的月工资如下:");
        for (i = 0; i < 12; i++)
            fprintf(fp, "%.2f ", p->gz[i]);
        fprintf(fp, "\n该职工的年度总工资为:");
        fprintf(fp, "%.2f", p->total);
        fprintf(fp, "\n\n");
        p = p->next;
    }
    fclose(fp);
    printf("保存成功，已保存至当前目录下的‘WorkerSalaryInfo.txt’文件中");
}

void menu()
{
    printf("▔▔▔▔▔▔欢迎进入工资管理系统▔▔▔▔▔▔\n");
    printf(" 1.录入职工每个月的工资信息                \n");
    printf(" 2.查找某个员工各月的工资                  \n");
    printf(" 3.查找某个职工的某个月的工资              \n");
    printf(" 4.修改某个职工某个月的工资                \n");
    printf(" 5.删除某个职工的相关信息                  \n");
    printf(" 6.插入职工工资信息                        \n");
    printf(" 7.统计某个职工年度总工资                  \n");
    printf(" 8.对职工的月工资或年工资进行排名           \n");
    printf(" 9.输出所有职工工资信息                    \n");
    printf(" 10、将所有职工的工资信息保存至文件         \n");
    printf(" 0.退出                                   \n");
    printf("-▁▁▁▁▁▁▁▁▁谢谢使用▁▁▁▁▁▁▁▁▁\n");
}

int main()
{
    int item, n, m; //item用于接收输入的命令，n用于接收输入的职工人数
    float s;
    char nam[10];
    Worker *L = NULL;
    L = InitList(L);
    do
    {
        menu();
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        switch (item)
        {
        case 1:
            printf("请输入您要录入的职工人数:");
            scanf("%d", &n);
            L = CreateList(L, n);
            break;
        case 2:
            printf("请输入您要查找的职工姓名:");
            scanf("%s", &nam);
            LIstSearch(L, nam);
            break;
        case 3:
            printf("请输入您要查找的职工的姓名:");
            scanf("%s", &nam);
            printf("请输入您要查找该职工第几个月的工资(1到12):");
            scanf("%d", &m);
            SearchMonthSalary(L, nam, m);
            break;
        case 4:
            printf("请输入您要修改的职工姓名:");
            scanf("%s", &nam);
            printf("\n请输入您要修改的月份:");
            scanf("%d", &m);
            printf("\n请输入您修改后的数据:");
            scanf("%f", &s);
            Modify(L, nam, m, s);
            break;
        case 5:
            printf("请输入您要删除的职工姓名:");
            scanf("%s", &nam);
            DeleteList(L, nam);
            break;
        case 6:
            InsertInfo(L);
            break;
        case 7:
            printf("功能完善中!");
            break;
        case 8:
            printf("功能完善中!");
            break;
        case 9:
            printf("全部职工的信息如下:\n\n");
            output(L);
            break;
        case 10:
            Save(L);
            break;
        case 0:
            printf("谢谢您使用工资管理系统，即将退出工资管理系统.....");
            exit(0);
            break;
        }
        printf("\n\n\n\n");
    } while (item);
    return 0;
}
