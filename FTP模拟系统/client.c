#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#define SERVERPORT 21
#define MAXDATASIZE 100
#define MAXBUF 1000
#define N 256

//定义的命令结构体，包含命令和参数
typedef struct command
{
    char commd[MAXDATASIZE]; //基本命令
    char arg[MAXDATASIZE];   //命令参数
} Commd;

//客户端函数声明
int commd_lls(char *arg);                              //列出客户端当前目录下的文件和目录
int commd_lcd(char *arg);                              //切换客户端当前所在的目录
int commd_lpwd();                                      //打印客户端当前所在目录完整路径名
int commd_lrm(char *arg);                              //删除当前所在目录下的指定文件
void commd_get();                                      //下载文件
void commd_ls(struct sockaddr_in my_addr, char *arg);  //显示服务端文件列表
void commd_cd(struct sockaddr_in my_addr, char *arg);  //切换服务端当前工作目录
void commd_pwd(struct sockaddr_in my_addr);            //打印服务端端当前工作目录
void commd_put(struct sockaddr_in my_addr, char *arg); //上传文件
void commd_rm(struct sockaddr_in my_addr, char *arg);  //删除服务端文件
int split(char *str, Commd *commd);                    //分割用户输入，获得命令和参数
void commd_help();                                     //帮助命令

int main(int argc, char *argv[])
{
    int sockfd, err, n;
    Commd commd;
    char input[MAXDATASIZE];
    struct sockaddr_in my_addr;

    //初始化sockaddr_in类型
    bzero(&my_addr, sizeof(my_addr));                 //将＆addr中的前sizeof（addr）字节置为0，包括'\0'
    my_addr.sin_family = AF_INET;                     //AF_INET代表TCP／IP协议
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //将点间隔地址转换为网络字节顺序
    my_addr.sin_port = htons(8989);                   //转换为网络字节顺序

    while (1)
    {
        printf("ftp>");
        bzero(input, MAXDATASIZE);
        if (fgets(input, MAXDATASIZE, stdin) == NULL)
        {
            printf("读取错误!\n");
            return -1;
        }
        n = split(input, &commd); //分割用户的输入，获得命令和参数

        //以下是对用户输入命令的判断，从而执行相应的操作
        if (strcmp(commd.commd, "ls") == 0) //处理ls命令
        {
            if (n == 2)
                commd_ls(my_addr, commd.arg);
            else
                commd_ls(my_addr, "./");
        }
        else if (strcmp(commd.commd, "cd") == 0) //处理cd命令
            commd_cd(my_addr, commd.arg);
        else if (strcmp(commd.commd, "pwd") == 0) //处理pwd命令
            commd_pwd(my_addr);
        else if (strcmp(commd.commd, "get") == 0) //处理get命令
            commd_get(my_addr, commd.arg);
        else if (strcmp(commd.commd, "rm") == 0) //处理rm命令
            commd_rm(my_addr, commd.arg);
        else if (strcmp(commd.commd, "lls") == 0) //处理lls命令
        {
            if (n == 2)
                commd_lls(commd.arg);
            else
                commd_lls("./");
        }
        else if (strcmp(commd.commd, "lcd") == 0) //处理lcd命令
            commd_lcd(commd.arg);
        else if (strcmp(commd.commd, "lpwd") == 0) //处理lpwd命令
            commd_lpwd();
        else if (strcmp(commd.commd, "put") == 0) //处理put命令
            commd_put(my_addr, commd.arg);
        else if (strcmp(commd.commd, "lrm") == 0) //处理lrm命令
            commd_lrm(commd.arg);
        else if (strcmp(commd.commd, "help") == 0) //处理help命令
            commd_help();
        else if (strcmp(commd.commd, "exit") == 0) //处理exit命令
        {
            exit(0);
            printf("谢谢您使用ftp模拟系统\n");
        }
        else //输入命令错误的处理方式
            printf("输入的命令错误，请重新输入!\n");
    }
    return 0;
}

//列出客户端当前目录下的文件和目录
int commd_lls(char *arg)
{
    int fd, err;
    char buf[MAXBUF], commd_str[100];
    if (arg != NULL)
        sprintf(commd_str, "ls -la %s > /tmp/buf", arg);
    err = system(commd_str);
    if (err < 0)
        return -1;
    fd = open("/tmp/buf", O_RDONLY);
    if (fd < 0)
        return -1;
    read(fd, buf, sizeof(buf));
    close(fd);
    remove("rm /tmp/buf");
    printf("%s\n", buf);
    return 0;
}

int commd_lcd(char *arg) //切换客户端当前所在的目录
{
    int err;
    err = chdir(arg);
    if (err < 0)
        return -1;
    return 0;
}

int commd_lpwd() //打印客户端当前所在目录完整路径名
{
    char buf[100];
    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;
}
int commd_lrm(char *arg) //删除当前所在目录下的指定文件
{
    int err;
    err = remove(arg);
    if (err < 0)
        return -1;
    return 0;
}

// 实现文件下载功能
void commd_get(struct sockaddr_in my_addr, char *arg)
{
    int fd;
    int sockfd;
    char buffer[N], commd[N];
    int nbytes;
    //创建套接字，并进行错误检测
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        exit(1);
    }
    //connect函数用于实现客户端与服务端的连接,此处还进行了错误检测
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        exit(1);
    }
    sprintf(commd, "get %s", arg);
    //通过write函数向服务端发送数据
    if (write(sockfd, commd, N) < 0)
    {
        printf("Write Error!At commd_get 1\n");
        exit(1);
    }
    //利用read函数来接受服务器发来的数据
    if (read(sockfd, buffer, N) < 0)
    {
        printf("Read Error!At commd_get 1\n");
        return;
    }
    //用于检测服务器端文件是否打开成功
    if (buffer[0] == 'N')
    {
        close(sockfd);
        printf("Can't Open The File!\n");
        return;
    }
    //open函数创建一个文件，文件地址为(commd+4)，该地址从命令行输入获取
    if ((fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        printf("Open Error!\n");
        exit(1);
    }
    //read函数从套接字中获取N字节数据放入buffer中，返回值为读取的字节数
    while ((nbytes = read(sockfd, buffer, N)) > 0)
    {
        //write函数将buffer中的内容读取出来写入fd所指向的文件，返回值为实际写入的字节数
        if (write(fd, buffer, nbytes) < 0)
        {
            printf("Write Error!At commd_get 2");
        }
    }
    close(fd);
    close(sockfd);
    return;
}

//显示服务端文件列表
void commd_ls(struct sockaddr_in my_addr, char *arg)
{
    int sockfd;
    char commd[N];
    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        return;
    }
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        return;
    }
    sprintf(commd, "ls %s", arg);
    if (write(sockfd, commd, N) < 0)
    {
        printf("写入错误\n");
        exit(1);
    }
    //利用read函数来接受服务器发来的数据
    while (read(sockfd, commd, N) > 0)
        printf("%s ", commd);
    printf("\n");
    close(sockfd);
    return;
}

void commd_cd(struct sockaddr_in my_addr, char *arg)
{
    int sockfd;
    char commd[N];
    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        return;
    }
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        return;
    }
    sprintf(commd, "cd %s", arg);
    if (write(sockfd, commd, N) < 0)
    {
        printf("写入错误\n");
        return;
    }
    //利用read函数来接受服务器发来的数据
    read(sockfd, commd, N);
    if (strncmp(commd, "0", 1) == 0)
        printf("切换成功\n");
    else
        printf("切换失败!\n");
}

void commd_pwd(struct sockaddr_in my_addr)
{
    int sockfd;
    char commd[N];
    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        return;
    }
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        return;
    }
    sprintf(commd, "pwd");
    if (write(sockfd, commd, N) < 0)
    {
        printf("写入错误\n");
        exit(1);
    }
    //利用read函数来接受服务器发来的数据
    read(sockfd, commd, N);
    printf("%s\n", commd);
}

//实现上传文件的功能
void commd_put(struct sockaddr_in my_addr, char *arg)
{
    int fd;
    int sockfd;
    char buffer[N], commd[N];
    int nbytes;
    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        exit(1);
    }
    //客户端与服务端连接
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        exit(1);
    }
    sprintf(commd, "put %s", arg);
    //从commd中读取N字节数据，写入套接字中
    if (write(sockfd, commd, N) < 0)
    {
        printf("Wrtie Error!At commd_put 1\n");
        exit(1);
    }
    //open函数从(commd+4)中，读取文件路径，以只读的方式打开
    if ((fd = open(arg, O_RDONLY)) < 0)
    {
        printf("Open Error!\n");
        exit(1);
    }
    //从fd指向的文件中读取N个字节数据
    while ((nbytes = read(fd, buffer, N)) > 0)
    {
        //从buffer中读取nbytes字节数据，写入套接字中
        if (write(sockfd, buffer, nbytes) < 0)
        {
            printf("Write Error!At commd_put 2");
        }
    }
    close(fd);
    close(sockfd);
    return;
}

void commd_rm(struct sockaddr_in my_addr, char *arg)
{
    int sockfd;
    char commd[N];
    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        return;
    }
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        return;
    }
    sprintf(commd, "rm -rf %s", arg);
    if (write(sockfd, commd, N) < 0)
    {
        printf("写入错误\n");
        return;
    }
    //利用read函数来接受服务器发来的数据
    read(sockfd, commd, N);
    if (strncmp(commd, "0", 1) == 0)
        printf("删除成功!\n");
    else
        printf("删除失败!\n");
    close(sockfd);
    return;
}

int split(char *str, Commd *commd)
{
    int n = 0;
    char *ret;
    char dataList[10][20];
    ret = strtok(str, " ");
    while (ret != NULL)
    {
        strcpy(dataList[n++], ret);
        ret = strtok(NULL, " ");
    }
    for (int i = 0; i < 2; i++)
        if (dataList[i][strlen(dataList[i]) - 1] == '\n')
            dataList[i][strlen(dataList[i]) - 1] = '\0';
    strcpy(commd->commd, dataList[0]);
    strcpy(commd->arg, dataList[1]);
    return n;
}

void commd_help()
{
    printf("\t\t\t***********************ftp命令一览**************************************\n");
    printf("\t\t\t*                                                                      *\n");
    printf("\t\t\t*        <1>.ls      <文件或目录>        列出服务端当前的文件和目录    *\n");
    printf("\t\t\t*        <2>.lls     <文件或目录>        列出客户端当前的文件和目录    *\n");
    printf("\t\t\t*        <3>.rm	     <文件或目录>        删除服务端文件                *\n");
    printf("\t\t\t*        <4>.lrm     <文件或目录>        删除客户端文件                *\n");
    printf("\t\t\t*        <5>.cd         <目录>           切换服务端目录                *\n");
    printf("\t\t\t*        <6>.lcd        <目录>           切换客户端目录                *\n");
    printf("\t\t\t*        <7>.get        <文件>           下载服务端文件                *\n");
    printf("\t\t\t*        <8>.put        <文件>           将客户端文件上传到服务端      *\n");
    printf("\t\t\t*        <9>.pwd	                 打印当前所在服务端目录        *\n");
    printf("\t\t\t*        <10>.lpwd	                 打印当前客户端所在目录        *\n");
    printf("\t\t\t*        <12>.help	                 帮助命令，查看所有命令用法    *\n");
    printf("\t\t\t*                                                欢迎使用ftp模拟系统！ *\n");
    printf("\t\t\t***********************************************************************\n");
}