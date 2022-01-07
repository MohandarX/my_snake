#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define snake_max 500
char mode;//��Ϸģʽ
bool end;
enum DIR
{
	up,
	down,
	left,
	right,
};
struct Snake//�ߵĽṹ��
{
	int size;//�ߵĽ���(����Բ)
	int dir;//�ߵĳ���
	int speed;//���ж����ٶ�
	POINT zb[snake_max];//�ߵ�����
}snake;
struct Food
{
	int x;//ʳ�������
	int y;//ʳ��������
	int r;//ʳ���С�뾶
	DWORD color;//ʳ����ɫ
	bool flag;//ʳ���Ƿ񱻳ԣ�����Ϊ�棬û�б���Ϊ��
}food;
void menu()
{
	initgraph(640, 480);//��������
	setbkcolor(RGB(99, 221, 96));//���ô�����ɫ
	cleardevice();//�����ɫ
	settextcolor(RED);//����������ɫ
	settextstyle(30,0,"΢���ź�");//����������ʽ
	outtextxy(260, 50, "̰������Ϸ");
	outtextxy(350, 90, "By:Shiki & ZeroTwo");
	outtextxy(275, 130, "0.play");
	outtextxy(275, 170, "1.exit");
	char stk = _getch();
	switch (stk)
	{
	case '0':return;
	case '1':exit(0);
	}
}
void game_mode()
{
	initgraph(640, 480);//��������
	setbkcolor(RGB(99, 221, 96));//���ô�����ɫ
	cleardevice();//�����ɫ
	settextcolor(RED);//����������ɫ
	settextstyle(30,0,"΢���ź�");//����������ʽ
	outtextxy(260, 50, "��ѡ���Ƿ���Χǽ");
	outtextxy(260, 90, "0.��");
	outtextxy(260, 130, "1.��");
	mode = _getch();
}
void gameinit()//�����ʼ��
{
	srand(GetTickCount());
	initgraph(640, 480);//��������
	snake.size = 3;
	snake.speed = 10;
	snake.dir = right;
	for (int i = 0; i <= snake.size; i++)
	{
		snake.zb[i].x = 60 - i * 10;
		snake.zb[i].y = 20;
	}
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = 8;
	food.flag = true;
}
void drawinit()//��ͼ
{
	BeginBatchDraw();//��ʼ˫�����ͼ
	setbkcolor(RGB(99, 221, 96));//���ô�����ɫ
	cleardevice();//�����ɫ
	//�����ߵ���ɫ
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++)//����
	{
		solidcircle(snake.zb[i].x, snake.zb[i].y, 5);
	}
	if (food.flag)//��ʳ��
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();//����˫�����ͼ
}
bool game_over()
{
	settextcolor(RED);
	outtextxy(50, 50, "Game Over");
	outtextxy(50, 70, "0.���ز˵�");
	outtextxy(50, 90, "1.�˳���Ϸ");
	while (1)
	{
		char flag = _getch();
		switch (flag)
		{
		case '0':return TRUE;
		case '1':exit(0);
		}
	}
}
void snakemove()
{
	for (int i = snake.size - 1; i > 0; i--)//�����������ͷ�ƶ�
	{
		snake.zb[i] = snake.zb[i - 1];//ÿһ��Ҫ�ƶ�������Ϊ��һ�ڵ�����
	}
	switch (snake.dir)//��ͷ�ƶ�
	{
	case right:
		snake.zb[0].x += snake.speed;
		if (snake.zb[0].x >= 640)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if(mode == '1')
			{
				snake.zb[0].x = 0;
			}
		}
		break;
	case left:
		snake.zb[0].x -= snake.speed;
		if (snake.zb[0].x <= 0)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if (mode == '1')
			{
				snake.zb[0].x = 640;
			}
		}
		break;
	case up:
		snake.zb[0].y -= snake.speed;
		if (snake.zb[0].y <= 0)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if (mode == '1')
			{
				snake.zb[0].y = 480;
			}
		}
		break;
	case down:
		snake.zb[0].y += snake.speed;
		if (snake.zb[0].y >= 480)
		{
			if (mode == '0')
			{
				end = game_over();
			}
			else if (mode == '1')
			{
				snake.zb[0].y = 0;
			}
		}
		break;
	}
}
void control()//���̸ı��ߵķ���
{
	if (_kbhit())//������˽�_kbhit()������
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != down)
			{
				snake.dir = up;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != up)
			{
				snake.dir = down;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != right)
			{
				snake.dir = left;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != left)
			{
				snake.dir = right;
			}
			break;
		}
	}
}
void eatfood()
{
	if (food.flag == true && snake.zb[0].x >= food.x - food.r && snake.zb[0].x <= food.x + food.r && snake.zb[0].y >= food.y - food.r && snake.zb[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)//���ʳ����ʧ���ٴ���һ���µ�ʳ��
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = 8;
		food.flag = true;
	}
}
void pause()//��ͣ����
{
	if (_kbhit())
	{
		if (_getch() == ' ')
		{
			while (_getch() != ' ');
		}
	}
}
void eatself()
{
	for (int k = 1; k < snake.size; k++)
	{
		if (snake.zb[0].x >= snake.zb[k].x - 5 && snake.zb[0].x <= snake.zb[k].x + 5 && snake.zb[0].y >= snake.zb[k].y - 5 && snake.zb[0].y <= snake.zb[k].y + 5)
		{
			end = game_over();
		}
	}
}
void game()
{
	end = FALSE;
	gameinit();
	while (1)
	{
		drawinit();
		eatfood();
		eatself();
		if (end)
		{
			break;
		}
		pause();
		snakemove();
		if (end)
		{
			break;
		}
		control();
		Sleep(100);
	}
}