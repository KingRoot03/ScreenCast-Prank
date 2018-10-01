#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>

using namespace std;

int ScreenWidth, ScreenHeight;
int Interval = 100;

LRESULT CALLBACK Melter(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
	{
		HDC Desktop = GetDC(HWND_DESKTOP);
		HDC Window = GetDC(hWnd);

		BitBlt(Window, 0, 0, ScreenWidth, ScreenHeight, Desktop, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, Window);
		ReleaseDC(HWND_DESKTOP, Desktop);

		SetTimer(hWnd, 0, Interval, 0);
		ShowWindow(hWnd, SW_SHOW);
		break;
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);
		break;
	}
	case WM_TIMER:
	{
		HDC Window = GetDC(hWnd);
		int X = (rand() % ScreenWidth) - (150 / 2),
			Y = (rand() % 15),
			Width = (rand() % 150);
		BitBlt(Window, X, Y, Width, ScreenHeight, Window, X, 0, SRCCOPY);
		ReleaseDC(hWnd, Window);
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}
	return 0;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int main(HINSTANCE Inst, HINSTANCE Prev, LPSTR Cmd, int showcmd)
{
	// Prende la grandezza dello schermo
	ScreenWidth = 550;
	ScreenHeight = 500;

	WNDCLASS wndClass = { 0, Melter, 0,0, Inst, 0, LoadCursorW(0, IDC_ARROW), 0, 0, L"PP" };

	if (RegisterClass(&wndClass))
	{
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "PP", 0, WS_POPUP,
									0, 0, ScreenWidth, ScreenHeight, HWND_DESKTOP, 0, Inst, 0);
		if (hWnd)
		{
			srand(GetTickCount());
			MSG Msg = { 0 };

			while (Msg.message != WM_QUIT)
			{
				if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
			}
		}
	}
	return 0;
}
