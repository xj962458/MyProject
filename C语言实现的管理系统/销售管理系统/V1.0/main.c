#include<x.h>
void main()
{
	int x;
	printf("==请选择所要运行的程序==\n");
	printf("===输入1求埃及分数======\n");
	printf("===输入2求分糖果次数====\n");
	printf("===输入3进入销售管理====\n");
	printf("======输入其他无效======\n");
	while(true){
		while(true){
		scanf("%d",&x);
		switch(x){
		case(1): aaa();break;  
		case(2): bbb();break;
		case(3): ccc();break;
		}
		break;
	}
}
