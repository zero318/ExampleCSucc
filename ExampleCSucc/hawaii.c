#include <stdio.h>
#include <stdlib.h>

//I had to use strlen() instead of sizeof() since apparently
//sizeof() can't handle retreiving data from a pointer.
#include <string.h>

#include <Windows.h>
#include <mmsystem.h>

#include "main_game.h"

#pragma warning(disable:4996)

char okina[] = "'", multiple_words[] = "", illegal_character[] = "", double_consonant[] = "", ending_consonant[] = "", wtf[] = "";

char *hawaiify(char *character, int position) {
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
	switch (character[0])
	{
		default:
			return illegal_character;
		case ' ':
			return multiple_words;
		case 'p': case 'k': case 'h': case 'l': case 'm': case 'n': case '\'': case 'w':
			switch (character[1])
			{
				case '\0':
					return ending_consonant;
				case 'p': case 'k': case 'h': case 'l': case 'm': case 'n': case '\'': case 'w':
					return double_consonant;
			}
		case 'a': case 'e': case 'i': case 'o': case 'u':
			break;
	}
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
	PlaySound(TEXT(BGMUSIC), NULL, (SND_FILENAME + SND_LOOP + SND_ASYNC));//lol
	printf("Enter a Hawaiian word:\n");
	fflush(stdout);
	char word[BUFSIZ];//I'd rather call this variable input_string, but meh
	(void)scanf("%s", &word);
	int input_length = 0;
	while (word[input_length] != '\0') {
		input_length++;
	}
	char *output_temp;
	size_t output_length = -1;
	char *output_string = NULL;
	size_t output_index = 0;
	for (int i = 0; i < 3; i++) {
		//This same loop is reused for sizing the output string, initializing it, and printing it.
		//i == 0: size;		i == 1: initialize;		i == 2: print
		if (i == 1) {
			output_string = (char*)malloc(output_length * sizeof(char));
		}
		if (i == 2) {//For some reason putting the printf in the loop made an error shut up
			output_string[output_length] = '\0';
			printf("%s\n", output_string);
		}
		else {
			for (int j = 0; j < input_length; j++) {
				output_temp = hawaiify(&word[j], j);
				if ((i == 0) && ((output_temp == multiple_words) || (output_temp == illegal_character) || (output_temp == double_consonant) || (output_temp == ending_consonant) || (output_temp == wtf))) {
					if (output_temp[0] != '') {
						i = 3;
					}
					switch (output_temp[0]) {
						case '':
							printf("Character %c is not allowed.\n", word[j]); break;
						case '':
							printf("Double consonants: %c%c\n", word[j], word[j + 1]); break;
						case '':
							printf("Consonant %c at end of the word.\n", word[j]); break;
						case '':
							printf("WTF did you do?\n"); break;
					}
					j = input_length;
				}
				else if (output_temp != okina) {
					if (i == 0) {
						output_length += strlen(output_temp);
					}
					else if ((output_string + (output_index * sizeof(char))) != 0) {//condition to make a warning shut up
						memcpy((output_string + (output_index * sizeof(char))), output_temp, (strlen(output_temp) * sizeof(char)));
						output_index += strlen(output_temp);
					}
				}
				else if ((i == 1) && output_string) {//condition to make a warning shut up
					output_string[output_index - 1] = '\'';
				}
			}
		}
	}
	while (1) {};
	//printf("BE GONE HAWAII\n");
	return 0;
}