#ifndef GAME_H
#define GAME_H

#include "head.h"
class AI;

class Game
{
public:
	Game(HWND, DWORD, DWORD);
	~Game();


	void Init();
	void Frame();
	void Updata();
	void Draw();
	void DrawBackgroud();

private:
	HDC memDC;
	HDC hdc;

	HWND hWnd;
	DWORD width;
	DWORD heigh;

	DWORD t0;

	int dir;

	AI *ai;
};

#endif