/*输入字符串，并进行长度验证明，长度必须小于lens，*/
void stringinput(char *t,int lens,char *notice){
	char n[255];
	do{
		printf(notice);			/*显示提示信息*/
		scanf("%s",n);		/*输入字符串*/
		if (strlen(n)>lens)
		{
			/* code */
			printf("\n exceed the required length!\n");/*长度校验，超过lens值重新输入*/
		}
	}while(strlen(n)>lens);
	strcpy(t,n);		/*将输入字符串复制到字符串t中*/
}
 
/*输入数值浮点数，对数值检验后返回该值，数值必须大于等于0*/
float numberinput(char *notice){
	float t=0.00;
	do{
			printf(notice);/*显示提示信息*/
			scanf("%f",&t);
			if (t<0)
			{
				/* code */
				printf("\n score must>=0!\n");/*进行数值校验*/
			}
	}while(t<0);
	return t;
}
