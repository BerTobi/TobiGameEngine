/*
Tobi Console Game Engine

Version 0.1c

Provides basic functionalities to create a game in the system console.
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <Windows.h>
#include <Tchar.h>
#include <string.h>
#include <exception>


using namespace std;

class TobiGameEngine
{
public:
	TobiGameEngine()
	{
		nScreenWidth = 80;
		nScreenHeight = 30;

		wConsoleHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		rConsoleHnd = GetStdHandle(STD_INPUT_HANDLE);

		sConsoleTitle = L"Tobi Game Engine";

	}

	//Creates a Console
	int createConsole(wstring title, int width, int height, short nFontWidth = 8, short nFontHeight = 8)
	{
		CONSOLE_FONT_INFOEX fontInfo;

		fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		fontInfo.nFont = 0;
		fontInfo.dwFontSize.X = nFontWidth;
		fontInfo.dwFontSize.Y = nFontHeight;
		fontInfo.FontFamily = FF_DONTCARE;
		fontInfo.FontWeight = FW_NORMAL;
		wcscpy_s(fontInfo.FaceName, L"Consolas");

		if (!SetCurrentConsoleFontEx(wConsoleHnd, false, &fontInfo))
			throw new exception("Couldn't set font");

		sConsoleTitle = title;
		const wchar_t* cConsoleTitle = sConsoleTitle.c_str();

		SetConsoleTitle(cConsoleTitle);

		nScreenWidth = width;
		nScreenHeight = height;

		SMALL_RECT srMinimalWindowSize = { 0, 0, 1, 1 };
		
		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srMinimalWindowSize)) 
			return 1;

		COORD cLargestWindow = GetLargestConsoleWindowSize(wConsoleHnd);

		if (cLargestWindow.X == 0 && cLargestWindow.Y == 0)
			throw new exception("Unable to retrieve largest possible window coordinates");

		nScreenWidth = min(cLargestWindow.X, nScreenWidth);
		nScreenHeight = min(cLargestWindow.Y, nScreenHeight);

		COORD cBufferSize = { (short)nScreenWidth, (short)nScreenHeight };
		

		if (!SetConsoleScreenBufferSize(wConsoleHnd, cBufferSize)) 
			return 2;

		SMALL_RECT srWindowSize = { 0, 0, (nScreenWidth - 1), (nScreenHeight - 1) };

		if (!SetConsoleWindowInfo(wConsoleHnd, TRUE, &srWindowSize))
		{
			DWORD error = GetLastError();
			return error;
		}
		

		return 0;
	}

	//Write an screen buffer to screen from coordinates {0, 0}
	void writeToScreen(wchar_t* screen, int screenSize)
	{
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputCharacter(wConsoleHnd, screen, screenSize, { 0,0 }, &dwBytesWritten);
	}

	//Sets the time between game ticks in milliseconds
	void setGameTick(int nMilliseconds)
	{
		this_thread::sleep_for(chrono::milliseconds(nMilliseconds));
	}

	void setCursorVisibility(bool visible)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = visible;
		SetConsoleCursorInfo(out, &cursorInfo);
	}

protected:

	int nScreenWidth;
	int nScreenHeight;
	HANDLE wConsoleHnd;
	HANDLE rConsoleHnd;

	wstring sConsoleTitle;
};