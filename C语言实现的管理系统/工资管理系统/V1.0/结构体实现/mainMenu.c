//mainMenu.c
#pragma once
#include "preProcess.h"
/*主菜单界面*/
void menu(){
	system("cls");		/*调用Dos命令清屏*/
	//textcolor(10);		/*在文本模式中选择新的字符颜色*/
	//gotoxy(10,5);		/*在文本窗口中设置光标*/
	cprintf("	The employee's Salary Management System\n");
	//gotoxy(10,8);
	cprintf("	***************************Menu*******************************	\n");
	//gotoxy(10,9);
	cprintf("	*	1.input record		2.delete record		*\n");
	//gotoxy(10,10);
	cprintf("	*	3.search record		4.modify record		*\n");
	//gotoxy(10,11);
	cprintf("	*	5.insert record		6.count record		*\n");
	//gotoxy(10,12);
	/***/
	cprintf("	**************************************************************  \n");
}
