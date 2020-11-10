# define _CRT_SECURE_NO_WARNINGS

# include <stdio.h>
# include <stdlib.h>
# include "StartHome.h"
# include <time.h>
# include "Comman.h"

// ���������õ�
# include "resource.h" // �õ���Դ�ļ�
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
	// ��ҳ
	Home();
	// ����
	BGM();
	// ��ʼ��Ϸ
	startgame();
	// �����ҳ
	system("cls");

	// ��Ϸ��ʼ���������λ��
	snake_pos_rand();
	GameBackgroud2();
	
	while (1)
	{
		system("cls");	
	// ��ʵ
		fruits();
	// �߱䳤
		snake_growup();
	// �ߵ������ж�
		if (false == snake_die())
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
			printf("���⣿һ�ٲ������绢���������ᳬ��5�����շ���Ϊ%d\n", snake_score);
			break;
		}
	// ��Ϸ�߿�
		GameBackgroud2();
	// �ߵķ���仯
		change_dir();
	// �ߵ��ƶ�
		SnakeMove();
		Score();
		Sleep(500);
	}
	
	system("pause");
	return 0;
}


// �ӳ���

// ��Ϸ�߿򱳾�
void GameBackgroud2(void)
{
	for (int i = 0; i < 20; i++)
	{
		printf("%s", back2[i]);
	}
}

// ��Ϸ��ʼʱ�ߵ����λ��
void snake_pos_rand(void)
{
	// ���λ��
	int nx = 0;
	int ny = 0;
	srand((unsigned int)time(NULL));
	nx = rand() % 19 + 1;
	ny = rand() % 18 + 1;

	// ��ʼ���ߵ������ڵ�
	snake_arr[0][0] = ny;
	snake_arr[0][1] = nx*2;
	snake_arr[0][2] = to_west;

	snake_arr[1][0] = ny;
	snake_arr[1][1] = nx*2 +2;
	snake_arr[1][2] = to_west;

	snake_arr[2][0] = ny;
	snake_arr[2][1] = nx*2 + 4;
	snake_arr[2][2] = to_west;

	// ����
	DrawSnake();
}

// ����
void DrawSnake(void)
{ 
	for (int i = 0; snake_arr[i][0] != 0; i++)
	{
		strncpy(&back2[snake_arr[i][0]][snake_arr[i][1]], "��", 2);
	}
}

// �ߵ��ƶ�
void SnakeMove(void)
{
	// ȥβ
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
	// ����
	DrawSnake();
}

// �ߵķ���仯
void change_dir(void)
{
	// ͬ����� _getch(); ÿ�ζ�Ҫ��һ�μ�
	// �첽���
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

// �ߵ������ж�
BOOL snake_die(void)
{
	if (to_west == snake_arr[0][2] || to_east == snake_arr[0][2])
	{
		if (0 == strncmp(&back2[snake_arr[0][0]][snake_arr[0][1] + snake_arr[0][2]], "��", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&back2[snake_arr[0][0] + snake_arr[0][2]][snake_arr[0][1]], "��", 2))
		{
			return false;
		}
	}
	return true;
}

// ��ʵ���������
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

	strncpy(&back2[ny1][nx1*2], "��", 2);

	fruits_go = false;
}

// �߱䳤
void snake_growup(void)
{
	// ��ͷ���������ʵ��ͬ
	if (nx1 * 2 == snake_arr[0][1] && ny1 == snake_arr[0][0])
	{
		//�߱䳤
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
// ����
void Score(void)
{
	// ���ù��λ��
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("����");

	rd.X = 56;
	rd.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("%d", snake_score);
}