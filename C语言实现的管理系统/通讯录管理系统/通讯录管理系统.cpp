#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

//自定义一个联系人结点类型
typedef struct node1
{
    string name;        //姓名
    string tel;         //手机号
    string email;       //邮箱
    string address;     //地址
    struct node1 *next; //指向下一节点的指针
} Node;

//自定义一个二叉排序树结点类型
typedef struct node2
{
    Node data;
    struct node2 *lchild, *rchild;
} BSTNode;

//构造结点通讯录类
class Fnode
{
public:
    Fnode();                                //构造函数，用于初始化一些变量
    ~Fnode();                               //析构函数，用于程序结束之后对分配的内存进行清理
    void CreateInfo();                      //录入联系人信息
    void InsertInfo();                      //插入联系人信息
    void FindInfoName();                    //按姓名查找联系人信息
    void FindInfoTel();                     //按手机号查找联系人信息
    void DeleteInfoTel();                   //按手机号删除联系人信息
    void DispInfo();                        //打印所有联系人信息
    void DispInfoSort();                    //按姓名排序输出联系人信息
    void SaveInfoToFile();                  //保存联系人信息至文件
    void ReadInfoFromFile();                //从文件读取联系人信息
    void Run();                             //功能函数，包含菜单和相关函数的入口
    bool InsertBST(BSTNode *&bt, Node key); //插入二叉排序树结点,递归实现
    void CreateBST();                       //由链表创建二叉排序树
    void InOrder(BSTNode *b);               //中序遍历输出二叉排序树，递归实现
    void DestroyBST(BSTNode *&b);           //释放二叉排序树,递归实现

private:
    bool opened;     //用于表明文件是否被读取过，未读为0,已读为1
    Node *L, *p, *q; //定义通讯录结点的头指针和其他成员函数中可能用到的指针
    BSTNode *btree;  //二叉排序树头节点
};

//构造函数，用于初始化一些变量
Fnode::Fnode()
{
    L = new Node;
    L->next = NULL;
    p = q = NULL;
    btree = NULL;
    opened = 0;
}

//析构函数，用于程序结束之后对分配的内存进行清理
Fnode::~Fnode()
{
    p = L;
    while (p != NULL)
    {
        delete p;
        p = p->next;
    }
}

void Fnode::CreateInfo() //创建结点
{
    int n;
    q = L, p = NULL;
    while (q->next != NULL)
        q = q->next;
    cout << "请输入您要录入的联系人个数:";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p = new Node;
        cout << "请输入第" << i + 1 << "位联系人的姓名、手机号、邮箱和地址(用空格隔开):" << endl;
        cin >> p->name >> p->tel >> p->email >> p->address;
        p->next = q->next;
        q->next = p;
        q = p;
    }
}

//插入联系人信息
void Fnode::InsertInfo()
{
    q = L, p = NULL;
    while (q->next != NULL)
        q = q->next;
    p = new Node;
    cout << "请输入您要插入的联系人的姓名、手机号、邮箱和地址(用空格隔开):" << endl;
    cin >> p->name >> p->tel >> p->email >> p->address;
    p->next = q->next;
    q->next = p;
    cout << "插入成功!" << endl;
}

//打印所有联系人信息
void Fnode::DispInfo()
{
    p = L->next;
    if (p == NULL)
        cout << "数据为空，无法打印" << endl;
    else
    {
        cout << "姓名  \t\t"
             << "手机号       \t\t"
             << "邮箱             \t\t"
             << "地址" << endl;
        while (p != NULL)
        {
            cout << p->name << "\t\t" << p->tel << "\t\t" << p->email << "\t\t" << p->address << endl;
            p = p->next;
        }
    }
}

//按姓名查找联系人信息
void Fnode::FindInfoName()
{
    string name;
    p = L->next;
    if (p == NULL)
        cout << "数据为空，无法查找" << endl;
    else
    {
        cout << "请输入要查找的联系人的姓名:";
        cin >> name;
        while (p->name != name)
        {
            p = p->next;
            if (p == NULL)
            {
                cout << "没有找到相关联系人信息" << endl;
                return;
            }
        }
        cout << "该联系人的信息如下" << endl;
        cout << "姓名  \t\t"
             << "手机号       \t\t"
             << "邮箱             \t\t"
             << "地址" << endl;
        cout << p->name << "\t\t" << p->tel << "\t\t" << p->email << "\t\t" << p->address << endl;
    }
}

//按手机号查找联系人信息
void Fnode::FindInfoTel()
{
    string tel;
    p = L->next;
    if (p == NULL)
        cout << "数据为空，无法查找" << endl;
    else
    {
        cout << "请输入要查找的联系人的手机号:";
        cin >> tel;
        while (p->tel != tel)
        {
            p = p->next;
            if (p == NULL)
            {
                cout << "没有找到相关信息" << endl;
                return;
            }
        }
        cout << "该联系人的信息如下" << endl;
        cout << "姓名  \t\t"
             << "手机号       \t\t"
             << "邮箱             \t\t"
             << "地址" << endl;
        cout << p->name << "\t\t" << p->tel << "\t\t" << p->email << "\t\t" << p->address << endl;
    }
}

//按手机号删除联系人信息
void Fnode::DeleteInfoTel()
{
    string tel;
    p = L->next, q = L;
    if (p == NULL)
        cout << "数据为空，无法删除" << endl;
    else
    {
        cout << "请输入要删除的联系人的手机号" << endl;
        cin >> tel;
        while (p->tel != tel)
        {
            p = p->next;
            q = q->next;
            if (p == NULL)
            {
                cout << "没有找到相关信息" << endl;
                return;
            }
        }
        q->next = p->next;
        delete p;
        cout << "手机号为" << tel << "的联系人删除成功!" << endl;
    }
}

//按姓名排序输出联系人信息
void Fnode::DispInfoSort()
{
    CreateBST();
    cout << "姓名  \t\t"
         << "手机号       \t\t"
         << "邮箱             \t\t"
         << "地址" << endl;
    InOrder(btree);
    DestroyBST(btree);
}

//保存联系人信息至文件
void Fnode::SaveInfoToFile()
{
    p = L->next;
    if (p == NULL)
        cout << "数据为空，无法写入!" << endl;
    else
    {
        ofstream outfile("./联系人.csv");
        if (!outfile)
        {
            cout << "无法打开文件!";
            return;
        }
        outfile << "姓名,"
                << "手机号,"
                << "邮箱,"
                << "地址" << endl;
        while (p->next != NULL)
        {
            outfile << p->name << "," << p->tel << "," << p->email << "," << p->address << endl;
            p = p->next;
        }
        outfile << p->name << "," << p->tel << "," << p->email << "," << p->address;
        outfile.close();
        cout << "保存联系人信息成功！请查看当前目录下的“联系人.csv文件”" << endl;
    }
}

//从文件读取联系人信息
void Fnode::ReadInfoFromFile()
{
    ifstream infile("./联系人.csv");
    if (!infile)
    {
        cout << "无法打开文件!";
        return;
    }
    else if (opened == 1)
    {
        cout << "文件已经被读取，不能够重复读取!" << endl;
        return;
    }
    else
    {
        char str[500];
        q = L, p = NULL;
        while (q->next != NULL)
            q = q->next;
        infile.getline(str, sizeof(str));
        while (!infile.eof())
        {
            p = new Node;
            infile.getline(str, sizeof(str));
            p->name = strtok(str, ",");
            p->tel = strtok(NULL, ",");
            p->email = strtok(NULL, ",");
            p->address = strtok(NULL, ",");
            p->next = q->next;
            q->next = p;
            q = p;
        }
        infile.close();
        cout << "读取数据成功！" << endl;
        opened = 1;
    }
}

//插入二叉排序树结点
bool Fnode::InsertBST(BSTNode *&bt, Node key)
{
    if (bt == NULL)
    {
        bt = new BSTNode;
        bt->data = key;
        bt->lchild = bt->rchild = NULL;
        return true;
    }
    else if (key.name == bt->data.name)
        return false;
    else if (key.name < bt->data.name)
        return InsertBST(bt->lchild, key);
    else
        return InsertBST(bt->rchild, key);
}

//由链表创建二叉排序树
void Fnode::CreateBST()
{
    btree = NULL;
    p = L->next;
    while (p != NULL)
    {
        InsertBST(btree, *p);
        p = p->next;
    }
}

//中序遍历输出二叉排序树
void Fnode::InOrder(BSTNode *b)
{
    if (b != NULL)
    {
        InOrder(b->lchild);
        cout << b->data.name << "\t\t" << b->data.tel << "\t\t" << b->data.email << "\t\t" << b->data.address << endl;
        InOrder(b->rchild);
    }
}

//释放二叉排序树
void Fnode::DestroyBST(BSTNode *&b)
{
    if (b != NULL)
    {
        DestroyBST(b->lchild);
        DestroyBST(b->rchild);
        delete b;
    }
}

//菜单
void Fnode::Run()
{
    int item;
    do
    {
        cout << "\t\t\t==================通讯录管理系统==================" << endl;
        cout << "\t\t\t# \t                                         #" << endl;
        cout << "\t\t\t# \t1)联系人信息的逐条录入。                 #" << endl;
        cout << "\t\t\t# \t2)插入某个联系人的信息。                 #" << endl;
        cout << "\t\t\t# \t3)按手机号查找某个联系人的信。           #" << endl;
        cout << "\t\t\t# \t4)按姓名查询某个联系人。                 #" << endl;
        cout << "\t\t\t# \t5)按手机号删除某个联系人的信息           #" << endl;
        cout << "\t\t\t# \t6)所有联系人信息的输出显示。             #" << endl;
        cout << "\t\t\t# \t7)所有联系人按姓名排序并输出显示。       #" << endl;
        cout << "\t\t\t# \t8)所有联系人信息的文件保存。             #" << endl;
        cout << "\t\t\t# \t9)所有联系人信息的文件读取。             #" << endl;
        cout << "\t\t\t# \t0)退出管理系统。                         #" << endl;
        cout << "\t\t\t==================================================" << endl;
        cout << "请输入相应的命令，执行相应的功能:";
        cin >> item;
        system("cls");
        switch (item)
        {
        case 1:
            CreateInfo();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 2:
            InsertInfo();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 3:
            FindInfoTel();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 4:
            FindInfoName();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 5:
            DeleteInfoTel();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 6:
            DispInfo();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 7:
            DispInfoSort();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 8:
            SaveInfoToFile();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 9:
            ReadInfoFromFile();
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
            break;
        case 0:
            cout << "即将退出通讯录管理系统......" << endl;
            cout << "谢谢您的使用!";
            exit(0);
            break;
        default:
            cout << "您输入的指令错误，请重新输入!" << endl;
            getchar();
            cout << "\n按任意键返回主菜单" << endl;
            getchar();
            system("cls");
        }
    } while (item);
}

//主函数
int main()
{
    Fnode f;
    system("cls");
    f.Run();
    return 0;
}