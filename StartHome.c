# include <stdio.h>
# include <stdlib.h>
# include <conio.h> // _getch()
# include "StartHome.h"

// 播放音乐用到
# include "resource.h" // 用到资源文件
# include <windows.h>
# include <MMSystem.h>
# pragma comment(lib,"winmm.lib")

// 首页
void Home(void)
{
	printf("\n\n");
	printf("\t  <HI, 铁子们，欢迎进入大蛇丸的世界>\n\n");
	printf("\t          【按空格开始游戏】\n");
	printf("\t     【WASD控制方向（注意大写哦）】\n");
}

// BGM
void BGM(void)
{
	// 通过路径添加音乐，可执行文件.exe比较小，可以替换音乐，灵活性高
	//PlaySound("H:\\煲机音乐\\Shape of You（101版）.wav", NULL, SND_FILENAME | SND_ASYNC);  // 绝对路径
	//PlaySound("Shape of You（101版）.wav", NULL, SND_FILENAME | SND_ASYNC); // 相对路径

	// 通过添加资源文件，可执行文件.exe大，不可替换
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
}

// 输入检测，按空格开始游戏，音乐停止
void startgame(void)
{
	while (1)
	{
		char Input;
		Input = _getch();
		if (' ' == Input)
		{
			break;
		}
	}
	PlaySound(NULL, 0, 0);
}