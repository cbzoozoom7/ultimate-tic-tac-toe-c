// functions.c
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#include "functions.h"
char getInput(const char *prompt, BoardLocation *loc) { // prompts the user with the given prompt until they provide a valid response (1–9), & writes the input onto the provided BoardLocation
	char isGoodInput = 0; // bool
	char buf[CELL_LENGTH];
	while (!isGoodInput) {
		printf("%s ", prompt);
		if (fgets(buf, CELL_LENGTH, stdin)) {
			if ((strlen(buf) < 3) && (buf[0] >= '1' && buf[0] <= '9')) {
				isGoodInput = 1;
				loc->name = buf[0];
				loc->row = (loc->name - '0' - 1) / BOARD_SIZE;
				loc->col = (loc->name - '0' - 1) % BOARD_SIZE;
			} else if (strcmp(buf, "undo\n") == 0) {
				isGoodInput = 2;
			} else {
				printf("Invalid input. Please enter a number 1–9. undo to go back a turn.\n");
			}
		} else {
			printf("Invalid input. Please enter a number 1–9. Undo to go back a turn.\n");
		}
	}
	return --isGoodInput;
}
char isSubboardFull(const Subboard subboard) { // returns bool
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
char checkWin(Subboard s, const BoardLocation *cell, Subboard overall, const BoardLocation *subboard) {
	signed char player = s[cell->row][cell->col];
	int i = 1;
	char rowWin = 1; // bool
	char colWin = 1; // bool
	while (i < BOARD_SIZE && (rowWin || colWin)) { // check for horizontal & vertical wins simultaneously
		rowWin = rowWin && (player == s[cell->row][(cell->col + i) % BOARD_SIZE]);
		colWin = colWin && (player == s[(cell->row + i) % BOARD_SIZE][cell->col]);
		i++;
	}
	char win = rowWin || colWin; // bool
	if (!win && (cell->name % 2 == 1)) { // if I didn't already detect a win, & it's an odd-numbered space, check for diagonal wins. Even numbered spaces are in the middle of a side, making them ineligible for diagonals.
		i = 1;
		char forwardWin = 1;
		char backwardWin = 1;
		win = 1;
		while (i < BOARD_SIZE && win) {
			forwardWin = forwardWin && (player == s[(cell->row + i) % BOARD_SIZE][(cell->col + i) % BOARD_SIZE]);
			backwardWin = backwardWin && (player == s[(cell->row + i) % BOARD_SIZE][(cell->col - i + BOARD_SIZE) % BOARD_SIZE]);
			i++;
			win = forwardWin || backwardWin;
		}
	}
	if (win) {
		// fill subboard with player
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				s[row][col] = player;
			}
		}
		overall[subboard->row][subboard->col] = player;
		// check if they won the game too
		if (cell != subboard) { // base case for recursion
			win += checkWin(overall, subboard, overall, subboard);
		}
	}
	return win;
}
char checkStalemate(const Subboard board[BOARD_SIZE][BOARD_SIZE], Subboard overall, const BoardLocation *subboard) {
	char stalemate = isSubboardFull(board[subboard->row][subboard->col]); // bool
	if (stalemate) {
		if (overall[subboard->row][subboard->col] == NUM_PLAYERS) { // if that sub-board is marked empty... (This check is used to avoid overwriting a win on the overall board)
			overall[subboard->row][subboard->col] = -1; // mark that sub-board full
		}
		int row = 0;
		while (stalemate && row < BOARD_SIZE) {
			int col = 0;
			while (stalemate && col < BOARD_SIZE) {
				if (overall[row][col] == NUM_PLAYERS) { // check for empty space in overall board
					stalemate = 0;
				}
				col++;
			}
			row++;
		}
	}
	return stalemate;
}
void initGameState(GameState *gs) {
	gs->subboard.name = 0;
	gs->cell.name = 0;
	gs->didChooseSubboard = 1;
}
