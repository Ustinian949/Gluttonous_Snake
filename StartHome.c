# include <stdio.h>
# include <stdlib.h>
# include <conio.h> // _getch()
# include "StartHome.h"

// ���������õ�
# include "resource.h" // �õ���Դ�ļ�
# include <windows.h>
# include <MMSystem.h>
# pragma comment(lib,"winmm.lib")

// ��ҳ
void Home(void)
{
	printf("\n\n");
	printf("\t  <HI, �����ǣ���ӭ��������������>\n\n");
	printf("\t          �����ո�ʼ��Ϸ��\n");
	printf("\t     ��WASD���Ʒ���ע���дŶ����\n");
}

// BGM
void BGM(void)
{
	// ͨ��·��������֣���ִ���ļ�.exe�Ƚ�С�������滻���֣�����Ը�
	//PlaySound("H:\\�һ�����\\Shape of You��101�棩.wav", NULL, SND_FILENAME | SND_ASYNC);  // ����·��
	//PlaySound("Shape of You��101�棩.wav", NULL, SND_FILENAME | SND_ASYNC); // ���·��

	// ͨ�������Դ�ļ�����ִ���ļ�.exe�󣬲����滻
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
}

// �����⣬���ո�ʼ��Ϸ������ֹͣ
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