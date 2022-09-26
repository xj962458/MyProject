#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct sale
{
    char no[12];            //代号
    char name[40];          //姓名
    int month[12];          //月份
    float sales[12];        //月销售额
    float total;            //年度总销售额
    struct sale *next;      //指向下一节点的指针
}SALE;

//函数声明放在这里
void ListCreate(SALE *L, int n); //创建链表节点
void LIstSearch(SALE *L);        //查找某个销售员某个月的销售额
void ListModify(SALE *L);        //修改某个销售员某个月的销售额
void ListDelete(SALE *L);        //删除某个销售员的销售信息
void Input(SALE *p, int i);      //录入销售员每个月销售额及其相关信息
void Sum(SALE *L);               //统计所有销售员的年度销售总额
void SumSale(SALE *L);           //输出所有销售员的年度销售总额
void Max(SALE *L);               //找出最大月销售额和年度总销售额
void Min(SALE *L);               //找出最大月销售额和年度总销售额
void Menu();                     //销售管理系统的菜单

//销售管理系统的主函数入口
int main()
{
    int item, n;                         //item用于接收输入的命令，n用于接收输入的销售员人数
    SALE *L = NULL;                      //初始化一个头节点
    L = (SALE *)malloc(sizeof(SALE));    //为头节点开辟内存空间
    L->next = NULL;                      //将头节点的指针域置空
    do
    {
        Menu();                         //菜单
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        system("cls");
        switch (item)
        {
        case 1:
            printf("请输入您要录入的销售员人数:");
            scanf("%d", &n);
            ListCreate(L, n); 
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 2:
            LIstSearch(L); 
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 3:
            ListModify(L);  //修改某个销售员某个月的销售额
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 4:
            ListDelete(L); //删除信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 5:
            Sum(L);
            SumSale(L);
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 6:
            Sum(L);
            Max(L);
            printf("\n");
            Min(L);
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 0: //退出销售管理系统
            printf("即将退出销售管理系统.....");
            exit(0);
        default:
            printf("您输入的指令不正确，请重新输入");
        }
        printf("\n\n");
    } while (item);
    return 0;
}

//创建链表，将新生成的节点插入到链表的表头
void ListCreate(SALE *L, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        SALE *p;
        //将新生成的节点插入到链表中
        p = NULL;
        p = (SALE *)malloc(sizeof(SALE));
        Input(p, i);
        p->next = L->next;
        L->next = p;
    }
    printf("录入成功！");
}

//查找某个销售员某个月的销售额
void LIstSearch(SALE *L)
{
    int a;
    char n[40];
    SALE *p = L->next;
    if (p == NULL)
        printf("数据为空，无法查找！");
    else
    {
        printf("请输入您要查找的销售员姓名:");
        scanf("%s", n);
        while (strcmp(p->name, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("请输入您要查找该销售员第几个月的销售额:");
        scanf("%d",&a);
        printf("销售员%s第%d月的销售额为%.2f\n",p->name,a,p->sales[a-1]);
    }
}

// 修改某个销售员某个月的销售额
void ListModify(SALE *L)
{
    int a;
    char nam[40];
    SALE *p = L->next;
    if (p == NULL)
        printf("数据为空，无法修改！");
    else
    {
        printf("请输入您修改的销售员姓名:");
        scanf("%s",nam);
        while(strcmp(p->name, nam) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("请输入您修改该销售员第几个月的销售额:");
        scanf("%d",&a);
        printf("请输入您修改后的第%d月的销售额:",a);
        scanf("%f",&p->sales[a-1]);
        printf("修改成功");
    }
}

//删除销售员销售信息
void ListDelete(SALE *L)
{
    char n[40];
    SALE *p = L->next, *pre = L; //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    if (p == NULL)
        printf("数据为空，无法删除！");
    else
    {
        printf("请输入您要删除的销售员姓名:");
        scanf("%s", n);
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

//统计所有销售员的年度总销售额
void Sum(SALE *L)
{
    int i;
    SALE *p=L->next;
    while(p!=NULL)
    {
        p->total=0;
        for(i=0;i<12;i++)
            p->total+=p->sales[i];
        p=p->next;
    }
}

//输出所有销售员的年度总销售额
void SumSale(SALE *L)
{
    SALE *p=L->next;
    printf("\n代号\t\t姓名\t\t年度总销售额\n");
    while(p!=NULL)
    {
        printf("\n%s\t\t%s\t\t%.2f",p->no,p->name,p->total);
        p=p->next;  
    }
}

//找出最大月销售额和年度总销售额
void Max(SALE *L)
{
    int i;
    float m=0,y=0;      //m用于表示月销售额,y用于表示年销售额
    SALE *p=L->next;
    while(p!=NULL)
    {
        for(i=0;i<12;i++)
        {
            if(p->sales[i]>m)
                m=p->sales[i];
        }
        if(p->total>y)
            y=p->total;
        p=p->next;
    }
    printf("最大月销售额为%.2f元\n",m);
    printf("最大年销售额为%.2f元\n",y);
}

//找出最小月销售额和年度总销售额
void Min(SALE *L)
{
    int i;
    float m,y;      //m用于表示月销售额,y用于表示年销售额
    SALE *p=L->next;
    m=p->sales[0];
    y=p->total;
    while(p!=NULL)
    {
        for(i=1;i<12;i++)
        {
            if(p->sales[i]<m)
                m=p->sales[i];
        }   
        if(p->total<y)
            y=p->total;
        p=p->next;
    }
    printf("最小月销售额为%.2f元\n",m);
    printf("最小年销售额为%.2f元\n",y);
}

//输入销售员每个月的销售额的相关信息
void Input(SALE *p, int i)
{
    int j;
    printf("请输入第%d个销售员代号:", i + 1);
    scanf("%s", p->no);
    printf("请输入第%d个销售员的姓名:", i + 1);
    scanf("%s", p->name);
    printf("请输入第%d名销售员12个月的的销售额(用空格隔开):", i + 1);
    for (j = 0; j < 12; j++)
    {
        scanf("%f", &p->sales[j]); //输入每个月的销售额
    }
}

//销售管理系统的菜单
void Menu()
{
    printf("\n\n");
    printf("\t\t\t======================销售管理系统==========================\n");
    printf("\t\t\t* 作者:XXX  班级:人工智能191  学号:XXXXXXXXXX              *\n");
    printf("\t\t\t*                                                          *\n");
    printf("\t\t\t*          1>. 录入销售员每个月销售额及其相关信息          *\n");
    printf("\t\t\t*          2>. 查找某个销售员某个月的销售额                *\n");
    printf("\t\t\t*          3>. 修改某个销售员某个月的销售额                *\n");
    printf("\t\t\t*          4>. 删除某个销售员的销售信息                    *\n");
    printf("\t\t\t*          5>. 统计所有销售员的销售信息                    *\n");
    printf("\t\t\t*          6>. 找出最大（或最小）月销售额和年度总销售额    *\n");
    printf("\t\t\t*          0>. 退出管理系统                                *\n");
    printf("\t\t\t*                                       欢迎使用本系统!    *\n");
    printf("\t\t\t===========================================================\n");
    printf("\t\t\t输入选项，按回车进入选项:                                   \n");
}