//save.c
#pragma once
#include "preProcess.h"
extern int saveflag;				/*需要存盘的标志变量*/
/*存储记录*/
void save(ZGGZ tp[],int n){
	FILE *fp;
	int i=0;
	fp=fopen("E:\zggz\gzgl.data","wb");
	if (fp==NULL)
	{
		/* code */
		printf("\n=======>open file error!\n");;
		getchar();
		return ;
	}
	for (i = 0; i < n; ++i)
	{
		/* code */
		if (fwrite(&tp[i],sizeof(ZGGZ),1,fp)==1)	/*每次写一条记录或一个结构数组元素到文件中草药*/
		{
			/* code */
			continue;
		}
		else
			break;
	}
	if (i>0)
	{
		/* code */
		getchar();
		printf("\n\n===========>save file complete,total saved's record number is :%d\n",i);
		getchar();
		saveflag=0;
	}
	else
	{
		system("cls");
		printf("the current link is empty,no employee record is saved!\n");
		getchar();
	}
	fclose(fp);
}
