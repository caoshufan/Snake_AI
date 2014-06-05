#include "AI.h"

AI::AI(int x, int y)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			B[i][j] = -INF;
		}
	}

	B[1][0] = 0;
	B[0][0] = -1;

	T = 0;
	len = 2;

	srand(time(0));
	bean.x = rand() % R;
	bean.y = rand() % C;

	count = 0;
}

AI::~AI()
{
}

bool AI::isOK(int x, int y, int S[R][C])
{
	return (x >= 0 && x < R && y >= 0 && y < C && !(T-S[x][y]<len-1));
}

void AI::CreateBean()
{
	if (len == R*C)
	{
		MessageBox(NULL, L"Win", NULL, MB_OK);
		exit(0);
	}
	int Ex, Ey;
	Find_Back(B,Ex, Ey);
	bean.x = rand() % R;
	bean.y = rand() % C;
	while (!isOK(bean.x, bean.y, B) || (Ex == bean.x && Ey == bean.y))
	{
		bean.x = rand() % R;
		bean.y = rand() % C;
	}
}

void AI::Draw(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, bean.x*BLOCK, bean.y*BLOCK, (bean.x + 1)*BLOCK, (bean.y + 1)*BLOCK);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(hdc, brush);
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (T - B[i][j] < len)
				Rectangle(hdc, i*BLOCK, j*BLOCK, (i + 1)*BLOCK, (j + 1)*BLOCK);
		}
	}
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 0, 255));
	SelectObject(hdc, brush);
	int x, y;
	Find_Head(B, x, y);
	Rectangle(hdc, x*BLOCK, y*BLOCK, (x + 1)*BLOCK, (y + 1)*BLOCK);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(255,255, 0));
	SelectObject(hdc, brush);
	Find_Back(B, x, y);
	Rectangle(hdc, x*BLOCK, y*BLOCK, (x + 1)*BLOCK, (y + 1)*BLOCK);

	DeleteObject(brush);
}

void  AI::Find_Head(int S[R][C], int &x, int &y)
{
	int tmp = -INF;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < R; j++)
		{
			if (tmp < S[i][j])
			{
				x = i;
				y = j;
				tmp = S[i][j];
			}
		}
	}
}

void AI::Find_Back(int S[R][C], int &x, int &y)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < R; j++)
		{
			if (T - S[i][j] == len - 1)
			{
				x = i;
				y = j;
			}
		}
	}
}

void AI::init(int S[R][C])
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			S[i][j] = INF;
		}
	}
}

void AI::Move(int S[R][C])
{
	int x, y, t= -1;
	Find_Head(S, x, y);

	int Min = INF;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isOK(nx, ny, S) && step[nx][ny] < Min)
		{
			Min = step[nx][ny];
			t = i;
		}
	}
	if (t == -1)	return;
	int nx = x + dx[t];
	int ny = y + dy[t];

	S[nx][ny] = S[x][y] + 1;
	T++;
}


void AI::Move2(int S[R][C])
{
	int x, y, t = -1;
	Find_Head(S, x, y);
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isOK(nx, ny, S))
		{
			t = i;
			break;
		}
	}

	if (t == -1)	return;
	int nx = x + dx[t];
	int ny = y + dy[t];

	S[nx][ny] = S[x][y] + 1;
	T++;
}

void AI::Move3(int S[R][C])
{
	int x, y, t = -1;
	Find_Head(S, x, y);

	int Max = -INF;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isOK(nx, ny, S) && step[nx][ny]!=INF && step[nx][ny] > Max)
		{
			Max = step[nx][ny];
			t = i;
		}
	}

	if (t == -1)	return;
	int nx = x + dx[t];
	int ny = y + dy[t];

	S[nx][ny] = S[x][y] + 1;
	T++;
}


bool AI::isEat(int S[R][C])
{
	int x, y;
	Find_Head(S, x, y);

	if (x == bean.x && bean.y == y)
	{
		return true;
	}
	return false;
}

void AI::BFS(int S[R][C], int x, int y)
{
	queue<POINTS> q;
	init(step);
	step[x][y] = 0;
	q.push(POINTS{ x, y });

	while (!q.empty())
	{
		POINTS next, now;
		now = q.front();	q.pop();
		for (int i = 0; i < 4; i++)
		{
			next = now;
			next.x += dx[i];
			next.y += dy[i];
			int p = step[now.x][now.y] + 1;
			if (isOK(next.x, next.y, S) && p < step[next.x][next.y])
			{
				step[next.x][next.y] = p;
				q.push(next);
			}
		}
	}

}

void AI::Judge()
{
	memcpy(virtual_B, B, sizeof(B));
	int Fx, Fy, Ex, Ey;
	int tmp_T = T;

	int flag1 = 0, flag2 = 0;

	Find_Head(virtual_B, Fx, Fy);
	BFS(virtual_B, Fx, Fy);
	if (step[bean.x][bean.y] < INF)
	{
		flag1 = 1;

		BFS(virtual_B, bean.x, bean.y);
		while (!isEat(virtual_B))
		{
			Move(virtual_B);
		}
		len++;
		Find_Head(virtual_B, Fx, Fy);
		Find_Back(virtual_B, Ex, Ey);
		BFS(virtual_B, Fx, Fy);
		if (step[Ex][Ey] < INF)	flag2 = 1;
		T = tmp_T;
		len--;
	}

	if (flag1 && flag2)
	{
		BFS(B, bean.x, bean.y);
		Move(B);
		count++;
	}
	else
	{
		Find_Back(B, Ex, Ey);
		BFS(B, Ex, Ey);
		Move3(B);
		count++;
	}
	if (isEat(B))
	{
		len++;
		CreateBean();
		count = 0;
	}

	if (count >= 2 * R*C)
	{
		MessageBox(NULL, L"À¿—≠ª∑", NULL, MB_OK);
		exit(0);
	}
}