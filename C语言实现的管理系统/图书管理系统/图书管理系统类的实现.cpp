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

class Fnode
{
public:
    Fnode();           //构造函数,用来初始成员变量
    ~Fnode();          //析构函数,在程序结束后清理分配的内存
    void CreateNode(); //创建图书信息
    void Del();        //删除图书结点信息
    void Insert();     //插入图书信息
    void FindTime();   //根据书名查找图书借阅次数
    void ChangeTime(); //修改图书借阅次数
    void FindMost();   //找出最大和最小的借阅次数
    void Menu();       //菜单
private:
    int max, min;            //最大和最小借阅次数
    Node *L, *p, *q;         //Node类型的指针，头节点指针L和其他函数中可能用到的指针p,q
    string maxname, minname; //存储最大和最小借阅次数的书名
};

//析构函数,用来初始成员变量
Fnode::Fnode()
{
    L->next == NULL;
    p = q = NULL;
}

//析构函数,在程序结束后清理分配的内存
Fnode::~Fnode()
{
    p = L;
    while (p != NULL)
    {
        delete p;
    }
}
// 录入图书信息（尾插法建立）
void Fnode::CreateNode()
{
    int n;
    L = new Node;
    L->next = NULL;
    q = L;
    cout << "请输入您要输入的图书本书:";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p = new Node;
        p->next = q->next;
        q->next = p;
        cout << "请输入第" << i + 1 << "本图书的编号、名称、作者、出版社和借阅次数(用空格隔开):\n";
        cin >> p->no >> p->bookname >> p->author >> p->publishers >> p->time;
        q = p;
    }
}

// 删除图书信息
void Fnode::Del()
{
    p = L->next, q = L;
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
void Fnode::Insert()
{
    p, q = L->next;
    while (q->next != NULL)
        q = q->next;
    p = new Node;
    p->next = q->next;
    q->next = p;
    cout << "请输入图书的编号、名称、作者、出版社和借阅次数(用空格隔开):" << endl;
    cin >> p->no >> p->bookname >> p->author >> p->publishers >> p->time;
    cout << "插入成功!\n";
}

// 查找图书借阅次数（根据书名查找）
void Fnode::FindTime()
{
    p = L->next;
    string name;
    if (p == NULL)
    {
        cout << "数据为空，无法查找。\n";
        return;
    }
    cout << "请输入您要查找的图书名称:";
    cin >> name;
    while (p->bookname != name)
    {
        p = p->next;
        if (p == NULL)
        {
            cout << "没有找到相关信息" << endl;
            return;
        }
    }
    cout << "图书《" << p->bookname << "》的借阅次数为" << p->time << endl;
}

// 修改图书借阅次数（根绝书名查找修改)
void Fnode::ChangeTime()
{
    p = L->next;
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
void Fnode::FindMost()
{
    p = L->next;
    maxname = p->bookname;
    minname = p->bookname;
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
void Fnode::Menu()
{
    int item;
    do
    {
        cout << "\t\t\t===================================================" << endl;
        cout << "\t\t\t#             *|图书借阅管理系统|*                #" << endl;
        cout << "\t\t\t#\t1).录入某本图书相关信息；                 #" << endl;
        cout << "\t\t\t#\t2).删除某本图书的相关信息；               #" << endl;
        cout << "\t\t\t#\t3).插入某本图书的相关信息；               #" << endl;
        cout << "\t\t\t#\t4).查找某本图书的借阅次数；               #" << endl;
        cout << "\t\t\t#\t5).修改某本图书的借阅次数；               #" << endl;
        cout << "\t\t\t#\t6).查找借阅次数最多和最少的图书记。       #" << endl;
        cout << "\t\t\t#\t0).退出图书管理系统!                      #" << endl;
        cout << "\t\t\t===================================================" << endl;
        cout << "请输入相应的编号，执行相应的操作:";
        cin >> item;
        system("cls");
        switch (item)
        {
        case 1:
            CreateNode();
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 2:
            Del();
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 3:
            Insert();
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 4:
            FindTime();
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 5:
            ChangeTime();
            getchar();
            cout << "\n请按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 6:
            FindMost();
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
    Fnode f;
    f.Menu();
    return 0;
}
