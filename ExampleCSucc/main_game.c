/* SuccMaster was here
	Example C Program
	8/26/2019
	
	Wassup, it's ya boi skinny comment.
*/

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#include "key_stuff.h"
#include "screen_stuff.h"
#include "main_game.h"

//int ChrisSucc1() {
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

#include "hawaii.h"

//char succ[] = "Chris lamented, \"Why doesn't my code work?\" without knowing that \\' could solve his problem.";
//char succ2[] = {'C','h','r','i','s',' ','l','a','m','e','n','t','e','d',',',' ','"','W','h','y',' ','d','o','e','s','n','\'','t',' ','m','y',' ','c','o','d','e',' ','w','o','r','k','?','"',' ','w','i','t','h','o','u','t',' ','k','n','o','w','i','n','g',' ','t','h','a','t',' ','\\','\'',' ','c','o','u','l','d',' ','s','o','l','v','e',' ','h','i','s',' ','p','r','o','b','l','e','m','.','\0'};

#define HAWAII_MODE 1
#define HAWAII_LOOP 0

void go_to_hawaii() {
	play_async_song("taco.wav");//lol
	if (HAWAII_LOOP == 0) {
		main2();
	}
	while (1) {
		if (HAWAII_LOOP) {
			main2();
		}
	}
}

int main() {
	//Hawaii Mode Enable
	if (HAWAII_MODE) {
		go_to_hawaii();
	}

	SetConsoleTitle("Debug X: C Edition");
	//adjustWindowSize(80, 25);
	adjustWindowSize(121, 40);

	//Prevents Ctrl+C closing the program
	signal(SIGINT, handle_ctrl_c);
	
	//Bind keys at startup

	//The array index of get_mapped_key() corresponds to the index of the key in this list
	//There's also an enum in the header
	const char *keys[] = {
		"Move Up",
		"Move Left",
		"Move Down",
		"Move Right",
		"Select",
		"Back"
	};

	const char *main_menu[] = {
		"New Game",
		"Continue Game",
		"Memes",
		"Settings",
		"Exit"
	};
		
	create_keys(keys, sizeof(keys));
	
	map_all_keys();

	create_input_thread();


	//Main loop

	int game_state = 1;
	while (game_state) {
		switch (game_state)
		{
			//Exit
			case 0:
				monitor_input = 0;
				break;
			//Title Screen
			case 1:
				suspend_input_thread();
				cls();
				play_async_song("taco.wav");
				//This line is the title screen string.
#pragma region TitleScreenArt
				printf(
					"                                                                                                                        \n"
					"     =                                                                                                                  \n"
					"     WXAI=               =   =IAAXI                                                          M=           A=            \n"
					"     XA =AXXA=          =WXAAI=         WI======                                              MA        IMI             \n"
					"     =W      IXA=        W             IWIIIIIIIXX   IA                                        AX=     XA               \n"
					"      MI       =AX=      W             AX        =M= AX         MX      IXAXI                    XX  =M=                \n"
					"       W          XA     MI            XA         =W AX         W=    XXI                         =MXM                  \n"
					"       XA          MI    XA            MI          W AX        IM    MA                            AMM=                 \n"
					"       =W          =W    XA            W=         XX IM        MI   IM                            IM  XA                \n"
					"        W           IM   XMAAAAAXAXA   W=      IXXI   W        W    MI        IA=                =W    IMI              \n"
					"        W           =W   =W            WI=IAXMXI      MI      IM    W=     XAXI MI               W=      AX             \n"
					"        W=          XA    W=          IWXAIIIIXXI     IX      XA    W=          IM              MI        =MI           \n"
					"        MI         IM     W=           MI       XX    =W      W     MI          MA             XX           MA          \n"
					"        XA        IM     =W            XI       IM     XA    MI     =MAAAIIIAAXXI             IM             =          \n"
					"        XA        W=     IM            XA       MI     =WAAXX=                                I                         \n"
					"        AX       AX      AX         == AX     IMA                                                                       \n"
					"        AX      XA       XA   =IAXXXI=  W   XXI                                                                         \n"
					"        XA    AM=        IAAAAI=        MXXX=                                                                           \n"
					"        XA=IXXA                         IA                                                                              \n"
					"        XXA=                                                                                                            \n"
					"                                                                                                                I       \n"
					"                                                                                   I ==        IAA=            =W       \n"
					"                              ===========                 I         ==IXXXAAA AXAXMWAII      IMIAMI   MX        MI      \n"
					"             =XXXX            WIIIIIIIIII=  AW=       AAAXWXAAI   AAII=XA         AX        MA    XX  WXX       =W      \n"
					"          =AXA               IM             MAMA          W            XA         W=       XX      W= W XA       W=     \n"
					"        AMA                  XA             W= IXA        W            XA        =M       AX       W =W  XA      W=     \n"
					"       IM                    W=             W    IW       W            W=        IX      =W        W =W   MA    =W      \n"
					"       MA                    W        ==   =M     W       W            W         IX      IM       IM =W    MI   IM      \n"
					"       W                    IWAAAXAAAAII   XA     W       W           IM         IX      =M       MI =W     MI  XA      \n"
					"       W                    XA             W=    AX       W           XA         IX       XX     XX  =W     =W= W=      \n"
					"       W=                   XI            =W    =W        W           W=         =W        XA  IMA   IM      IMIM       \n"
					"       IM                   MI            AX   =W=        W=IAXI     IM           W=       =XAXI     AX       MWX       \n"
					"        AM         =XI     =W       ==    AA =AM=    IIAXXMI=        AX         =IMXAAXAAAA=         AA        WA       \n"
					"         IXXI===AXXA       IWIAAAXXAII    AMXA=      ==              MI       =AI===                 I=                 \n"
					"            =III=           I=            ==                         MI                                                 \n"
					"                                                                                                                        \n"
					"                                                                                                                        \n"
					"                                                                                                                        \n"
					"                                                                                                                        \n"
					"(C) 69BC-Waffle http://nazr.in/18vx                                                                                     ");
#pragma endregion TitleScreenArt
				COORD flash_letters_coord = {44, 37};
				int flash_letters = 0;
				int flash_delay = 10000;
				while (_kbhit() == 0) {
					if (flash_letters == 2 * flash_delay) {
						flash_letters = 0;
					}
					if (flash_letters == 0) {
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), flash_letters_coord);
						printf("                                ");
					}
					else if (flash_letters == flash_delay) {
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), flash_letters_coord);
						printf("Press Any Key to not Succ Ballz!");
					}
					flash_letters++;
				}
				game_state = 2;
				break;
			//Main Menu
			case 2:
				//adjustWindowSize(80, 25);
				stop_async_song();
				cls();
				printf("This is where the main menu is supposed to be, but it doesn't exist yet.\n\nEnjoy GBJ.");
				while(1) {}

				break;
		}
		/*if (key_index == -1) {
			monitor_input = 0;
		}*/
		//animate_idle(spinning_line, 125);
		/*if (_kbhit())
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
		}*/
	}
	while (1) {}
	return 0;
}