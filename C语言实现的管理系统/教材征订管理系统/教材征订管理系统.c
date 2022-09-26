struct node
{
    char no[12];            //书号
    char name[40];          //书名
    char author[40];        //作者
    char publisher[40];     //出版社
    int number;             //数量
    float price;            //单价
    float total;            //金额
    struct node *next;      //指向下一节点的指针
};