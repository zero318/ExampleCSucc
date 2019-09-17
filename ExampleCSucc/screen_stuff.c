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

COORD top_left = { 0, 0 };
void cls() {
	for (int i = 0; i < 42; i++) {
		printf("\n");
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), top_left);
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

int print_menu(const char *menu_title, const char *menu_items[], unsigned int number_of_menu_items) {
	printf("%s", menu_title);
	for (unsigned int i = 0; i < number_of_menu_items; i++) {
		printf(" %d. %s\n", i, menu_items[i]);
	}
	int selected_menu_index = 0;

	return selected_menu_index;
}