#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//项目名称:贪吃蛇
//作者:Shiki & ZeroTwo
//注意事项:该程序由C语言编写,运行图形库需要easyX的支持,否则无法编译,程序在VS2022下编译，理论上支持向上兼容
//         easyX图形库下载网站:    https://easyx.cn/

void game();
void menu();
void game_mode();
int main()
{
	while (1)
	{
		menu();
		game_mode();
		game();
	}
	return 0;
}