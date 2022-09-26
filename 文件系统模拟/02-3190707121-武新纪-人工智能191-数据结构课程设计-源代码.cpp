#include <iostream>
#include <string>
#include <cstring>
using namespace std;

typedef struct file
{
    string filename;    //文件或目录名
    int isdir;          //是否是目录,是的话为1,不是为0
    int opened;         //是否打开
    string filecontent; //文件内容
    file *parent;       //双亲节点
    file *child;        //孩子节点
    file *next;         //后一个兄弟节点
    file *pre;          //前一个兄弟节点
} File;

class FileClass
{
public:
    File *InitFile(string filename, int isdir); // 创建文件与目录结点
    void CreateRoot();                          // 创建文件存储根结点
    void FindPara(string topara);               //寻找当前路径的父路径和祖先路径
    void Mkdir();                               //创建目录
    void Create();                              //创建文件
    void Read();                                //读取文件内容
    void Write();                               //向文件写入内容
    void Del();                                 //删除文件或目录
    void Cd();                                  //切换目录
    void Dir();                                 //显示文件和目录
    void Help();                                //帮助函数
    int Run();                                  //程序运行函数

private:
    File *root, *recent, *temp, *ttemp;         //几个指针，用于类中函数的调用
    string para, command, temppara, recentpara; //几个字符串变量，用来存储路径以及输入的命令
};

// 创建文件与目录结点
File *FileClass::InitFile(string filename, int isdir)
{
    File *node = new File;
    node->filename = filename;
    node->isdir = isdir;
    node->opened = 0;
    node->parent = NULL;
    node->child = NULL;
    node->next = NULL;
    node->pre = NULL;
    return node;
}

// 创建文件存储根结点
void FileClass::CreateRoot()
{
    recent = root = InitFile("/", 1);
    root->parent = NULL;
    root->child = NULL;
    root->pre = root->next = NULL;
    para = "/";
}

//创建目录
void FileClass::Mkdir()
{
    temp = InitFile(" ", 1);
    cin >> temp->filename;
    if (recent->child == NULL)
    {
        temp->parent = recent;
        temp->child = NULL;
        recent->child = temp;
        temp->pre = temp->next = NULL;
        cout << " 目录创建成功!" << endl;
    }
    else
    {
        ttemp = recent->child;
        if (ttemp->filename == temp->filename && ttemp->isdir == 1)
        {
            cout << " 目录已经存在!" << endl;
            return;
        }
        else
        {
            while (ttemp->next)
            {
                ttemp = ttemp->next;
                if (ttemp->filename == temp->filename && ttemp->isdir == 1)
                {
                    cout << " 目录已经存在!" << endl;
                    return;
                }
            }
        }
        ttemp->next = temp;
        temp->parent = NULL;
        temp->child = NULL;
        temp->pre = ttemp;
        temp->next = NULL;
        cout << " 目录创建成功!" << endl;
    }
}

//创建文件
void FileClass::Create()
{
    temp = InitFile(" ", 0);
    cin >> temp->filename;
    cin >> temp->filecontent;
    if (recent->child == NULL)
    {
        temp->parent = recent;
        temp->child = NULL;
        recent->child = temp;
        temp->pre = temp->next = NULL;
        cout << " 文件创建成功!" << endl;
    }
    else
    {
        ttemp = recent->child;
        if (ttemp->filename == temp->filename && ttemp->isdir == 0)
        {
            cout << " 文件已经存在!" << endl;
            return;
        }
        else
        {
            while (ttemp->next)
            {
                ttemp = ttemp->next;
                if (ttemp->filename == temp->filename && ttemp->isdir == 0)
                {
                    cout << " 文件已存在!" << endl;
                    return;
                }
            }
        }
        ttemp->next = temp;
        temp->parent = NULL;
        temp->child = NULL;
        temp->pre = ttemp;
        temp->next = NULL;
        cout << " 文件创建成功!" << endl;
    }
}

//显示文件和目录
void FileClass::Dir()
{
    int i = 0, j = 0;
    temp = recent;
    if (temp != root)
    {
        cout << " <目录> .." << endl;
        i++;
    }
    if (temp->child == NULL)
    {
        cout << "总计:"
             << " 目录:" << i << "\t文件:" << j << endl;
        return;
    }
    temp = temp->child;
    while (temp != NULL)
    {
        if (temp->isdir)
        {
            cout << " <目录> " << temp->filename << endl;
            i++;
        }
        else
        {
            cout << " <文件> " << temp->filename << endl;
            j++;
        }
        temp = temp->next;
    }
    cout << "总计: "
         << "目录: " << i << "\t文件:" << j << endl;
}

//读取文件内容
void FileClass::Read()
{
    string filename;
    cin >> filename;
    if (recent->child == NULL)
    {
        cout << "文件不存在!" << endl;
        return;
    }
    else
    {
        temp = recent->child;
        while (temp)
        {
            if (temp->filename == filename)
            {
                cout << temp->filecontent << endl;
                return;
            }
            temp = temp->next;
        }
        cout << " 文件不存在!" << endl;
    }
}

//向文件写入内容
void FileClass::Write()
{
    string filename;
    cin >> filename;
    if (recent->child == NULL)
    {
        cout << "文件不存在!" << endl;
        return;
    }
    else
    {
        temp = recent->child;
        while (temp != NULL)
        {
            if (temp->filename == filename)
            {
                recent->opened = 1; //设置文件标记为打开
                cin >> temp->filecontent;
                recent->opened = 0; //设置文件标记为关闭
                cout << "文件写入成功!" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "文件不存在!" << endl;
    }
}

//删除文件或目录
void FileClass::Del()
{
    string filename;
    cin >> filename;
    if (recent->child != NULL)
    {
        temp = recent->child;
        while (temp->next && temp->filename != filename)
            temp = temp->next;
        if (temp->filename != filename)
        {
            cout << " 不存在该文件!" << endl;
            return;
        }
    }
    else
    {
        cout << " 不存在该文件! " << endl;
        return;
    }
    if (temp->parent == NULL)
    {
        temp->pre->next = temp->next;
        if (temp->next)
            temp->next->pre = temp->pre;
        temp->pre = temp->next = NULL;
    }
    else
    {
        if (temp->next)
            temp->next->parent = temp->parent;
        temp->parent->child = temp->next;
    }
    delete temp;
    cout << "文件已删除!" << endl;
}

//切换目录
void FileClass::Cd()
{
    string topara;
    cin >> topara;
    if (topara == "..") //切换上一级目录
    {
        int i;
        while (recent->pre)
            recent = recent->pre;
        if (recent->parent)
            recent = recent->parent;
        i = para.length();
        while (para[i] != '/' && i > 0)
            i--;
        para.replace(i + 1, para.length(), "\0");
    }
    else
        FindPara(topara);
}

//寻找当前路径的父路径和祖先路径
void FileClass::FindPara(string topara)
{
    int i = 0;
    int sign = 1;
    char str[50];
    if (topara == "/") //切换回根结点
    {
        recent = root;
        para = "/";
        return;
    }
    temp = recent;
    temppara = para;
    if (topara[0] == '/') //切换为根节点的第一级子目录
    {
        recent = root->child;
        i++;
        para = "/";
    }
    else
    {
        if (recent != NULL && recent != root)
            para += "/";
        if (recent && recent->child)
        {
            if (recent->isdir)
                recent = recent->child;
            else
            {
                cout << "路径错误!" << endl;
                return;
            }
        }
    }
    while (i <= signed(topara.length()) && recent) //以下主要对输出路径进行处理
    {
        int j = 0;
        if (topara[i] == '/' && recent->child)
        {
            i++;
            if (recent->isdir)
                recent = recent->child;
            else
            {
                cout << "路径错误!" << endl;
                return;
            }
            para += "/";
        }
        while (topara[i] != '/' && i <= signed(topara.length()))
        {
            str[j] = topara[i];
            i++;
            j++;
        }
        str[j] = '\0';
        recentpara = string(str);
        while ((recent->filename != recentpara || (recent->isdir != 1)) &&
               recent->next != NULL)
        {
            recent = recent->next;
        }
        if (recent->filename == recentpara)
        {
            if (recent->isdir == 0)
            {
                para = temppara;
                recent = temp;
                cout << " 是文件不是目录。\n";
                return;
            }
            para += recent->filename;
        }
        if (recent->filename != recentpara || recent == NULL)
        {
            para = temppara;
            recent = temp;
            cout << " 输入路径错误\n";
            return;
        }
    }
}

//帮助函数
void FileClass::Help()
{
    cout << "\t\t\t=====================帮助命令一览====================\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*          1>. create: 创建文件                     *\n";
    cout << "\t\t\t*          2>. read: 读取文件                       *\n";
    cout << "\t\t\t*          3>. write: 写入文件                      *\n";
    cout << "\t\t\t*          4>. del : 删除文件                       *\n";
    cout << "\t\t\t*          5>. mkdir: 建立目录                      *\n";
    cout << "\t\t\t*          6>. cd: 切换目录                         *\n";
    cout << "\t\t\t*          7>. exit: 退出登录                       *\n";
    cout << "\t\t\t*                                    欢迎使用本系统!*\n";
    cout << "\t\t\t=====================================================\n";
}

//程序运行函数
int FileClass::Run()
{
    cout << "root" << para << ">";
    cin >> command;
    if (command == "mkdir")
        Mkdir();
    else if (command == "dir")
        Dir();
    else if (command == "cd")
        Cd();
    else if (command == "create")
        Create();
    else if (command == "read")
        Read();
    else if (command == "write")
        Write();
    else if (command == "del")
        Del();
    else if (command == "help")
        Help();
    else if (command == "exit")
    {
        cout << "即将退出文件系统模拟，谢谢您的使用！" << endl;
        return 0;
    }
    else
        cout << " 请参考help 提供的命令列表!" << endl;
    return 1;
}
int main()
{
    int i = 0;
    bool in = false;     //in为true是允许进入系统，负责不允许进入
    FileClass f;         //构建一个FileClass对象
    string user, passwd; //用于存储用户名和密码
    cout << "\t\t\t=====================文件系统模拟====================\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*         1>. 你只有三次机会来试验账号              *\n";
    cout << "\t\t\t*         2>. 键入help 可以获取帮助                 *\n";
    cout << "\t\t\t*                                    欢迎使用本系统!*\n";
    cout << "\t\t\t=====================================================\n";
    cout << endl;
    while (i < 3) //设置输入账号和密码的次数最多为三次
    {
        cout << "请输入用户名:";
        cin >> user;
        cout << "请输入密码:";
        cin >> passwd;
        if (user == "root" && passwd == "root")
        {
            in = true;
            break;
        }
        else
        {
            if (2 - i != 0)
                cout << "\t您输入的账号或密码错误，请重新输入,您还有" << 2 - i << "次机会!" << endl;
            else
            {
                cout << "\t您的机会已用完！谢谢您的使用" << endl;
                exit(0);
            }
        }
        i++;
    }
    f.CreateRoot(); //创建根节点
    while (in)      //进入消息循环
    {
        if (!f.Run())
            break;
    }
    return 0;
}