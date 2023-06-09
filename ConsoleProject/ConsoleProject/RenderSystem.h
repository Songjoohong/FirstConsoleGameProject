#pragma once
#include <Windows.h>

namespace render
{
	void InitScreen();
	void ScreenRelease();

	void ScreenFlipping();
	void ScreenClear();

	void ScreenDraw(int x, int y, const char c);
	void ScreenDraw(int x, int y, const char* pStr);
	void ScreenDraw2(int x, int y, const char* pStr);

	SMALL_RECT GetPlayerMovableRect();

	void DrawBorder();
}