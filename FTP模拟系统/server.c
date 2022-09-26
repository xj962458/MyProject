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
#define N 256 //�ļ������������Ϊ256�ֽ�

//���������ṹ�壬��������Ͳ���
typedef struct command
{
    char commd[MAXDATASIZE];
    char arg[MAXDATASIZE];
} Commd;

// ����˺�������
void commd_ls(int sockfd, char *arg);  //��ʾ�ļ��б�
void commd_get(int sockfd, char *arg); //�����ļ�
void commd_put(int sockfd, char *arg); //�ϴ��ļ�
void commd_rm(int sockfd, char *arg);  //ɾ���ļ�
void commd_cd(int sockfd, char *arg);  //�л�����Ŀ¼
void commd_pwd(int sockfd);            //��ӡ��ǰ����Ŀ¼
int split(char *str, Commd *commd);    //�ָ�ͻ��˷�������Ϣ���������Ͳ���

int main(int arg, char *argv[])
{
    int ser_sockfd, cli_sockfd;
    pthread_t nid;
    struct sockaddr_in ser_addr, cli_addr;
    int ser_len, cli_len;
    char commd_str[N];
    Commd commd;
    bzero(commd_str, N); //��commd��ָ����ַ�����ǰN���ֽ���Ϊ0������'\0'

    if ((ser_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Sokcet Error!\n");
        return -1;
    }

    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //����ip��ַ
    ser_addr.sin_port = htons(8989);              //ת���������ֽ�
    ser_len = sizeof(ser_addr);
    //��ip��ַ���׽��ְ�
    if ((bind(ser_sockfd, (struct sockaddr *)&ser_addr, ser_len)) < 0)
    {
        perror("Bind Error!\n");
        return -1;
    }
    //�������˼���
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
        //�������˽������Կͻ��˵����ӣ�����һ���׽��֣����׽���Ϊ�½���һ���������ͻ��˵ĵ�ַ����Ϣ����cli_addr��
        //ԭ�����׽����Դ��ڼ�����
        if ((cli_sockfd = accept(ser_sockfd, (struct sockaddr *)&cli_addr, &cli_len)) < 0)
        {
            perror("��Ӧ����!\n");
            exit(1);
        }
        //���׽��ֽ�������ʱ���׽��ְѽ��յ����ݷ����׽��ֻ������������û���������Ǹ��Ƶ��û���������Ȼ����read������ȡ
        //write����ͬ��
        if (read(cli_sockfd, commd_str, N) < 0) //read������cli_sockfd�ж�ȡN���ֽ����ݷ���commd��
        {
            perror("��ȡ����!\n");
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
            printf("�������!\n");
    }
    return 0;
}
//�ָ�ͻ��˷�������Ϣ���������Ͳ���
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

// ��ʾ�ļ��б�
void commd_ls(int sockfd, char *arg)
{
    DIR *mydir = NULL;
    struct dirent *myitem = NULL;
    char commd[N];
    bzero(commd, N);
    //opendirΪ�����򿪲���name ָ����Ŀ¼, ������DIR*��̬��Ŀ¼��
    //mydir�д������Ŀ¼����Ϣ
    if ((mydir = opendir(arg)) == NULL)
    {
        perror("OpenDir Error!\n");
        exit(1);
    }

    while ((myitem = readdir(mydir)) != NULL) //������ȡĿ¼,������dirent�ṹ��ָ��
    {
        if (sprintf(commd, myitem->d_name, N) < 0) //���ļ���д��commdָ��Ļ�����
        {
            perror("Sprintf Error!\n");
            exit(1);
        }

        if (write(sockfd, commd, N) < 0) //��commd�����������ݷ��ͻ�client
        {
            perror("Write Error!\n");
            exit(1);
        }
    }

    closedir(mydir); //�ر�Ŀ¼��
    close(sockfd);
    return;
}

// ʵ���ļ�������
void commd_get(int sockfd, char *filename)
{
    int fd, nbytes;
    char buffer[N];
    bzero(buffer, N);
    printf("get filename : [ %s ]\n", filename);
    if ((fd = open(filename, O_RDONLY)) < 0) //��ֻ���ķ�ʽ��clientҪ���ص��ļ�
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
    buffer[0] = 'Y'; //�˴���ʾ���ļ���ȡ�ɹ�
    if (write(sockfd, buffer, N) < 0)
    {
        perror("Write Error! At commd_get 2!\n");
        close(fd);
        exit(1);
    }
    while ((nbytes = read(fd, buffer, N)) > 0) //���ļ����ݶ���buffer��
    {
        if (write(sockfd, buffer, nbytes) < 0) //��buffer���ͻ�client
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

// ʵ���ļ����ϴ�
void commd_put(int sockfd, char *filename)
{
    int fd, nbytes;
    char buffer[N];
    bzero(buffer, N);
    printf("get filename : [ %s ]\n", filename);
    if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) //��ֻд�ķ�ʽ���ļ������ļ���������գ����ļ����������½��ļ�
    {
        perror("���ļ�����!\n");
        return;
    }
    while ((nbytes = read(sockfd, buffer, N)) > 0) //��client���͵��ļ�д��buffer
    {
        if (write(fd, buffer, nbytes) < 0) //��buffer�е�����д���ļ���
        {
            perror("д�����!\n");
            close(fd);
            exit(1);
        }
    }
    close(fd);
    close(sockfd);
    return;
}

//ʵ�ַ��������ļ���ɾ��
void commd_rm(int sockfd, char *arg)
{
    int err;
    char buf[100];
    err = remove(arg);
    sprintf(buf, "%d", err);
    if (write(sockfd, buf, 100) < 0) //��commd�����������ݷ��ͻ�client
    {
        perror("д�����!\n");
        exit(1);
    }
}

// ʵ�ַ�������Ŀ¼���л�
void commd_cd(int sockfd, char *arg)
{
    int err;
    char buf[100];
    err = chdir(arg);
    sprintf(buf, "%d", err);
    if (write(sockfd, buf, 100) < 0) //��commd�����������ݷ��ͻ�client
    {
        perror("д�����!\n");
        exit(1);
    }
}

// ʵ�ִ�ӡ�������˵�ǰ����Ŀ¼
void commd_pwd(int sockfd)
{
    char buf[100];
    getcwd(buf, sizeof(buf));
    if (write(sockfd, buf, 100) < 0) //��commd�����������ݷ��ͻ�client
    {
        perror("д�����!\n");
        exit(1);
    }
}