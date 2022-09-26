#include<stdio.h>
struct node
{
    char no[12];            //教师工号
    char name[40];          //姓名
    int term[2];            //学期
    float workload[2];      //工作量
    float total;            //年度总工作量
    struct node *next;      //指向下一节点的指针
};