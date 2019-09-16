#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <mmsystem.h>
#include "main_game.h"

//Yes, I used ASCII control characters as error codes. Deal with it.
#define DCE ''
#define DC1 ''
#define DC2 ''
#define DC3 ''
#define DC4 ''

char okina[] = "'",
screw_null_references[] = "",
//These are arrays so that they can be returned by hawaiify without a warning about levels of indirection
multiple_words[] = { DCE },
illegal_character[] = { DC1 },
double_consonant[] = { DC2 },
ending_consonant[] = { DC3 },
wtf[] = { DC4 };

char *hawaiify(char *character, int position) {
	//If the letter is a capital, just pretend it isn't since that doesn't affect the output
	switch (character[0])
	{
		case 'P': character[0] = 'p'; break;
		case 'K': character[0] = 'k'; break;
		case 'H': character[0] = 'h'; break;
		case 'L': character[0] = 'l'; break;
		case 'M': character[0] = 'm'; break;
		case 'N': character[0] = 'n'; break;
		case 'W': character[0] = 'w'; break;
		case 'A': character[0] = 'a'; break;
		case 'E': character[0] = 'e'; break;
		case 'I': character[0] = 'i'; break;
		case 'O': character[0] = 'o'; break;
		case 'U': character[0] = 'u'; break;
	}
	//Check for error conditions
	switch (character[0])
	{
		case ' ':
			return multiple_words;
		case 'p': case 'k': case 'h': case 'l': case 'm': case 'n': case '\'': case 'w':
			switch (character[1])
			{
				case '\0'://End of string
					return ending_consonant;
				case 'p': case 'k': case 'h': case 'l': case 'm': case 'n': case '\'': case 'w':
					return double_consonant;
			}
		case 'a': case 'e': case 'i': case 'o': case 'u':
			break;
		default:
			return illegal_character;
	}
	//Hawaii time
	switch (character[0])
	{
		case 'p': return "p";
		case 'k': return "k";
		case 'h': return "h";
		case 'l': return "l";
		case 'm': return "m";
		case 'n': return "n";
		case '\'': return okina;
		case 'w':
			if (position == 0) {
				return "w";
			}
			else {
				//This is in an else statement to avoid invalid reads when position == 0
				switch (character[-1]) {
					case 'a': case 'o': case 'u': default:
						return "w";
					case 'e': case 'i':
						return "v";
				}
			}
		case 'a':
			switch (character[1]) {
				case 'e': case 'i':
					return "eye-";
				case 'o': case 'u':
					return "ow-";
				default:
					return "ah-";
			}
		case 'e':
			switch (character[1]) {
				case 'i': return "ay-";
				default: return "eh-";
			}
		case 'i':
			switch (character[1]) {
				case 'u': return "ew-";
				default: return "ee-";
			}
		case 'o':
			switch (character[1]) {
				case 'i': return "oy-";
				case 'u': return "ow-";
				default: return "oh-";
			}
		case 'u':
			switch (character[1]) {
				case 'i': return "ooey-";
				default: return "oo-";
			}
	}
	return wtf;//It shouldn't be possible to reach this, but you never know.
}

int main2() {
	async_song();//lol
	printf("Enter a Hawaiian word:\n");
	fflush(stdout);
	char word[BUFSIZ];//I'd rather call this variable input_string, but meh
	(void)scanf("%s", word);
	int input_length;
	for (input_length = 0; word[input_length] != '\0'; input_length++) {/*Empty for loops are fun. :D*/}
	char *output_temp = screw_null_references;
	int output_temp_length = 0;
	size_t output_length = -1;
	char* output_string = screw_null_references;
	size_t output_index = 0;
	for (int i = 0; i < 3; i++) {
		//This same loop is reused for sizing the output string, initializing it, and printing it.
		//This loop exists 
		//i == 0: size;		i == 1: initialize;		i == 2: print
		if (i == 1) {
			output_string = (char*)malloc((output_length) * sizeof(char));
		}
		if (i == 2) {//For some reason putting the printf in the loop made an error shut up *shrug*
			//Words always end with vowels, so my string builder ends up tacking an extra - on the end of the output.
			//Since the string isn't terminated yet, that extra - can be conveniently and safely converted to a terminator
			output_string[output_length] = '\0';
			printf("%s\n", output_string);
		}
		else {
			for (int j = 0; j < input_length; j++) {
				output_temp = hawaiify(&word[j], j);
				if ((i == 0) && ((output_temp == multiple_words) || (output_temp == illegal_character) || (output_temp == double_consonant) || (output_temp == ending_consonant) || (output_temp == wtf))) {
					if (output_temp[0] != DCE) {//If the error isn't multiple_words, forcibly exit.
						i = 3;
					}
					switch (output_temp[0]) {
						case DC1:
							printf("Character %c is not allowed.\n", (int)word[j]); break;
						case DC2:
							printf("Double consonants: %c%c\n", (int)word[j], (int)word[j + 1]); break;
						case DC3:
							printf("Consonant %c at end of the word.\n", (int)word[j]); break;
						case DC4:
							printf("WTF did you do?\n"); break;
					}
					j = input_length;
				}
				else if (output_temp != okina) {
					//This loop exists to calculate the string length of output_temp without using strlen()
					for (output_temp_length = 0; output_temp[output_temp_length] != '\0'; output_temp_length++) {}
					if (i == 0) {
						output_length += output_temp_length;
					}
					else {
						memcpy((output_string + (output_index * sizeof(char))), output_temp, (output_temp_length * sizeof(char)));
						output_index += output_temp_length;
					}
				}
				//This condition can only be reached if output_temp == okina
				else if ((i == 1) && (output_index >= 1)) {
					output_string[output_index - 1] = '\'';
				}
			}
		}
	}
	while (1) {};
	//printf("BE GONE HAWAII\n");
	return 0;
}