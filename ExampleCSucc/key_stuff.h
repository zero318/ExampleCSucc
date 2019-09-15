#ifndef KEYSTUFF_H
#define KEYSTUFF_H
//Prevents Ctrl+C closing the program.
void handle_ctrl_c(int sig);
//This function polls for user input and returns the address used to reference that input.
int *get_pressed_key();
//Prints the name of the key most likely to correspond with the given keycode.
void print_key(int *input_key);
//Prints all possible key combinations that can generate the given keycode.
void print_key_combos(int *input_key);
//Prints the technical identifier of the given keycode.
void print_keycode(int *input_key);
/*
	This function initializes the key_mappings array
	based on the provided array of string pointers.
	This comment sucks, but I don't feel like fixing it.
*/
void create_keys(const char *key_names[], unsigned int size_of_keys);
//Returns the number of keys. If keys haven't been created, returns -1;
int get_key_count();
//Loops through the key_mappings array and prompts the user to bind every key.
void map_all_keys();
//If the input keycode is bound, returns the index of the keybind. Otherwise returns -1.
int get_mapped_key(int *input_key);
//Returns the pointer to the string used to generate the keybind.
const char *get_indexed_key_name(int key_index);
int monitor_input;
int key_index;
//Vague attempt at multithreading
void create_input_thread();
void suspend_input_thread();
void resume_input_thread();
//int get_input_exit_code();
#endif