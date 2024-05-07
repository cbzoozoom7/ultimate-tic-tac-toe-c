// functions.c
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#include "functions.h"
void getInput(const char *prompt, BoardLocation *loc) { // prompts the user with the given prompt until they provide a valid response (1–9), & writes the input onto the provided BoardLocation
	char isBadInput = 1; // bool
	char buf[CELL_LENGTH];
	while (isBadInput) {
		printf("%s ", prompt);
		fgets(buf, CELL_LENGTH, stdin);
		if (strlen(buf) == 2) {
			if (buf[0] > '9' || buf[0] < '1') {
				printf("Invalid input. Please enter a number 1–9.\n");
			} else {
				isBadInput = 0;
			}
		}
	}
	loc->name = buf[0];
	loc->row = (loc->name - '0' - 1) / BOARD_SIZE;
	loc->col = (loc->name - '0' - 1) % BOARD_SIZE;
}
char isSubboardFull(const int subboard[BOARD_SIZE][BOARD_SIZE]) { // returns bool
	char isFull = 1;
	int row = 0;
	while (row < BOARD_SIZE && isFull) {
		int col = 0;
		while (col < BOARD_SIZE && isFull) {
			isFull = subboard[row][col] != NUM_PLAYERS;
			col++;
		}
		row++;
	}
	return isFull;
}
