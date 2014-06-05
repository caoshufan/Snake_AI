#include "head.h"

const TCHAR szWindowClass[] = L"AAAAA";
const TCHAR szWindowTitle[] = L"Snake-AI£¬·ÇSB°æ";

Game *pGame;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszClassName = szWindowClass;

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(szWindowClass,
		szWindowTitle,
		WS_OVERLAPPEDWINDOW,
		200, 100,
		WIDTH, HEIGH,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	pGame = new Game(hWnd, WIDTH, HEIGH);
	pGame->Init();

	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		pGame->Frame();
	}

	return msg.wParam;
}