#ifndef AI_H
#define AI_H

#include "head.h"
//#define R 20
//#define C 20

struct BEAN
{
	int x, y;
};

class AI
{
public:
	AI(int, int );
	~AI();

	void CreateBean();
	bool isOK(int x, int y, int S[R][C]);
	bool isEat(int S[R][C]);
	void Move(int S[R][C]);
	void Move2(int S[R][C]);
	void Move3(int S[R][C]);
	void Find_Head(int S[R][C], int &x, int &y);
	void Find_Back(int S[R][C], int &x, int &y);
	void BFS(int S[R][C], int, int);

	void Draw(HDC);
	void Judge();

private:
	void init(int S[R][C]);

	int B[R][C];			//’Ê…ﬂ
	int virtual_B[R][C];	//–È…ﬂ

	int step[R][C];
	BEAN bean;

	int T;
	int len;

	int count;
};

#endif