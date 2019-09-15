/*
	Example C Program
	8/26/2019
	
	Wassup, it's ya boi skinny comment.

	This program is intended to conform to the specifications
	of the C language as defined by the C11 standard!
	If your compile doesn't support C11 features, go away.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
//#include <thread.h>

/*
	This is a nonstandard header included with Windows.
	It allows reading keyboard input without pressing enter,
	testing whether a key has been pressed, and converting
	scan codes to legible characters. Kind of sucks that C
	doesn't let you do that normally. Even LC-3 did.
*/
#include <conio.h>

#include "key_stuff.h"
#include "menu_stuff.h"
#include "main_game.h"

//int ChrisSucc() {
//	char InputCharrot;
//	scanf("%c", &InputCharrot);
//	if ((65 <= InputCharrot) && (InputCharrot <= 90)) {
//		int Spaces;
//		int PrintCharrot = 64;
//		for (int CurrentCharrot = 65; CurrentCharrot <= InputCharrot; CurrentCharrot++) {
//			for (Spaces = InputCharrot - CurrentCharrot; Spaces > 0; Spaces--) {
//				printf(" ");
//			}
//			for (PrintCharrot++; PrintCharrot < CurrentCharrot; PrintCharrot++) {
//				printf("%c", PrintCharrot);
//			}
//			for (PrintCharrot; PrintCharrot > 64; PrintCharrot--) {
//				printf("%c", PrintCharrot);
//			}
//			printf("\n");
//		}
//	}
//	return 0;
//}

int main()
{
	//Prevents Ctrl+C closing the program
	signal(SIGINT, handle_ctrl_c);
	
	//Bind keys at startup

	//The array index of get_mapped_key() corresponds to the index of the key in this list
	const char *keys[] = { "Move Up", "Move Left", "Move Down", "Move Right", "Select", "Back" };
		
	create_keys(keys, sizeof(keys));
	
	map_all_keys();

	//Main loop

	int not_dead = 1;
	int key_index;
	while (not_dead)
	{
		if (_kbhit())
		{
			key_index = get_mapped_key(get_pressed_key());
			if (key_index != -1)
			{
				printf("%s\n", get_indexed_key_name(key_index));
			}
		}
		else
		{
			animate_idle(spinning_line, 1250);
		}
	}

	return 0;
}