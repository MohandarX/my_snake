#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//��Ŀ����:̰����
//����:Shiki & ZeroTwo
//ע������:�ó�����C���Ա�д,����ͼ�ο���ҪeasyX��֧��,�����޷�����,������VS2022�±��룬������֧�����ϼ���
//         easyXͼ�ο�������վ:    https://easyx.cn/

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