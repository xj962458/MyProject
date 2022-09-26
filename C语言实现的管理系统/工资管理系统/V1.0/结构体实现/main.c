//main.c
#pragma once
#include "preProcess.h"
int saveflag = 0; /*需要存盘的标志变量*/
int main()
{

    ZGGZ gz[N]; /*定义ZGGZ结构体*/
    FILE *fp;
    int select;    /*保存选择结果变量*/
    char ch;       /**/
    int count = 0; /*定义保存记录数*/

    void menu(); /*主菜单界面*/
    void printheader();
    void PRINTdata(ZGGZ pp);
    void disp(ZGGZ tp[], int n);
    void wrong();
    void nofind();
    void stringinput(char *t, int lens, char *notice); /*输入字符串，并进行长度验证明，长度必须小于lens，*/
    float numberinput(char *notice);                   /*输入数值浮点数，对数值检验后返回该值，数值必须大于等于0*/
    void save(ZGGZ tp[], int n);                       /*存储记录*/
    int add(ZGGZ tp[], int n);                         /*增加记录*/
    int insert(ZGGZ tp[], int n);                      /*插入记录*/

    fp = fopen("E:\zggz\gzgl.data", "ab+"); /*追加方式打开二进制文件，可读/写。此文件若不存在则新建*/
    if (fp == NULL)
    {
        /* code */
        printf("\n Can not open file!\n");
        exit(0);
    }
    while (!feof(fp))
    {
        if (fread(&gz[count], sizeof(ZGGZ), 1, fp) == 1)
            count++;
    }
    fclose(fp);
    printf("\n==>open file success,the total records number is:%d.\n", count);
    getchar();

    //system("pause");
    menu();
    while (1)
    {
        system("cls");
        menu(); //调用主菜单
        printf("\n 	Please Enter your choice(0~9):");
        scanf("%d", &select);
        if (select == 0)
        {
            /* code */
            if (saveflag == 1) /*若对数组中数据修改过且未存盘，则此标志为1*/
            {
                /* code */
                getchar();
                printf("\n==>Whether save the modified records to file?(y/n)");
                scanf("%c", &ch);
                if (ch == 'y' || ch == 'Y')
                {
                    save(gz, count);
                    /* code */
                }
            }
            printf("\n===>Thank you for useness!\n");
            getchar();
            break;
        }
        switch (select)
        {
        case 1:
            count = add(gz, count);
            break; /*增加记录*/
        //case 2:count=del(gz,count);break;			/*删除记录*/
        //case 3:qur(gz,count);break;					/*查询记录*/
        //case 4:modify(gz,count);break;				/*修改记录*/
        case 5:
            count = insert(gz, count);
            break; /*插入记录*/

        default:
            wrong();
            getchar();
            break; /*按键有误，或功能还未实现*/
        }
    }
    system("pause");
    return 0;
}
