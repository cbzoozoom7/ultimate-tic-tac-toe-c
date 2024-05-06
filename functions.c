// functions.c
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#include "functions.h"
void getInput(const char *prompt, BoardLocation *loc) { // prompts the user with the given prompt until they provide a valid response (1–9), & writes the input onto the provided BoardLocation
	loc->name = -1;
	char isBadInput = 1; // bool
	while (isBadInput) {
		printf("%s ", prompt);
		loc->name = getc(stdin);
		while (getc(stdin) != '\n') {}
		if (loc->name > '9' || loc->name < '1') {
			printf("Invalid input. Please enter a number 1–9.\n");
		} else {
			isBadInput = 0;
		}
	}
	loc->row = (loc->name - '0' - 1) / BOARD_SIZE;
	loc->col = (loc->name - '0' - 1) % BOARD_SIZE;
}
char ***getSubboard(const char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][CELL_LENGTH], const BoardLocation *loc) {
	return board[loc->row][loc->col];
}
char *getCell(const char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][CELL_LENGTH], const BoardLocation *subboardLoc, const BoardLocation *cellLoc) {
	return getSubboard(board, subboardLoc)[cellLoc->row][cellLoc->col];
}
char isSubboardFull(const char subboard[BOARD_SIZE][BOARD_SIZE][CELL_LENGTH]) { // returns bool
	char isFull = 1;
	int row = 0;
	while (row < BOARD_SIZE && isFull) {
		int col = 0;
		while (col < BOARD_SIZE && isFull) {
			isFull = strcmp((subboard[row][col]), " ");
			col++;
		}
		row++;
	}
	if (isFull) {
		isFull = 1;
	}
	return isFull;
}
