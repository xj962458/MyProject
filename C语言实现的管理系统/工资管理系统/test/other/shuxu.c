#include<stdio.h>
typedef struct student
{
    char name[20];
    int age;
}STU;

int main()
{
    STU student1,*p=&student1;
    p->age=18;
    scanf("%s",p->name);
    printf("%s\n",p->name);
    printf("%d",p->age);
    printf("\n%d",p->age+1);
    printf("\n%d",(p->age)+1);
    return 0;
}
