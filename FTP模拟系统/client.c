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

//���������ṹ�壬��������Ͳ���
typedef struct command
{
    char commd[MAXDATASIZE]; //��������
    char arg[MAXDATASIZE];   //�������
} Commd;

//�ͻ��˺�������
int commd_lls(char *arg);                              //�г��ͻ��˵�ǰĿ¼�µ��ļ���Ŀ¼
int commd_lcd(char *arg);                              //�л��ͻ��˵�ǰ���ڵ�Ŀ¼
int commd_lpwd();                                      //��ӡ�ͻ��˵�ǰ����Ŀ¼����·����
int commd_lrm(char *arg);                              //ɾ����ǰ����Ŀ¼�µ�ָ���ļ�
void commd_get();                                      //�����ļ�
void commd_ls(struct sockaddr_in my_addr, char *arg);  //��ʾ������ļ��б�
void commd_cd(struct sockaddr_in my_addr, char *arg);  //�л�����˵�ǰ����Ŀ¼
void commd_pwd(struct sockaddr_in my_addr);            //��ӡ����˶˵�ǰ����Ŀ¼
void commd_put(struct sockaddr_in my_addr, char *arg); //�ϴ��ļ�
void commd_rm(struct sockaddr_in my_addr, char *arg);  //ɾ��������ļ�
int split(char *str, Commd *commd);                    //�ָ��û����룬�������Ͳ���
void commd_help();                                     //��������

int main(int argc, char *argv[])
{
    int sockfd, err, n;
    Commd commd;
    char input[MAXDATASIZE];
    struct sockaddr_in my_addr;

    //��ʼ��sockaddr_in����
    bzero(&my_addr, sizeof(my_addr));                 //����addr�е�ǰsizeof��addr���ֽ���Ϊ0������'\0'
    my_addr.sin_family = AF_INET;                     //AF_INET����TCP��IPЭ��
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //��������ַת��Ϊ�����ֽ�˳��
    my_addr.sin_port = htons(8989);                   //ת��Ϊ�����ֽ�˳��

    while (1)
    {
        printf("ftp>");
        bzero(input, MAXDATASIZE);
        if (fgets(input, MAXDATASIZE, stdin) == NULL)
        {
            printf("��ȡ����!\n");
            return -1;
        }
        n = split(input, &commd); //�ָ��û������룬�������Ͳ���

        //�����Ƕ��û�����������жϣ��Ӷ�ִ����Ӧ�Ĳ���
        if (strcmp(commd.commd, "ls") == 0) //����ls����
        {
            if (n == 2)
                commd_ls(my_addr, commd.arg);
            else
                commd_ls(my_addr, "./");
        }
        else if (strcmp(commd.commd, "cd") == 0) //����cd����
            commd_cd(my_addr, commd.arg);
        else if (strcmp(commd.commd, "pwd") == 0) //����pwd����
            commd_pwd(my_addr);
        else if (strcmp(commd.commd, "get") == 0) //����get����
            commd_get(my_addr, commd.arg);
        else if (strcmp(commd.commd, "rm") == 0) //����rm����
            commd_rm(my_addr, commd.arg);
        else if (strcmp(commd.commd, "lls") == 0) //����lls����
        {
            if (n == 2)
                commd_lls(commd.arg);
            else
                commd_lls("./");
        }
        else if (strcmp(commd.commd, "lcd") == 0) //����lcd����
            commd_lcd(commd.arg);
        else if (strcmp(commd.commd, "lpwd") == 0) //����lpwd����
            commd_lpwd();
        else if (strcmp(commd.commd, "put") == 0) //����put����
            commd_put(my_addr, commd.arg);
        else if (strcmp(commd.commd, "lrm") == 0) //����lrm����
            commd_lrm(commd.arg);
        else if (strcmp(commd.commd, "help") == 0) //����help����
            commd_help();
        else if (strcmp(commd.commd, "exit") == 0) //����exit����
        {
            exit(0);
            printf("лл��ʹ��ftpģ��ϵͳ\n");
        }
        else //�����������Ĵ���ʽ
            printf("����������������������!\n");
    }
    return 0;
}

//�г��ͻ��˵�ǰĿ¼�µ��ļ���Ŀ¼
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

int commd_lcd(char *arg) //�л��ͻ��˵�ǰ���ڵ�Ŀ¼
{
    int err;
    err = chdir(arg);
    if (err < 0)
        return -1;
    return 0;
}

int commd_lpwd() //��ӡ�ͻ��˵�ǰ����Ŀ¼����·����
{
    char buf[100];
    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;
}
int commd_lrm(char *arg) //ɾ����ǰ����Ŀ¼�µ�ָ���ļ�
{
    int err;
    err = remove(arg);
    if (err < 0)
        return -1;
    return 0;
}

// ʵ���ļ����ع���
void commd_get(struct sockaddr_in my_addr, char *arg)
{
    int fd;
    int sockfd;
    char buffer[N], commd[N];
    int nbytes;
    //�����׽��֣������д�����
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        exit(1);
    }
    //connect��������ʵ�ֿͻ��������˵�����,�˴��������˴�����
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        exit(1);
    }
    sprintf(commd, "get %s", arg);
    //ͨ��write���������˷�������
    if (write(sockfd, commd, N) < 0)
    {
        printf("Write Error!At commd_get 1\n");
        exit(1);
    }
    //����read���������ܷ���������������
    if (read(sockfd, buffer, N) < 0)
    {
        printf("Read Error!At commd_get 1\n");
        return;
    }
    //���ڼ����������ļ��Ƿ�򿪳ɹ�
    if (buffer[0] == 'N')
    {
        close(sockfd);
        printf("Can't Open The File!\n");
        return;
    }
    //open��������һ���ļ����ļ���ַΪ(commd+4)���õ�ַ�������������ȡ
    if ((fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        printf("Open Error!\n");
        exit(1);
    }
    //read�������׽����л�ȡN�ֽ����ݷ���buffer�У�����ֵΪ��ȡ���ֽ���
    while ((nbytes = read(sockfd, buffer, N)) > 0)
    {
        //write������buffer�е����ݶ�ȡ����д��fd��ָ����ļ�������ֵΪʵ��д����ֽ���
        if (write(fd, buffer, nbytes) < 0)
        {
            printf("Write Error!At commd_get 2");
        }
    }
    close(fd);
    close(sockfd);
    return;
}

//��ʾ������ļ��б�
void commd_ls(struct sockaddr_in my_addr, char *arg)
{
    int sockfd;
    char commd[N];
    //�����׽���
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
        printf("д�����\n");
        exit(1);
    }
    //����read���������ܷ���������������
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
    //�����׽���
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
        printf("д�����\n");
        return;
    }
    //����read���������ܷ���������������
    read(sockfd, commd, N);
    if (strncmp(commd, "0", 1) == 0)
        printf("�л��ɹ�\n");
    else
        printf("�л�ʧ��!\n");
}

void commd_pwd(struct sockaddr_in my_addr)
{
    int sockfd;
    char commd[N];
    //�����׽���
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
        printf("д�����\n");
        exit(1);
    }
    //����read���������ܷ���������������
    read(sockfd, commd, N);
    printf("%s\n", commd);
}

//ʵ���ϴ��ļ��Ĺ���
void commd_put(struct sockaddr_in my_addr, char *arg)
{
    int fd;
    int sockfd;
    char buffer[N], commd[N];
    int nbytes;
    //�����׽���
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Error!\n");
        exit(1);
    }
    //�ͻ�������������
    if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        printf("Connect Error!\n");
        exit(1);
    }
    sprintf(commd, "put %s", arg);
    //��commd�ж�ȡN�ֽ����ݣ�д���׽�����
    if (write(sockfd, commd, N) < 0)
    {
        printf("Wrtie Error!At commd_put 1\n");
        exit(1);
    }
    //open������(commd+4)�У���ȡ�ļ�·������ֻ���ķ�ʽ��
    if ((fd = open(arg, O_RDONLY)) < 0)
    {
        printf("Open Error!\n");
        exit(1);
    }
    //��fdָ����ļ��ж�ȡN���ֽ�����
    while ((nbytes = read(fd, buffer, N)) > 0)
    {
        //��buffer�ж�ȡnbytes�ֽ����ݣ�д���׽�����
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
    //�����׽���
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
        printf("д�����\n");
        return;
    }
    //����read���������ܷ���������������
    read(sockfd, commd, N);
    if (strncmp(commd, "0", 1) == 0)
        printf("ɾ���ɹ�!\n");
    else
        printf("ɾ��ʧ��!\n");
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
    printf("\t\t\t***********************ftp����һ��**************************************\n");
    printf("\t\t\t*                                                                      *\n");
    printf("\t\t\t*        <1>.ls      <�ļ���Ŀ¼>        �г�����˵�ǰ���ļ���Ŀ¼    *\n");
    printf("\t\t\t*        <2>.lls     <�ļ���Ŀ¼>        �г��ͻ��˵�ǰ���ļ���Ŀ¼    *\n");
    printf("\t\t\t*        <3>.rm	     <�ļ���Ŀ¼>        ɾ��������ļ�                *\n");
    printf("\t\t\t*        <4>.lrm     <�ļ���Ŀ¼>        ɾ���ͻ����ļ�                *\n");
    printf("\t\t\t*        <5>.cd         <Ŀ¼>           �л������Ŀ¼                *\n");
    printf("\t\t\t*        <6>.lcd        <Ŀ¼>           �л��ͻ���Ŀ¼                *\n");
    printf("\t\t\t*        <7>.get        <�ļ�>           ���ط�����ļ�                *\n");
    printf("\t\t\t*        <8>.put        <�ļ�>           ���ͻ����ļ��ϴ��������      *\n");
    printf("\t\t\t*        <9>.pwd	                 ��ӡ��ǰ���ڷ����Ŀ¼        *\n");
    printf("\t\t\t*        <10>.lpwd	                 ��ӡ��ǰ�ͻ�������Ŀ¼        *\n");
    printf("\t\t\t*        <12>.help	                 ��������鿴���������÷�    *\n");
    printf("\t\t\t*                                                ��ӭʹ��ftpģ��ϵͳ�� *\n");
    printf("\t\t\t***********************************************************************\n");
}