#include "Game.h"

Game::Game(HWND hwnd, DWORD w, DWORD h)
{
	hWnd = hwnd;
	width = w;
	heigh = h;
	hdc = GetDC(hWnd);
	HBITMAP hTemp = CreateCompatibleBitmap(hdc, width, heigh);

	memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hTemp);
	DeleteObject(hTemp);
}

Game::~Game()
{
	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}

/***************************************
Init():
��Ҫ������ĳ�ʼ��������ͼƬ��
***************************************/
void Game::Init()
{
	srand(unsigned int(time(0)));

	t0 = GetTickCount();
	dir = 5;

	ai = new AI(0, 0);
}


void Game::Draw()
{
	//������,����
	ai->Draw(memDC);
}



void Game::DrawBackgroud()
{
	//���Ʊ�������
	SelectObject(memDC, (HBRUSH)GetStockObject(WHITE_BRUSH));
	Rectangle(memDC, 0, 0, BLOCK*R, BLOCK*C);
}

void Game::Updata()
{
	DrawBackgroud();
	Draw();
	BitBlt(hdc, 0, 0, width, heigh, memDC, 0, 0, SRCCOPY);
}

void Game::Frame()
{
	DWORD t1;
	t1 = GetTickCount();

	if (t1 - t0 >= 20)
	{
		ai->Judge();

		//���»���
		Updata();
		t0 = t1;
	}
}
