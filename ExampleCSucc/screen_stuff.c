#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <conio.h>
#include <Windows.h>

#include "key_stuff.h"
#include "screen_stuff.h"

/*
	These numbers are from code page 437, *not* ASCII!
	Look at https://en.wikipedia.org/wiki/Code_page_437
	for documentation. CMD really is ancient I guess.
*/
const int idle_frame_data[9][9] = {
	{179, 47, 196, 92, -1},
	{219, 32, -1},
	{176, 177, 178, 219, 178, 177, 176, 32, -1},
	{220, 219, 223, 32, -1},
	{223, 219, 220, 32, -1},
	{222, 219, 221, 32, -1},
	{221, 219, 222, 32, -1},
	{192, 218, 191, 217, -1},
	{217, 191, 218, 192, -1}
};

//Awesome idle animations
void animate_idle(idle_types idle_type, int delay) {
	static int idle_timer;
	static int idle_frame;
	static idle_types previous_idle_type;
	if (idle_type != previous_idle_type) {
		idle_timer = 0;
		idle_frame = 0;
		previous_idle_type = idle_type;
	}
	if ((idle_timer / delay) == 1) {
		if (idle_frame_data[idle_type][idle_frame] == -1) {
			idle_frame = 0;
		}
		printf("%c\b", idle_frame_data[idle_type][idle_frame]);
		idle_frame++;
		idle_timer = 0;
	}
	else {
		idle_timer++;
	}
}

void adjustWindowSize(short width, short height) {
	SMALL_RECT test;

	HANDLE hStdout;
	COORD coord;
	BOOL ok;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = width;
	coord.Y = height;
	ok = SetConsoleScreenBufferSize(hStdout, coord);

	test.Left = 0;
	test.Top = 0;
	test.Right = coord.X - 1;
	test.Bottom = coord.Y - 1;

	SetConsoleWindowInfo(hStdout, ok, &test);

}

int menu_choice() {

	return 0;
}

///* Standard error macro for reporting API errors */
//#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line % d\n", __FILE__, GetLastError(), api, __LINE__);}
//
//void cls(HANDLE hConsole) {
//	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
//										cursor */
//	BOOL bSuccess;
//	DWORD cCharsWritten;
//	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
//	DWORD dwConSize;                 /* number of character cells in
//										the current buffer */
//
//										/* get the number of character cells in the current buffer */
//
//	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
//	PERR(bSuccess, "GetConsoleScreenBufferInfo");
//	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
//
//	/* fill the entire screen with blanks */
//
//	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
//		dwConSize, coordScreen, &cCharsWritten);
//	PERR(bSuccess, "FillConsoleOutputCharacter");
//
//	/* get the current text attribute */
//
//	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
//	PERR(bSuccess, "ConsoleScreenBufferInfo");
//
//	/* now set the buffer's attributes accordingly */
//
//	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
//		dwConSize, coordScreen, &cCharsWritten);
//	PERR(bSuccess, "FillConsoleOutputAttribute");
//
//	/* put the cursor at (0, 0) */
//
//	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
//	PERR(bSuccess, "SetConsoleCursorPosition");
//	return;
//}