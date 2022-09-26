//preProcess.h
/*
*源文件编译预处理命令，包括加载头文件，定义结构体、常量和变量，并对它们进行初始化
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define HEADER1 "----------------------GongZi--------------------------------------------------\n"
#define HEADER2 "|number|	name	|	jbgz	|	jj	|	kk	|	yfgz	|	sk	|	sfgz	|\n"
#define HEADER3 "|------|-----------|-----------|-------|-------|-----------|-------|-----------|\n"
#define FORMAT "|%-5s|%-10s|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|\n"
#define DATA p->num, p->name, p->jbgz, p->jj, p->kk, p->yfgz, p->sk, p->sfgz
#define END "------------------------------------------------------------------------------\n"
#define N 60

//事实上，这个saveflag全局变量虽然是全局使用，但不应放在预编译中
//int saveflag=0;				/*需要存盘的标志变量*/

/*定义员工数据结构，各成员名在数据库中也称为字段*/
typedef struct employee
{
    /* data */
    char num[10];  /*员工编号*/
    char name[15]; /*员工姓名*/
    float jbgz;    /*基本工资*/
    float jj;      /*奖金*/
    float kk;      /*扣款*/
    float yfgz;    /*应发工资*/
    float sk;      /*税款*/
    float sfgz;    /*实发工资*/
} ZGGZ;
