#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#define MAXDATASIZE 100
#define N 256 //文件名和命令名最长为256字节

//定义的命令结构体，包含命令和参数
typedef struct command
{
    char commd[MAXDATASIZE];
    char arg[MAXDATASIZE];
} Commd;

// 服务端函数声明
void commd_ls(int sockfd, char *arg);  //显示文件列表
void commd_get(int sockfd, char *arg); //下载文件
void commd_put(int sockfd, char *arg); //上传文件
void commd_rm(int sockfd, char *arg);  //删除文件
void commd_cd(int sockfd, char *arg);  //切换工作目录
void commd_pwd(int sockfd);            //打印当前工作目录
int split(char *str, Commd *commd);    //分割客户端发来的信息，获得命令和参数

int main(int arg, char *argv[])
{
    int ser_sockfd, cli_sockfd;
    pthread_t nid;
    struct sockaddr_in ser_addr, cli_addr;
    int ser_len, cli_len;
    char commd_str[N];
    Commd commd;
    bzero(commd_str, N); //将commd所指向的字符串的前N个字节置为0，包括'\0'

    if ((ser_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Sokcet Error!\n");
        return -1;
    }

    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //本地ip地址
    ser_addr.sin_port = htons(8989);              //转换成网络字节
    ser_len = sizeof(ser_addr);
    //将ip地址与套接字绑定
    if ((bind(ser_sockfd, (struct sockaddr *)&ser_addr, ser_len)) < 0)
    {
        perror("Bind Error!\n");
        return -1;
    }
    //服务器端监听
    if (listen(ser_sockfd, 5) < 0)
    {
        perror("Linsten Error!\n");
        return -1;
    }

    bzero(&cli_addr, sizeof(cli_addr));
    ser_len = sizeof(cli_addr);

    while (1)
    {
        printf("server>");
        //服务器端接受来自客户端的连接，返回一个套接字，此套接字为新建的一个，并将客户端的地址等信息存入cli_addr中
        //原来的套接字仍处于监听中
        if ((cli_sockfd = accept(ser_sockfd, (struct sockaddr *)&cli_addr, &cli_len)) < 0)
        {
            perror("响应错误!\n");
            exit(1);
        }
        //由套接字接收数据时，套接字把接收的数据放在套接字缓冲区，再由用户程序把它们复制到用户缓冲区，然后由read函数读取
        //write函数同理
        if (read(cli_sockfd, commd_str, N) < 0) //read函数从cli_sockfd中读取N个字节数据放入commd中
        {
            perror("读取错误!\n");
            exit(1);
        }
        split(commd_str, &commd);
        if (strcmp(commd.commd, "ls") == 0)
        {
            commd_ls(cli_sockfd, commd.arg);
        }
        else if (strcmp(commd.commd, "cd") == 0)
            commd_cd(cli_sockfd, commd.arg);
        else if (strcmp(commd.commd, "pwd") == 0)
            commd_pwd(cli_sockfd);
        else if (strcmp(commd.commd, "rm") == 0)
            commd_rm(cli_sockfd, commd.arg);
        else if (strcmp(commd.commd, "get") == 0)
            commd_get(cli_sockfd, commd.arg);
        else if (strcmp(commd.commd, "put") == 0)
            commd_put(cli_sockfd, commd.arg);
        else
            printf("命令错误!\n");
    }
    return 0;
}
//分割客户端发来的信息，获得命令和参数
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

// 显示文件列表
void commd_ls(int sockfd, char *arg)
{
    DIR *mydir = NULL;
    struct dirent *myitem = NULL;
    char commd[N];
    bzero(commd, N);
    //opendir为用来打开参数name 指定的目录, 并返回DIR*形态的目录流
    //mydir中存有相关目录的信息
    if ((mydir = opendir(arg)) == NULL)
    {
        perror("OpenDir Error!\n");
        exit(1);
    }

    while ((myitem = readdir(mydir)) != NULL) //用来读取目录,返回是dirent结构体指针
    {
        if (sprintf(commd, myitem->d_name, N) < 0) //把文件名写入commd指向的缓冲区
        {
            perror("Sprintf Error!\n");
            exit(1);
        }

        if (write(sockfd, commd, N) < 0) //将commd缓冲区的内容发送会client
        {
            perror("Write Error!\n");
            exit(1);
        }
    }

    closedir(mydir); //关闭目录流
    close(sockfd);
    return;
}

// 实现文件的下载
void commd_get(int sockfd, char *filename)
{
    int fd, nbytes;
    char buffer[N];
    bzero(buffer, N);
    printf("get filename : [ %s ]\n", filename);
    if ((fd = open(filename, O_RDONLY)) < 0) //以只读的方式打开client要下载的文件
    {
        perror("Open file Error!\n");
        buffer[0] = 'N';
        if (write(sockfd, buffer, N) < 0)
        {
            perror("Write Error!At commd_get 1\n");
            exit(1);
        }
        return;
    }
    buffer[0] = 'Y'; //此处标示出文件读取成功
    if (write(sockfd, buffer, N) < 0)
    {
        perror("Write Error! At commd_get 2!\n");
        close(fd);
        exit(1);
    }
    while ((nbytes = read(fd, buffer, N)) > 0) //将文件内容读到buffer中
    {
        if (write(sockfd, buffer, nbytes) < 0) //将buffer发送回client
        {
            perror("Write Error! At commd_get 3!\n");
            close(fd);
            exit(1);
        }
    }
    close(fd);
    close(sockfd);
    return;
}

// 实现文件的上传
void commd_put(int sockfd, char *filename)
{
    int fd, nbytes;
    char buffer[N];
    bzero(buffer, N);
    printf("get filename : [ %s ]\n", filename);
    if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) //以只写的方式打开文件，若文件存在则清空，若文件不存在则新建文件
    {
        perror("打开文件错误!\n");
        return;
    }
    while ((nbytes = read(sockfd, buffer, N)) > 0) //将client发送的文件写入buffer
    {
        if (write(fd, buffer, nbytes) < 0) //将buffer中的内容写到文件中
        {
            perror("写入错误!\n");
            close(fd);
            exit(1);
        }
    }
    close(fd);
    close(sockfd);
    return;
}

//实现服务器端文件的删除
void commd_rm(int sockfd, char *arg)
{
    int err;
    char buf[100];
    err = remove(arg);
    sprintf(buf, "%d", err);
    if (write(sockfd, buf, 100) < 0) //将commd缓冲区的内容发送会client
    {
        perror("写入错误!\n");
        exit(1);
    }
}

// 实现服务器端目录的切换
void commd_cd(int sockfd, char *arg)
{
    int err;
    char buf[100];
    err = chdir(arg);
    sprintf(buf, "%d", err);
    if (write(sockfd, buf, 100) < 0) //将commd缓冲区的内容发送会client
    {
        perror("写入错误!\n");
        exit(1);
    }
}

// 实现打印服务器端当前所在目录
void commd_pwd(int sockfd)
{
    char buf[100];
    getcwd(buf, sizeof(buf));
    if (write(sockfd, buf, 100) < 0) //将commd缓冲区的内容发送会client
    {
        perror("写入错误!\n");
        exit(1);
    }
}