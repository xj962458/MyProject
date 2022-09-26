//out.c
#pragma once
#include "preProcess.h"
/*printheader()函数用于在屏幕上以表格形式显示记录。记录的显示经常要进行，因此单独设置
printheader()函数，便于其他模块调用，减少代码的重复
*/
void printheader(){
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}
 
void PRINTdata(ZGGZ pp){/*格式化输出表中数据*/
	ZGGZ *p;
	p=&pp;
	printf(FORMAT,DATA);
}
void disp(ZGGZ tp[],int n){/*显示数组tp[]中存储的记录，内容为*/
	int i;
	if (n==0)
	{
		/* code */
		printf("\n========>No employees record!\n");
		getchar();
		return ;
	}
	printf("\n\n");
	printheader();		/*输出表格头部*/
	i=0;
	while(i<n){	/*逐条输出数组中存储的员工信息*/
		PRINTdata(tp[i]);
		i++;
		printf(HEADER3);
	}
	getchar();
}
 
void wrong(){	/*输出按键错误信息*/
	printf("\n\n\n\n*******Error:input has wrong!press any key to continue*******\n");
	getchar();
}
void nofind(){	/*输出未查找到此员工的信息*/
	printf("\n====>Not find this employee record!\n");
}
