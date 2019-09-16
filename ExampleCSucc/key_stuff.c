#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

/*
	This is a nonstandard header included with Windows.
	It allows reading keyboard input without pressing enter,
	testing whether a key has been pressed, and converting
	scan codes to legible characters. Kind of sucks that C
	doesn't let you do that normally. Even LC-3 did.
*/
#include <conio.h>
//MULTITHREAD ALL THE THINGS
#include <Windows.h>

#include "key_stuff.h"
#include "screen_stuff.h"

#pragma region PrintfMacros
//region PrintfMacros

#define printf_code(input, keycode)\
if (code) {\
	printf(keycode);\
} else {\
	printf(input);\
}

#define printf_full(input, full_input)\
if (full) {\
	printf(full_input);\
} else {\
	printf(input);\
}

#define printf_full_code(input, full_input, keycode)\
if (code) {\
	printf(keycode);\
} else if (full) {\
	printf(full_input);\
} else {\
	printf(input);\
}

//endregion PrintfMacros
#pragma endregion PrintfMacros

/*
	Swag Key Library
	8/26/2019

	This set of functions can parse any key input.
	Everything is commented to take advantage of visual
	studio displaying the comments when hovering.
*/

//Stores keybind information
typedef struct key_mapping {
	const char *key_name;	//The purpose of the keybind.
	int key_code[2];		//The input[] values of the keybind.
} key_map;

int input[2] = { 0, 0 };		//Holds the most recently polled user input.
int key_count;					//Used to index key_mappings as an array.
int keys_created;				//This prevents running create_keys twice and giving everything AIDS.
key_map *key_mappings;	//Stores all of the keybind structs.

key_map null_key = { "", { 0, 0 } };	//Used to guarantee a return value when IDK what else to use.


int allow_interrupt_change_input = 1;	//Related to the Ctrl+C handling stuff. Don't touch.
//Prevents Ctrl+C closing the program.
void handle_ctrl_c(int sig) {
	signal(sig, SIG_IGN);
	if (allow_interrupt_change_input) {
		input[0] = 3;
		input[1] = 0;
	}
	signal(SIGINT, handle_ctrl_c);
}

//This function polls for user input and returns the address used to reference that input.
int *get_pressed_key() {
	input[0] = _getch();
	input[1] = 0;
	if (input[0] == 0xE0)
	{
		input[0] = _getch();
		input[1] = 1;
	}
	else if (input[0] == 0x00)
	{
		input[0] = _getch();
		input[1] = 2;
	}
	return input;
}

/*
	This function is a bunch of giant switch statements to
	turn keycodes into legible output. It isn't necessary
	for letters and numbers since their keycodes correspond
	to their ASCII values, but crap like "Ctrl+Alt+Numpad /"
	is a lot more annoying to work with.
*/
static void print_key_inner(int *input_key, int code, int full) {
	switch (input_key[1])
	{
		case 0:
			switch (input_key[0])
			{
				case 0://I don't think this is possible, but can never be too sure.
					printf("NUL");
					break;
				case 1:
					printf_code("Ctrl+a", "SOH");
					break;
				case 2:
					printf_code("Ctrl+b", "STX");
					break;
				case 3://Ctrl+c just stops the console
					printf_full_code("Ctrl+2", "Ctrl+2 or Ctrl+c", "ETX");
					break;
				case 4:
					printf_code("Ctrl+d", "EOT");
					break;
				case 5:
					printf_code("Ctrl+e", "ENQ");
					break;
				case 6:
					printf_code("Ctrl+f", "ACK");
					break;
				case 7:
					printf_code("Ctrl+g", "BEL");
					break;
				case 8:
					printf_full_code("Backspace", "Backspace or Ctrl+h", "BKSP");
					break;
				case 9:
					printf_full_code("Tab", "Tab or Ctrl+i","TAB");
					break;
				case 10:
					printf_full_code("Ctrl+Enter", "Ctrl+Enter or Ctrl+j", "LF");
					break;
				case 11:
					printf_code("Ctrl+k", "VT");
					break;
				case 12:
					printf_code("Ctrl+l", "FF");
					break;
				case 13:
					printf_full_code("Enter", "Enter or Ctrl+m", "CR");
					break;
				case 14:
					printf_code("Ctrl+n", "SO");
					break;
				case 15:
					printf_code("Ctrl+o", "SI");
					break;
				case 16:
					printf_code("Ctrl+p", "DLE");
					break;
				case 17:
					printf_code("Ctrl+q", "DC1");
					break;
				case 18:
					printf_code("Ctrl+r", "DC2");
					break;
				case 19://This one seems to do something weird.
					printf_code("Ctrl+s", "DC3");
					break;
				case 20:
					printf_code("Ctrl+t", "DC4");
					break;
				case 21:
					printf_code("Ctrl+u", "NAK");
					break;
				case 22:
					printf_code("Ctrl+v", "SYN");
					break;
				case 23:
					printf_code("Ctrl+w", "ETB");
					break;
				case 24:
					printf_code("Ctrl+x", "CAN");
					break;
				case 25:
					printf_code("Ctrl+y", "EM");
					break;
				case 26:
					printf_code("Ctrl+z", "SUB");
					break;
				case 27:
					printf_full_code("Escape", "Escape or Ctrl+[","ESC");
					break;
				case 28:
					printf_code("Ctrl+\\", "FS");
					break;
				case 29:
					printf_code("Ctrl+]", "GS");
					break;
				case 30:
					printf_code("Ctrl+Shift+6", "RS");
					break;
				case 31:
					printf_code("Ctrl+Shift+-", "US");
					break;
				case 32:
					printf_code("Space","SPC");
					break;
				case 33:
					printf_code("!", "Shift+1");
					break;
				case 34:
					printf_code("\"", "Shift+'");
					break;
				case 35:
					printf_code("#", "Shift+3");
					break;
				case 36:
					printf_code("$", "Shift+4");
					break;
				case 37:
					printf_code("%%", "Shift+5");
					break;
				case 38:
					printf_code("&", "Shift+7");
					break;
				case 39:
					printf("'");
					break;
				case 40:
					printf_code("(", "Shift+9");
					break;
				case 41:
					printf_code(")", "Shift+0");
					break;
				case 42:
					printf_full("*", "* or Num *");
					break;
				case 43:
					printf_full("+", "+ or Num +");
					break;
				case 44:
					printf(",");
					break;
				case 45:
					printf_full("-", "- or Num -");
					break;
				case 46:
					printf_full(".", ". or Num .");
					break;
				case 47:
					printf_full("/", "/ or Num /");
					break;
				case 48:
					printf_full("0", "0 or Num 0");
					break;
				case 49:
					printf_full("1", "1 or Num 1");
					break;
				case 50:
					printf_full("2", "2 or Num 2");
					break;
				case 51:
					printf_full("3", "3 or Num 3");
					break;
				case 52:
					printf_full("4", "4 or Num 4");
					break;
				case 53:
					printf_full("5", "5 or Num 5");
					break;
				case 54:
					printf_full("6", "6 or Num 6");
					break;
				case 55:
					printf_full("7", "7 or Num 7");
					break;
				case 56:
					printf_full("8", "8 or Num 8");
					break;
				case 57:
					printf_full("9", "9 or Num 9");
					break;
				case 58:
					printf_code(":", "Shift+;");
					break;
				case 59:
					printf(";");
					break;
				case 60:
					printf_code("<", "Shift+,");
					break;
				case 61:
					printf_code("=", "Shift++");
					break;
				case 62:
					printf_code(">", "Shift+.");
					break;
				case 63:
					printf_code("?", "Shift+/");
					break;
				case 64:
					printf_code("@", "Shift+2");
					break;
				case 65:
					printf_code("A", "Shift+a");
					break;
				case 66:
					printf_code("B", "Shift+b");
					break;
				case 67:
					printf_code("C", "Shift+c");
					break;
				case 68:
					printf_code("D", "Shift+d");
					break;
				case 69:
					printf_code("E", "Shift+e");
					break;
				case 70:
					printf_code("F", "Shift+f");
					break;
				case 71:
					printf_code("G", "Shift+g");
					break;
				case 72:
					printf_code("H", "Shift+h");
					break;
				case 73:
					printf_code("I", "Shift+i");
					break;
				case 74:
					printf_code("J", "Shift+j");
					break;
				case 75:
					printf_code("K", "Shift+k");
					break;
				case 76:
					printf_code("L", "Shift+l");
					break;
				case 77:
					printf_code("M", "Shift+m");
					break;
				case 78:
					printf_code("N", "Shift+n");
					break;
				case 79:
					printf_code("O", "Shift+o");
					break;
				case 80:
					printf_code("P", "Shift+p");
					break;
				case 81:
					printf_code("Q", "Shift+q");
					break;
				case 82:
					printf_code("R", "Shift+r");
					break;
				case 83:
					printf_code("S", "Shift+s");
					break;
				case 84:
					printf_code("T", "Shift+t");
					break;
				case 85:
					printf_code("U", "Shift+u");
					break;
				case 86:
					printf_code("V", "Shift+v");
					break;
				case 87:
					printf_code("W", "Shift+w");
					break;
				case 88:
					printf_code("X", "Shift+x");
					break;
				case 89:
					printf_code("Y", "Shift+y");
					break;
				case 90:
					printf_code("Z", "Shift+z");
					break;
				case 91:
					printf("[");
					break;
				case 92:
					printf("\\");
					break;
				case 93:
					printf("]");
					break;
				case 94:
					printf_code("^", "Shift+6");
					break;
				case 95:
					printf_code("_", "Shift+-");
					break;
				case 96:
					printf("`");
					break;
				case 97:
					printf("a");
					break;
				case 98:
					printf("b");
					break;
				case 99:
					printf("c");
					break;
				case 100:
					printf("d");
					break;
				case 101:
					printf("e");
					break;
				case 102:
					printf("f");
					break;
				case 103:
					printf("g");
					break;
				case 104:
					printf("h");
					break;
				case 105:
					printf("i");
					break;
				case 106:
					printf("j");
					break;
				case 107:
					printf("k");
					break;
				case 108:
					printf("l");
					break;
				case 109:
					printf("m");
					break;
				case 110:
					printf("n");
					break;
				case 111:
					printf("o");
					break;
				case 112:
					printf("p");
					break;
				case 113:
					printf("q");
					break;
				case 114:
					printf("r");
					break;
				case 115:
					printf("s");
					break;
				case 116:
					printf("t");
					break;
				case 117:
					printf("u");
					break;
				case 118:
					printf("v");
					break;
				case 119:
					printf("w");
					break;
				case 120:
					printf("x");
					break;
				case 121:
					printf("y");
					break;
				case 122:
					printf("z");
					break;
				case 123:
					printf_code("{", "Shift+[");
					break;
				case 124:
					printf_code("|", "Shift+\\");
					break;
				case 125:
					printf_code("}", "Shift+]");
					break;
				case 126:
					printf_code("~", "Shift+`");
					break;
				case 127:
					printf_code("Ctrl+Backspace","Ctrl+BKSP");
					break;
				//case 128:
				//	printf("Ç");
				//	break;
				//case 129:
				//	printf("ü");
				//	break;
				//case 130:
				//	printf("é");
				//	break;
				//case 131:
				//	printf("â");
				//	break;
				//case 132:
				//	printf("ä");
				//	break;
				//case 133:
				//	printf("à");
				//	break;
				//case 134:
				//	printf("å");
				//	break;
				//case 135:
				//	printf("ç");
				//	break;
				//case 136:
				//	printf("ê");
				//	break;
				//case 137:
				//	printf("ë");
				//	break;
				//case 138:
				//	printf("è");
				//	break;
				//case 139:
				//	printf("ï");
				//	break;
				//case 140:
				//	printf("î");
				//	break;
				//case 141:
				//	printf("ì");
				//	break;
				//case 142:
				//	printf("Ä");
				//	break;
				//case 143:
				//	printf("Å");
				//	break;
				//case 144:
				//	printf("É");
				//	break;
				//case 145:
				//	printf("æ");
				//	break;
				//case 146:
				//	printf("Æ");
				//	break;
				//case 147:
				//	printf("ô");
				//	break;
				//case 148:
				//	printf("ö");
				//	break;
				//case 149:
				//	printf("ò");
				//	break;
				//case 150:
				//	printf("û");
				//	break;
				//case 151:
				//	printf("ù");
				//	break;
				//case 152:
				//	printf("ÿ");
				//	break;
				//case 153:
				//	printf("Ö");
				//	break;
				//case 154:
				//	printf("Ü");
				//	break;
				//case 155:
				//	printf("¢");
				//	break;
				//case 156:
				//	printf("£");
				//	break;
				//case 157:
				//	printf("¥");
				//	break;
				////IDK if 158 or 159 are typable
				//case 160:
				//	printf("á");
				//	break;
				//case 161:
				//	printf("í");
				//	break;
				//case 162:
				//	printf("ó");
				//	break;
				//case 163:
				//	printf("ú");
				//	break;
				//case 164:
				//	printf("ñ");
				//	break;
				//case 165:
				//	printf("Ñ");
				//	break;
				//case 166:
				//	printf("²");
				//	break;
				//case 167:
				//	printf("°");
				//	break;
				//case 168:
				//	printf("¿");
				//	break;
				////Pretty sure 169 can't be typed
				//case 170:
				//	printf("¬");
				//	break;
				//case 171:
				//	printf("½");
				//	break;
				//case 172:
				//	printf("¼");
				//	break;
				//case 173:
				//	printf("¡");
				//	break;
				//case 174:
				//	printf("«");
				//	break;
				//case 175:
				//	printf("»");
				//	break;
				////176-224 *definitely* can't be typed
				//case 225:
				//	printf("ß");
				//	break;
				////226-229 aren't possible
				//case 230:
				//	printf("µ");
				//	break;
				default:
					if (input_key[0] >= 0) {
						_putch(input_key[0]);
						printf(" %d", input_key[0]);
					}
					else {
						printf("%d", input_key[0]);
					}
			}
			break;
		case 1:
			switch (input_key[0])
			{
				case 71:
					printf_code("Home","HOME");
					break;
				case 72:
					printf_code("Up Arrow","UP");
					break;
				case 73:
					printf_code("Page Up","PGUP");
					break;
				case 75:
					printf_code("Left Arrow","LEFT");
					break;
				case 77:
					printf_code("Right Arrow","RIGHT");
					break;
				case 79:
					printf_code("End","END");
					break;
				case 80:
					printf_code("Down Arrow","DOWN");
					break;
				case 81:
					printf_code("Page Down","PGDN");
					break;
				case 82:
					printf_code("Insert","INS");
					break;
				case 83:
					printf_code("Delete","DEL");
					break;
				case 115:
					printf_code("Ctrl+Left Arrow", "Ctrl+LEFT");
					break;
				case 116:
					printf_code("Ctrl+Right Arrow", "Ctrl+RIGHT");
					break;
				case 117:
					printf_code("Ctrl+End", "Ctrl+END");
					break;
				case 118:
					printf_code("Ctrl+Page Down", "Ctrl+PGDN");
					break;
				case 119:
					printf_code("Ctrl+Home", "Ctrl+HOME");
					break;
				case 132:
					printf_code("Ctrl+Page Up", "Ctrl+PGUP");
					break;
				case 133:
					printf("F11");
					break;
				case 134:
					printf("F12");
					break;
				case 135:
					printf("Shift+F11");
					break;
				case 136:
					printf("Shift+F12");
					break;
				case 137:
					printf("Ctrl+F11");
					break;
				case 138:
					printf("Ctrl+F12");
					break;
				case 139:
					printf("Alt+F11");
					break;
				case 140:
					printf("Alt+F12");
					break;
				case 141:
					printf_code("Ctrl+Up Arrow", "Ctrl+UP");
					break;
				case 145:
					printf_code("Ctrl+Down Arrow", "Ctrl+DOWN");
					break;
				case 146:
					printf_code("Ctrl+Insert", "Ctrl+INS");
					break;
				case 147:
					printf_code("Ctrl+Delete", "Ctrl+DEL");
					break;
				default:
					printf("%d %d", input_key[0], input_key[1]);
			}
			break;
		case 2:
			switch (input_key[0])
			{
				case 1://Doesn't seem to function
					printf_code("Ctrl+Alt+Escape", "Ctrl+Alt+ESC");
					break;
				case 14:
					printf_code("Ctrl+Alt+Backspace", "Ctrl+Alt+BKSP");
					break;
				case 15://Changes windows instead
					printf_code("Ctrl+Alt+Tab", "Ctrl+Alt+TAB");
					break;
				case 16:
					printf("Ctrl+Alt+q");
					break;
				case 17:
					printf("Ctrl+Alt+w");
					break;
				case 18:
					printf("Ctrl+Alt+e");
					break;
				case 19:
					printf("Ctrl+Alt+r");
					break;
				case 20:
					printf("Ctrl+Alt+t");
					break;
				case 21:
					printf("Ctrl+Alt+y");
					break;
				case 22:
					printf("Ctrl+Alt+u");
					break;
				case 23:
					printf("Ctrl+Alt+i");
					break;
				case 24:
					printf("Ctrl+Alt+o");
					break;
				case 25:
					printf("Ctrl+Alt+p");
					break;
				case 26:
					printf("Ctrl+Alt+[");
					break;
				case 27:
					printf("Ctrl+Alt+]");
					break;
				case 28:
					printf("Ctrl+Alt+Enter");
					break;
				case 30:
					printf("Ctrl+Alt+a");
					break;
				case 31:
					printf("Ctrl+Alt+s");
					break;
				case 32:
					printf("Ctrl+Alt+d");
					break;
				case 33:
					printf("Ctrl+Alt+f");
					break;
				case 34:
					printf("Ctrl+Alt+g");
					break;
				case 35:
					printf("Ctrl+Alt+h");
					break;
				case 36:
					printf("Ctrl+Alt+j");
					break;
				case 37:
					printf("Ctrl+Alt+k");
					break;
				case 38:
					printf("Ctrl+Alt+l");
					break;
				case 39:
					printf("Ctrl+Alt+;");
					break;
				case 40:
					printf("Ctrl+Alt+'");
					break;
				case 41:
					printf("Ctrl+Alt+`");
					break;
				case 44:
					printf("Ctrl+Alt+z");
					break;
				case 45:
					printf("Ctrl+Alt+x");
					break;
				case 46:
					printf("Ctrl+Alt+c");
					break;
				case 47:
					printf("Ctrl+Alt+v");
					break;
				case 48:
					printf("Ctrl+Alt+b");
					break;
				case 49:
					printf("Ctrl+Alt+n");
					break;
				case 50:
					printf("Ctrl+Alt+m");
					break;
				case 51:
					printf("Ctrl+Alt+,");
					break;
				case 52:
					printf("Ctrl+Alt+.");
					break;
				case 53:
					printf("Ctrl+Alt+/");
					break;
				case 59:
					printf("F1");
					break;
				case 60:
					printf("F2");
					break;
				case 61:
					printf("F3");
					break;
				case 62:
					printf("F4");
					break;
				case 63:
					printf("F5");
					break;
				case 64:
					printf("F6");
					break;
				case 65:
					printf("F7");
					break;
				case 66:
					printf("F8");
					break;
				case 67:
					printf("F9");
					break;
				case 68:
					printf("F10");
					break;
				case 71:
					printf_full_code("Num Home", "Num Home or Shift+Num 7 with NumLock", "NUM HOME");
					break;
				case 72:
					printf_full_code("Num Up Arrow", "Num Up Arrow or Shift+Num 8 with NumLock", "NUM UP");
					break;
				case 73:
					printf_full_code("Num Page Up", "Num Page Up or Shift+Num 9 with NumLock", "NUM PGUP");
					break;
				case 75:
					printf_full_code("Num Left Arrow", "Num Left Arrow or Shift+Num 4 with NumLock", "NUM LEFT");
					break;
				case 77:
					printf_full_code("Num Right Arrow", "Num Right Arrow or Shift+Num 6 with NumLock", "NUM RIGHT");
					break;
				case 79:
					printf_full_code("Num End", "Num End or Shift+Num 1 with NumLock", "NUM END");
					break;
				case 80:
					printf_full_code("Num Down Arrow", "Num Down Arrow or Shift+Num 2 with NumLock", "NUM DOWN");
					break;
				case 81:
					printf_full_code("Num Page Down", "Num Page Down or Shift+Num 3 with NumLock", "NUM PGDN");
					break;
				case 82:
					printf_full_code("Num Insert", "Num Insert or Shift+Num 0 with NumLock", "NUM INS");
					break;
				case 83:
					printf_full_code("Num Delete", "Num Delete or Shift+Num . with NumLock", "NUM DEL");
					break;
				case 84:
					printf("Shift+F1");
					break;
				case 85:
					printf("Shift+F2");
					break;
				case 86:
					printf("Shift+F3");
					break;
				case 87:
					printf("Shift+F4");
					break;
				case 88:
					printf("Shift+F5");
					break;
				case 89:
					printf("Shift+F6");
					break;
				case 90:
					printf("Shift+F7");
					break;
				case 91:
					printf("Shift+F8");
					break;
				case 92:
					printf("Shift+F9");
					break;
				case 93:
					printf("Shift+F10");
					break;
				case 94:
					printf("Ctrl+F1");
					break;
				case 95:
					printf("Ctrl+F2");
					break;
				case 96:
					printf("Ctrl+F3");
					break;
				case 97:
					printf("Ctrl+F4");
					break;
				case 98:
					printf("Ctrl+F5");
					break;
				case 99:
					printf("Ctrl+F6");
					break;
				case 100:
					printf("Ctrl+F7");
					break;
				case 101:
					printf("Ctrl+F8");
					break;
				case 102:
					printf("Ctrl+F9");
					break;
				case 103:
					printf("Ctrl+F10");
					break;
				case 104:
					printf("Alt+F1");
					break;
				case 105:
					printf("Alt+F2");
					break;
				case 106:
					printf("Alt+F3");
					break;
				case 107:
					printf("Alt+F4");
					break;
				case 108:
					printf("Alt+F5");
					break;
				case 109:
					printf("Alt+F6");
					break;
				case 110:
					printf("Alt+F7");
					break;
				case 111:
					printf("Alt+F8");
					break;
				case 112:
					printf("Alt+F9");
					break;
				case 113:
					printf("Alt+F10");
					break;
				case 115:
					printf_full_code("Ctrl+Num Left Arrow", "Ctrl+Num Left Arrow or Ctrl+Shift+Num 4 with NumLock", "Ctrl+NUM LEFT");
					break;
				case 116:
					printf_full_code("Ctrl+Num Right Arrow", "Ctrl+Num Right Arrow or Ctrl+Shift+Num 6 with NumLock", "Ctrl+NUM RIGHT");
					break;
				case 117:
					printf_full_code("Ctrl+Num End", "Ctrl+Num End or Ctrl+Shift+Num 1 with NumLock", "Ctrl+NUM END");
					break;
				case 118:
					printf_full_code("Ctrl+Num Page Down", "Ctrl+Num Page Down or Ctrl+Shift+Num 3 with NumLock", "Ctrl+NUM PGDN");
					break;
				case 119:
					printf_full_code("Ctrl+Num Home", "Ctrl+Num Home or Ctrl+Shift+Num 7 with NumLock", "Ctrl+NUM HOME");
					break;
				case 120:
					printf("Ctrl+Alt+1");
					break;
				case 121:
					printf("Ctrl+Alt+2");
					break;
				case 122:
					printf("Ctrl+Alt+3");
					break;
				case 123:
					printf("Ctrl+Alt+4");
					break;
				case 124:
					printf("Ctrl+Alt+5");
					break;
				case 125:
					printf("Ctrl+Alt+6");
					break;
				case 126:
					printf("Ctrl+Alt+7");
					break;
				case 127:
					printf("Ctrl+Alt+8");
					break;
				case 128:
					printf("Ctrl+Alt+9");
					break;
				case 129:
					printf("Ctrl+Alt+0");
					break;
				case 130:
					printf("Ctrl+Alt+-");
					break;
				case 131:
					printf("Ctrl+Alt+=");
					break;
				case 132:
					printf_full_code("Ctrl+Num Page Up", "Ctrl+Num Page Up or Ctrl+Shift+Num 9 with NumLock", "Ctrl+NUM PGUP");
					break;
				case 141:
					printf_full_code("Ctrl+Num Up Arrow", "Ctrl+Num Up Arrow or Ctrl+Shift+Num 8 with NumLock", "Ctrl+NUM UP");
					break;
				case 145:
					printf_full_code("Ctrl+Num Down Arrow", "Ctrl+Num Down Arrow or Ctrl+Shift+Num 2 with NumLock", "Ctrl+NUM DOWN");
					break;
				case 146:
					printf_full_code("Ctrl+Num Insert", "Ctrl+Num Insert or Ctrl+Shift+Num 0 with NumLock", "Ctrl+NUM INS");
					break;
				case 147:
					printf_full_code("Ctrl+Num Delete", "Ctrl+Num Delete or Ctrl+Shift+Num . with NumLock", "Ctrl+NUM DEL");
					break;
				case 148:
					printf_code("Ctrl+Tab","Ctrl+TAB");
					break;
				case 149:
					printf_code("Ctrl+Num /","Ctrl+GRAY /");
					break;
				case 151:
					printf_code("Alt+Home", "Alt+HOME");
					break;
				case 152:
					printf_code("Alt+Up Arrow", "Alt+UP");
					break;
				case 153:
					printf_code("Alt+Page Up", "Alt+PGUP");
					break;
				case 155:
					printf_code("Alt+Left Arrow", "Alt+LEFT");
					break;
				case 157:
					printf_code("Alt+Right Arrow", "Alt+RIGHT");
					break;
				case 159:
					printf_code("Alt+End", "Alt+END");
					break;
				case 160:
					printf_code("Alt+Down Arrow", "Alt+DOWN");
					break;
				case 161:
					printf_code("Alt+Page Down", "Alt+PGDN");
					break;
				case 162:
					printf_code("Alt+Insert", "Alt+INS");
					break;
				case 163:
					printf_code("Alt+Delete", "Alt+DEL");
					break;
				case 164:
					printf_code("Ctrl+Alt+Num /", "Ctrl+Alt+GRAY /");
					break;
				case 166:
					printf_code("Ctrl+Alt+Num Enter", "Ctrl+Alt+NUM ENTER");
					break;
				default:
					printf("%d %d", input_key[0], input_key[1]);
			}
			break;
	}
}

//Prints the name of the key most likely to correspond with the given keycode.
void print_key(int *input_key)
{
	allow_interrupt_change_input = 0;
	print_key_inner(input_key, 0, 0);
	allow_interrupt_change_input = 1;
}
//Prints all possible key combinations that can generate the given keycode.
void print_key_combos(int *input_key)
{
	allow_interrupt_change_input = 0;
	print_key_inner(input_key, 0, 1);
	allow_interrupt_change_input = 1;
}
//Prints the technical identifier of the given keycode.
void print_keycode(int *input_key)
{
	allow_interrupt_change_input = 0;
	print_key_inner(input_key, 1, 0);
	allow_interrupt_change_input = 1;
}

/*
	This function initializes the key_mappings array
	based on the provided array of string pointers.
	This comment sucks, but I don't feel like fixing it.
*/
void create_keys(const char *key_names[], unsigned int size_of_keys) {
	if (keys_created == 0) {
		key_count = size_of_keys / sizeof(key_names[0]);	//This local is used to make a warning shut up
		if (key_count >= 1) {
			key_mappings = malloc(key_count * sizeof(key_map));
			if (key_mappings == NULL) {
				printf("malloc of size %d failed!\n", (int)(key_count * sizeof(key_map)));
				exit(1);
			}
			else {
				for (int i = 0; i < key_count; i++) {
					key_mappings[i].key_name = key_names[i];
					key_mappings[i].key_code[0] = 0;
					key_mappings[i].key_code[1] = 0;
				}
			}
			keys_created = 1;
		}
	}
}

//Returns the number of keys. If keys haven't been created, returns -1;
//int get_key_count() {
//	if (keys_created) {
//		return key_count;
//	}
//	return -1;
//}

int monitor_input = 1;

static void bind_key(int key_index, int j_count) {
	suspend_input_thread();
	int key_already_bound;
	int* key_pointer;
	do {
		key_already_bound = 0;
		printf("Press a key to map to \"%s\":   \t", key_mappings[key_index].key_name);
		key_pointer = get_pressed_key();
		print_key(key_pointer);
		for (int j = 0; j < j_count; j++) {
			if (memcmp(key_mappings[j].key_code, input, sizeof(input)) == 0) {
				key_already_bound = j + 1;
			}
		}
		if (key_already_bound) {
			printf("\n");
			print_key(key_pointer);
			printf(" is already bound to %s!\n\n", get_indexed_key_name(get_mapped_key(key_pointer)));
		}
	} while (key_already_bound);
	memcpy(key_mappings[key_index].key_code, input, sizeof(input));
	printf("\n\n");
	monitor_input = 1;
	resume_input_thread();
}

//Checks if a key exists and prompts the user to bind it
void map_one_key(int key_index) {
	if ((key_index >= 0) && (key_index <= key_count)) {
		bind_key(key_index, key_count);
	}
}

//Loops through the key_mappings array and prompts the user to bind every key.
void map_all_keys() {
	for (int i = 0; i < key_count; i++) {
		bind_key(i, i);
	}
}

//If the input keycode is bound, returns the index of the keybind. Otherwise returns -1.
int get_mapped_key(int *input_key) {
	for (int i = 0; i < key_count; i++) {
		if (memcmp(key_mappings[i].key_code, input_key, sizeof(key_mappings[i].key_code)) == 0) {
			return i;
		}
	}
	return -1;
}

//Returns the pointer to the string used to generate the keybind.
const char *get_indexed_key_name(int key_index) {
	if ((key_index >= 0) && (key_index <= key_count)) {
		return key_mappings[key_index].key_name;
	}
	else {
		return null_key.key_name;
	}
}

int key_index;
static DWORD WINAPI monitor_input_function(LPVOID lol_whats_an_lpvoid) {
	//This is some extra sketchy thread junk. It prob
	while (monitor_input) {
		if (_kbhit())
		{
			key_index = get_mapped_key(get_pressed_key());
			if (key_index != -1)
			{
				printf("%s\n", get_indexed_key_name(key_index));
			}
		}
		/*else {
		  	animate_idle(spinning_line, 125);
		}*/
	}
	ExitThread((DWORD)0);
}

int input_thread_id;
HANDLE input_handle;
//Vague attempt at multithreading
void create_input_thread() {
	input_handle = CreateThread((LPSECURITY_ATTRIBUTES)NULL, (DWORD)0, (LPTHREAD_START_ROUTINE)&monitor_input_function, (LPVOID)NULL, (DWORD)4, (LPDWORD)&input_thread_id);
}

void suspend_input_thread() {
	if (input_thread_id) {
		SuspendThread(input_handle);
	}
}

void resume_input_thread() {
	if (input_thread_id) {
		ResumeThread(input_handle);
	}
}

//int get_input_exit_code() {
//	DWORD exit_code = 0;
//	LPDWORD exit_code_p = &exit_code;
//	GetExitCodeThread(input_handle, exit_code_p);
//	return (int)exit_code;
//}