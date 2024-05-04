// functions.c
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#include "functions.h"
int getInput(const char *prompt, int *row, int *col) {
	int input = -1;
	char isBadInput = 1; // bool
	while (isBadInput) {
		printf("%s ", prompt);
		scanf("%d", &input);
		if (input > 9 || input < 1) {
			printf("Invalid input. Please enter a number 1–9.\n");
		} else {
			isBadInput = 0;
		}
	}
	*row = (input-1) / BOARD_SIZE;
	*col = (input-1) % BOARD_SIZE;
	return input;
}
char isSmallBoardFull(char smallBoard[BOARD_SIZE][BOARD_SIZE][CELL_LENGTH]) {
	char isFull = 1;
	int row = 0;
	while (row < BOARD_SIZE && isFull) {
		int col = 0;
		while (col < BOARD_SIZE && isFull) {
			isFull = strcmp((smallBoard[row][col]), " ");
			col++;
		}
		row++;
	}
	if (isFull) {
		isFull = 1;
	}
	return isFull;
}
