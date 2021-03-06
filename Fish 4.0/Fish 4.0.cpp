// Fish 4.0.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<conio.h>
#include <graphics.h>
#include<time.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 768
IMAGE background;
IMAGE img_p1 , img_p1bei;
IMAGE img_zha;
IMAGE img_zhabei;//炸弹图片
IMAGE img_f1;
IMAGE img_f1bei;//1号鱼图片
IMAGE img_f2;
IMAGE img_f2bei;//2号鱼图片
IMAGE img_f3;
IMAGE img_f3bei;//3号鱼图片
IMAGE img_f4;
IMAGE img_f4bei;//4号鱼图片
IMAGE img_bk0;  //进入界面图
struct yu
{
	double position_x;//横坐标
	double position_y;//纵坐标
	double v_x;//水平速度
	double v_y;//竖直速度
};
yu player;//玩家
yu zhadan;//炸弹
yu food1;//1号鱼
yu food2;//2号鱼
yu food3;//3号鱼
yu food4;//4号鱼
double  p1size;//玩家鱼的尺寸；
double  start_p1size;//玩家的初始大小；
char input;
int gameStatus = 0; // 游戏状态，0为选择界面，1为开始界面，2为结束游戏

#include "stdafx.h"
#include <conio.h>
#include <math.h>
#include <graphics.h>

void startMenu()
{
	putimage(0, 0, &img_bk0);//显示背景
	settextcolor(RGB(123, 90, 254));
	settextstyle(70, 0, _T("华文琥珀"));
	outtextxy(WINDOW_WIDTH * 0.36, WINDOW_HEIGHT * 0.15, _T("GREEDY FISH"));

	setbkmode(TRANSPARENT);
	settextcolor(RGB(106, 0, 0));
	settextstyle(37, 0, _T("幼圆"));
	//outtextxy(WINDOW_WIDTH*0.35, WINDOW_HEIGHT*0.36, _T("1. 新游戏"));
	//outtextxy(WINDOW_WIDTH*0.35, WINDOW_HEIGHT*0.44, _T("2. 退出游戏"));

	settextcolor(RGB(64, 0, 128));
	settextstyle(25, 0, _T("微软雅黑"));
	outtextxy(WINDOW_WIDTH*0.65, WINDOW_HEIGHT*0.75, _T("方向键控制"));
	outtextxy(WINDOW_WIDTH*0.65, WINDOW_HEIGHT*0.80, _T("限时内达到目标分"));
	outtextxy(WINDOW_WIDTH*0.65, WINDOW_HEIGHT*0.85, _T("一共三条生命"));
	outtextxy(WINDOW_WIDTH*0.65, WINDOW_HEIGHT*0.90, _T("撞大鱼以及碰炸弹将失去一条"));

	FlushBatchDraw();
	Sleep(2);

	if (_kbhit())//判断是否有输入
	{
		input = _getch();//根据用户的不同输入来移动
		if (input == ' ')
			gameStatus = 1;
	}
}

void startup()
{
	p1size = 60;//初始大小为60
	start_p1size = p1size;
	srand((unsigned)time(NULL));//随机数
	loadimage(&img_bk0, _T("enter.jpg"), 1200, 768, true);//进入界面
	loadimage(&background, _T("background.jpg"),1200,768,true);//背景
	loadimage(&img_zha, _T("zhadan1.jpg"), 50, 50, true);
	loadimage(&img_zhabei, _T("zhadan1bei.jpg"), 50, 50, true);//炸弹

	loadimage(&img_f1, _T("food1.jpg"), 45, 45, true);
	loadimage(&img_f1bei, _T("food1bei.jpg"), 45, 45, true);//1号鱼

	loadimage(&img_f2, _T("food2.jpg"), 80, 80, true);
	loadimage(&img_f2bei, _T("food2bei.jpg"), 80, 80, true);//2号鱼

	loadimage(&img_f3, _T("food3.jpg"), 110, 110, true);
	loadimage(&img_f3bei, _T("food3bei.jpg"), 110, 110, true);//3号鱼

	loadimage(&img_f4, _T("food4.jpg"), 130, 130, true);
	loadimage(&img_f4bei, _T("food4bei.jpg"));
	loadimage(&img_f4bei, _T("food4bei.jpg"));
	loadimage(&img_f4bei, _T("food4bei.jpg"), 130, 130, true);//4号鱼

	player.position_x = WINDOW_WIDTH / 2.0;//玩家横坐标
	player.position_y = WINDOW_HEIGHT / 2.0;//玩家纵坐标
	player.v_x = 0.8;//玩家水平速度
	player.v_y = 0.8;//玩家竖直速度

	zhadan.position_x = WINDOW_WIDTH + 500;//横坐标
	zhadan.position_y = rand() % 500;//纵坐标随机设定
	zhadan.v_x = 0.6;//速度

	food1.position_x = 0;//1号鱼横坐标
	food1.position_y = rand() % 400;//1号鱼纵坐标随机设定
	food1.v_x = 0.45;//1号鱼速度

	food2.position_x = -200;//2号鱼横坐标
	food2.position_y = rand() % 400;//2号鱼纵坐标随机设定
	food2.v_x = 0.45;//2号鱼速度

	food3.position_x = -500;//3号鱼横坐标
	food3.position_y = rand() % 400;//3号鱼纵坐标随机设定
	food3.v_x = 0.5;//3号鱼速度

	food4.position_x = -800;//4号鱼横坐标
	food4.position_y = rand() % 400;//4号鱼纵坐标随机设定
	food4.v_x = 0.5;//4号鱼速度

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//画面大小
	BeginBatchDraw();

	while (gameStatus == 0)
		startMenu();//初始菜单界面
}


void show()
{
	putimage(0, 0, &background);//显示背景
	loadimage(&img_p1, _T("player.jpg"), p1size, p1size, true);
	loadimage(&img_p1bei, _T("playerbei.jpg"), p1size, p1size, true);//玩家
	putimage(zhadan.position_x, zhadan.position_y, &img_zhabei, NOTSRCERASE);//显示炸弹
	putimage(zhadan.position_x, zhadan.position_y, &img_zha, SRCINVERT);

	putimage(food1.position_x, food1.position_y, &img_f1bei, NOTSRCERASE);//显示1号鱼
	putimage(food1.position_x, food1.position_y, &img_f1, SRCINVERT);

	putimage(food2.position_x, food2.position_y, &img_f2bei, NOTSRCERASE);//显示2号鱼
	putimage(food2.position_x, food2.position_y, &img_f2, SRCINVERT);

	putimage(food3.position_x, food3.position_y, &img_f3bei, NOTSRCERASE);//显示3号鱼
	putimage(food3.position_x, food3.position_y, &img_f3, SRCINVERT);

	putimage(food4.position_x, food4.position_y, &img_f4bei, NOTSRCERASE);//显示4号鱼
	putimage(food4.position_x, food4.position_y, &img_f4, SRCINVERT);

	putimage(player.position_x, player.position_y, &img_p1bei, NOTSRCERASE);//显示玩家
	putimage(player.position_x, player.position_y, &img_p1, SRCINVERT);

	FlushBatchDraw();
}

void updateWithoutInput()
{
	zhadan.position_x = zhadan.position_x - zhadan.v_x;//向左移动
	food1.position_x = food1.position_x + food1.v_x;//1号鱼向右移动
	food2.position_x = food2.position_x + food2.v_x;//2号鱼向右移动
	food3.position_x = food3.position_x + food3.v_x;//3号鱼向右移动
	food4.position_x = food4.position_x + food4.v_x;//4号鱼向右移动
	if (zhadan.position_x <= 0)
	{
		zhadan.position_x = 5000;
		zhadan.position_y = rand() % 500;//重复出现
	}
	if (food1.position_x >= WINDOW_WIDTH)
	{
		food1.position_x = -400;
		food1.position_y = rand() % 400;//1号鱼重复出现
	}
	if (food2.position_x >= WINDOW_WIDTH)
	{
		food2.position_x = -900;
		food2.position_y = rand() % 400;//2号鱼重复出现
	}
	if (food3.position_x >= WINDOW_WIDTH)
	{
		food3.position_x = -1500;
		food3.position_y = rand() % 400;//3号鱼重复出现
	}
	if (food4.position_x >= WINDOW_WIDTH)
	{
		food4.position_x = -1800;
		food4.position_y = rand() % 400;//4号鱼重复出现
	}
	if ((zhadan.position_x + 25 >= player.position_x + 20 && zhadan.position_x + 25 <= player.position_x + p1size) && (zhadan.position_y + 25 >= player.position_y + 20 && zhadan.position_y + 25 <= player.position_y + p1size))
	{
		zhadan.position_x = 4000;
		zhadan.position_y = rand() % 500;//玩家吃掉炸弹
	}

	if (food1.position_x + 25.5>player.position_x && food1.position_x + 25.5<player.position_x + p1size && food1.position_y + 25.5>player.position_y && food1.position_y + 25.5<player.position_y + p1size)
		//判断一号鱼是否被吃。判断条件为一号鱼的中心坐标在玩家一内部即被吃
	{
		p1size += 5;
		food1.position_x = -400;
		food1.position_y = rand() % (WINDOW_HEIGHT - 45);//小鱼被吃，重新随机生成
	}
	if (p1size>80)
	{
		if (food2.position_x + 40>player.position_x && food2.position_x + 40<player.position_x + p1size && food2.position_y + 40>player.position_y && food2.position_y + 40<player.position_y + p1size)
		{
			p1size += 7;
			food2.position_x = -900;
			food2.position_y = rand() % (WINDOW_HEIGHT - 80);
		}

	}
	else
	{
		if (player.position_x + p1size / 2.0>food2.position_x && player.position_x + p1size / 2.0<food2.position_x + 80 && player.position_y + p1size / 2.0>food2.position_y && player.position_y + p1size / 2.0<food2.position_y + 80)
		{
			p1size = start_p1size;
			player.position_x = rand() % (WINDOW_WIDTH - 60);//出现在随机位置
			player.position_y = rand() % (WINDOW_HEIGHT - 60);
		}
	}
	//玩家与比自身大的鱼相撞，大小回到初始状态；并随机在其他地方生成；

	if (p1size>110)
	{
		if (food3.position_x + 55.5>player.position_x && food3.position_x + 55.5<player.position_x + p1size && food3.position_y + 55.5>player.position_y && food3.position_y + 55.5<player.position_y + p1size)
		{
			p1size += 9;
			food3.position_x = -1500;
			food3.position_y = rand() % (WINDOW_HEIGHT - 110);
		}
	}
	else
	{
		if (player.position_x + p1size / 2.0>food3.position_x && player.position_x + p1size / 2.0<food3.position_x + 110 && player.position_y + p1size / 2.0>food3.position_y && player.position_y + p1size / 2.0<food3.position_y + 110)
		{
			p1size = start_p1size;
			player.position_x = rand() % (WINDOW_WIDTH - 60);//出现在随机位置
			player.position_y = rand() % (WINDOW_HEIGHT - 60);
		}
	}
	if (p1size>130)
	{
		if (food4.position_x + 65>player.position_x && food4.position_x + 65<player.position_x + p1size && food4.position_y + 65>player.position_y && food4.position_y + 65<player.position_y + p1size)
		{
			p1size += 11;
			food4.position_x = -1800;
			food4.position_y = rand() % (WINDOW_HEIGHT - 130);
		}

	}
	else
	{
		if (player.position_x + p1size / 2.0>food4.position_x && player.position_x + p1size / 2.0<food4.position_x + 130 && player.position_y + p1size / 2.0>food4.position_y && player.position_y + p1size / 2.0<food4.position_y + 130)
		{
			p1size = start_p1size;
			player.position_x = rand() % (WINDOW_WIDTH - 60);//出现在随机位置
			player.position_y = rand() % (WINDOW_HEIGHT - 60);
		}
	}
}

void updateWithInput()
{
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && (player.position_x>0))
		player.position_x = player.position_x - player.v_x;  //左移
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (player.position_x<WINDOW_WIDTH - 80))
		player.position_x = player.position_x + player.v_x;  //右移
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && player.position_y>0)
		player.position_y = player.position_y - player.v_y;  //上移
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && player.position_y<WINDOW_HEIGHT - 80)
		player.position_y = player.position_y + player.v_y;  //下移

}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main()
{
	startup();
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	gameover();
	return 0;
}