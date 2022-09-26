#include<stdio.h>
struct node
{
    char name[40];          //姓名
    char tele[20];          //电话号码
    char ID[18];            //身份证号码
    char unit[60];          //单位
    char no[16];            //房间号
    struct node *next;      //指向下一节点的指针
};