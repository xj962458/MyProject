#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// 定义图书信息结点
typedef struct node
{
    string no;         //编号
    string bookname;   //书名
    string author;     //作者
    string publishers; //出版社
    int time;          //被借阅次数
    struct node *next; //指向下一节点的指针
} Node;

// 录入图书信息（尾插法建立）
void CreateNode(Node *&L)
{
    int n;
    L = new Node;
    L->next = NULL;
    Node *p, *tail = L;
    cout << "请输入您要输入的图书本书:";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p = new Node;
        p->next = tail->next;
        tail->next = p;
        cout << "请输入第" << i + 1 << "本图书的编号、名称、作者、出版社和借阅次数(用空格隔开):\n";
        cin >> p->no >> p->bookname >> p->author >> p->publishers >> p->time;
        tail = p;
    }
}

// 删除图书信息
void Del(Node *&L)
{
    Node *p = L->next, *q = L;
    string name;
    if (p == NULL)
    {
        cout << "数据为空，无法删除";
        return;
    }
    cout << "请输入您要删除的书名:";
    cin >> name;
    while (p != NULL)
    {
        if (p->bookname == name)
        {
            q->next = p->next;
            delete p;
            cout << "删除成功!" << endl;
            return;
        }
        p = p->next;
        q = q->next;
    }
    if (p == NULL && p->bookname == name)
        cout << "未找到相关信息";
}

// 插入图书信息（尾插法插入）
void Insert(Node *&L)
{
    Node *p, *tail = L->next;
    while (tail->next != NULL)
        tail = tail->next;
    p = new Node;
    p->next = tail->next;
    tail->next = p;
    cout << "请输入图书的编号、名称、作者、出版社和借阅次数(用空格隔开):\n";
    cin >> p->no >> p->bookname >> p->author >> p->publishers >> p->time;
    cout << "插入成功!\n";
}

// 查找图书借阅次数（根据书名查找）
void FindTime(Node *L)
{
    Node *p = L->next;
    string name;
    if (p == NULL)
    {
        cout << "数据为空，无法查找。\n";
        return;
    }
    cout << "请输入您要查找的图书名称:";
    cin >> name;
    while (p != NULL)
    {
        if (p->bookname == name)
        {
            cout << "图书《" << p->bookname << "》的借阅次数为" << p->time << endl;
            return;
        }
        p = p->next;
    }
    if (p == NULL && p->bookname != name)
        cout << "未找到相关信息\n";
}

// 修改图书借阅次数（根绝书名查找修改)
void ChangeTime(Node *L)
{
    Node *p = L->next;
    string name;
    if (p == NULL)
    {
        cout << "数据为空，无法查找。\n";
        return;
    }
    cout << "请输入您要查找的图书名称\n";
    cin >> name;
    while (p != NULL)
    {
        if (p->bookname == name)
        {
            cout << p->bookname << "的当前借阅次数为" << p->time << endl;
            cout << "请输入您要修改后的借阅次数:";
            cin >> p->time;
            cout << "修改成功。当前图书《" << p->bookname << "》的借阅次数为" << p->time << endl;
            return;
        }
        p = p->next;
    }
    if (p == NULL && p->bookname != name)
        cout << "未找到相关信息\n";
}

// 寻找最大和最小的图书借阅次数
void FindMost(Node *L)
{
    Node *p = L->next;
    int max, min;
    string maxname = p->bookname, minname = p->bookname;
    max = p->time;
    min = p->time;
    while (p != NULL)
    {
        if (p->time > max)
        {
            max = p->time;
            maxname = p->bookname;
        }
        if (p->time < min)
        {
            min = p->time;
            minname = p->bookname;
        }
        p = p->next;
    }
    cout << "借阅次数最多的图书是《" << maxname << "》,借阅次数为:" << max << "次" << endl;
    cout << "借阅次数最少的图书是《" << minname << "》,借阅次数为:" << min << "次" << endl;
}

// 程序菜单
void Menu()
{
    int item;
    Node *L;
    do
    {
        cout << "\t\t    图书借阅管理系统               " << endl;
        cout << "\t\t1).录入某本图书相关信息；           " << endl;
        cout << "\t\t2).删除某本图书的相关信息；         " << endl;
        cout << "\t\t3).插入某本图书的相关信息；         " << endl;
        cout << "\t\t4).查找某本图书的借阅次数；         " << endl;
        cout << "\t\t5).修改某本图书的借阅次数；         " << endl;
        cout << "\t\t6).查找借阅次数最多和最少的图书记录。" << endl;
        cout << "\t\t0).退出图书管理系统!               " << endl;
        cout << "请输入相应的编号，执行相应的操作:       " << endl;

        cin >> item;
        system("cls");
        switch (item)
        {
        case 1:
            CreateNode(L);
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 2:
            Del(L);
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 3:
            Insert(L);
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 4:
            FindTime(L);
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 5:
            ChangeTime(L);
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 6:
            FindMost(L);
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 0:
            cout << "\n谢谢您的使用，程序即将退出!" << endl;
            exit(0);
            break;
        default:
            cout << "您输入的指令错误，请重新输入\n";
            getchar();
            cout << "请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        }
    } while (item);
}

// 主函数
int main()
{
    Menu();
    return 0;
}
