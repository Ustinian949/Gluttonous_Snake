# define _CRT_SECURE_NO_WARNINGS

# include <stdio.h>
# include <stdlib.h>
# include "StartHome.h"
# include <time.h>
# include "Comman.h"

// 播放音乐用到
# include "resource.h" // 用到资源文件
# include <windows.h>
# include <MMSystem.h>
# pragma comment(lib,"winmm.lib")

void snake_pos_rand();
void DrawSnake();
void GameBackgroud2();
void SnakeMove();
void change_dir();
BOOL snake_die();
void fruits();
void snake_growup();
void Score();

int main(void)
{
	// 首页
	Home();
	// 音乐
	BGM();
	// 开始游戏
	startgame();
	// 清空首页
	system("cls");

	// 游戏开始蛇随机出现位置
	snake_pos_rand();
	GameBackgroud2();
	
	while (1)
	{
		system("cls");	
	// 果实
		fruits();
	// 蛇变长
		snake_growup();
	// 蛇的死亡判断
		if (false == snake_die())
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
			printf("就这？一顿操作猛如虎，分数不会超过5，最终分数为%d\n", snake_score);
			break;
		}
	// 游戏边框
		GameBackgroud2();
	// 蛇的方向变化
		change_dir();
	// 蛇的移动
		SnakeMove();
		Score();
		Sleep(500);
	}
	
	system("pause");
	return 0;
}


// 子程序

// 游戏边框背景
void GameBackgroud2(void)
{
	for (int i = 0; i < 20; i++)
	{
		printf("%s", back2[i]);
	}
}

// 游戏开始时蛇的随机位置
void snake_pos_rand(void)
{
	// 随机位置
	int nx = 0;
	int ny = 0;
	srand((unsigned int)time(NULL));
	nx = rand() % 19 + 1;
	ny = rand() % 18 + 1;

	// 初始化蛇的三个节点
	snake_arr[0][0] = ny;
	snake_arr[0][1] = nx*2;
	snake_arr[0][2] = to_west;

	snake_arr[1][0] = ny;
	snake_arr[1][1] = nx*2 +2;
	snake_arr[1][2] = to_west;

	snake_arr[2][0] = ny;
	snake_arr[2][1] = nx*2 + 4;
	snake_arr[2][2] = to_west;

	// 画蛇
	DrawSnake();
}

// 画蛇
void DrawSnake(void)
{ 
	for (int i = 0; snake_arr[i][0] != 0; i++)
	{
		strncpy(&back2[snake_arr[i][0]][snake_arr[i][1]], "■", 2);
	}
}

// 蛇的移动
void SnakeMove(void)
{
	// 去尾
	for (int i = 0; snake_arr[i][0] != 0; i++)
	{
		strncpy(&back2[snake_arr[i][0]][snake_arr[i][1]], "  ", 2);
	}

	int i = snake_length - 1;
	for (i; i >= 1; i--)
	{
		if (0 == snake_arr[i][0])
		{
			continue;
		}	
		snake_arr[i][0] = snake_arr[i - 1][0];
		snake_arr[i][1] = snake_arr[i - 1][1];
		snake_arr[i][2] = snake_arr[i - 1][2];
	}

	snake_arr[0][2] = snake_dir;
	if (to_west == snake_arr[0][2] || to_east == snake_arr[0][2])
	{
		snake_arr[0][1] += snake_arr[0][2];
	}
	else
	{
		snake_arr[0][0] += snake_arr[0][2];
	}
	// 画蛇
	DrawSnake();
}

// 蛇的方向变化
void change_dir(void)
{
	// 同步检测 _getch(); 每次都要按一次键
	// 异步检测
	if (GetAsyncKeyState('W'))
	{
		if (to_south != snake_arr[0][2])
		snake_dir = to_north;
	}
	if (GetAsyncKeyState('A'))
	{
		if (to_east != snake_arr[0][2])
		snake_dir = to_west;
	}
	if (GetAsyncKeyState('S'))
	{
		if (to_north != snake_arr[0][2])
		snake_dir = to_south;
	}
	if (GetAsyncKeyState('D'))
	{
		if (to_west != snake_arr[0][2])
		snake_dir = to_east;
	}
}

// 蛇的死亡判断
BOOL snake_die(void)
{
	if (to_west == snake_arr[0][2] || to_east == snake_arr[0][2])
	{
		if (0 == strncmp(&back2[snake_arr[0][0]][snake_arr[0][1] + snake_arr[0][2]], "■", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&back2[snake_arr[0][0] + snake_arr[0][2]][snake_arr[0][1]], "■", 2))
		{
			return false;
		}
	}
	return true;
}

// 果实的随机出现
void fruits(void)
{
	srand((unsigned int)time(NULL));

	if (fruits_go == false)
	{
		return ;
	}

	while (1)
	{ 
	BOOL flag = true;
	nx1 = rand() % 18 + 1;
	ny1 = rand() % 19 + 1;
	for (int i = 0; snake_arr[i][0] != 0; i++)
	{
		if (nx1 * 2 == snake_arr[i][1] && ny1 == snake_arr[i][0])
		{
			flag = false;
		}
	}
	if (flag == true)
	{
		break;
	}
	}

	strncpy(&back2[ny1][nx1*2], "★", 2);

	fruits_go = false;
}

// 蛇变长
void snake_growup(void)
{
	// 蛇头的坐标与果实相同
	if (nx1 * 2 == snake_arr[0][1] && ny1 == snake_arr[0][0])
	{
		//蛇变长
		if (to_east == snake_arr[snake_len][2])
		{
			snake_arr[snake_len + 1][0] = snake_arr[snake_len][0];
			snake_arr[snake_len + 1][1] = snake_arr[snake_len][1] - 2;
			snake_arr[snake_len + 1][2] = snake_arr[snake_len][2];
		}
		else if (to_west == snake_arr[snake_len][2])
		{
			snake_arr[snake_len + 1][0] = snake_arr[snake_len][0];
			snake_arr[snake_len + 1][1] = snake_arr[snake_len][1] + 2;
			snake_arr[snake_len + 1][2] = snake_arr[snake_len][2];
		}
		else if (to_north == snake_arr[snake_len][2])
		{
			snake_arr[snake_len + 1][0] = snake_arr[snake_len][0] + 1;
			snake_arr[snake_len + 1][1] = snake_arr[snake_len][1];
			snake_arr[snake_len + 1][2] = snake_arr[snake_len][2];
		}
		else if (to_south == snake_arr[snake_len][2])
		{
			snake_arr[snake_len + 1][0] = snake_arr[snake_len][0] - 1;
			snake_arr[snake_len + 1][1] = snake_arr[snake_len][1];
			snake_arr[snake_len + 1][2] = snake_arr[snake_len][2];
		}
		snake_len++;
		snake_score++;
		fruits_go = true;
	} 
}
// 分数
void Score(void)
{
	// 设置光标位置
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("分数");

	rd.X = 56;
	rd.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("%d", snake_score);
}