#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "key_stuff.h"
#include "menu_stuff.h"

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

int menu_choice() {

	return 0;
}