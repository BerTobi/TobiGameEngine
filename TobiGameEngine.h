/*
Tobi Console Game Engine

Version 0.1b

Provides basic functionalities to create a game in the system console.
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <Windows.h>
#include <Tchar.h>
#include <string.h>


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
	int createConsole(wstring title, int width, int height)
	{
		sConsoleTitle = title;
		const wchar_t* cConsoleTitle = sConsoleTitle.c_str();

		SetConsoleTitle(cConsoleTitle);

		nScreenWidth = width;
		nScreenHeight = height;

		SMALL_RECT srWindowSize = { 0, 0, 1, 1 };

		SetConsoleWindowInfo(wConsoleHnd, TRUE, &srWindowSize);

		COORD cBufferSize = { (short)nScreenWidth, (short)nScreenHeight };

		SetConsoleScreenBufferSize(wConsoleHnd, cBufferSize);
		SetConsoleActiveScreenBuffer(wConsoleHnd);

		srWindowSize = { 0, 0, (short) (nScreenWidth - 1), (short)(nScreenHeight - 1) };

		SetConsoleWindowInfo(wConsoleHnd, TRUE, &srWindowSize);

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

protected:

	int nScreenWidth;
	int nScreenHeight;
	HANDLE wConsoleHnd;
	HANDLE rConsoleHnd;

	wstring sConsoleTitle;
};