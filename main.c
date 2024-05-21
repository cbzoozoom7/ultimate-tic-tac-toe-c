//main.c
//ultimate-tic-tac-toe-c
//copyright Christopher Bowman 2024
//created Fri 3 May 2024
#include "main.h"
int main(void) {
	signed char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE]; // Think of them like nested 2D arrays, not a 4D array.
	Subboard wins; // represents sub-boards that have been won. This makes it much easier to determine if the game is over
	char playerSymbols[][CELL_LENGTH] = {"\x1b[31mX\x1b[0m", "\x1b[33mO\x1b[0m", " "}; // {"X" in red, "O" in blue, " "}
	signed char currentPlayer = 0; // bool used as index for playerSymbols
	char gameOver = 0; // bool used to end the game
	for (int bigRow = 0; bigRow < BOARD_SIZE; bigRow++) { // Initialize the game board with spaces
		for (int bigCol = 0; bigCol < BOARD_SIZE; bigCol++) {
			for (int smallRow = 0; smallRow < BOARD_SIZE; smallRow++) {
				for (int smallCol = 0; smallCol < BOARD_SIZE; smallCol++) {
					board[bigRow][bigCol][smallRow][smallCol] = NUM_PLAYERS; // playerSymbols is used as a lookup table to print out the board. playerSymbols[NUM_PLAYERS] = " ", representing an empty space
				}
			}
			wins[bigRow][bigCol] = NUM_PLAYERS;
		}
	}
	GameState backup[NUM_PLAYERS]; // used to restore the previous state of the board
	for (int player = 0; player < NUM_PLAYERS; player++) {
		initGameState(&(backup[currentPlayer]));
	}
	BoardLocation subboardLoc;
	subboardLoc.name = 0;
	while (!gameOver) {
		BoardLocation cellLoc;
		UndoStatus undoState = NORMAL;
		printf("1|2|3\n");
		printf("-+-+-\n");
		printf("4|5|6\n");
		printf("-+-+-\n");
		printf("7|8|9\n");
		char prompt[PROMPT_LENGTH];
		if (subboardLoc.name == 0) {
			backup[currentPlayer].didChooseSubboard = 1;
			snprintf(prompt, PROMPT_LENGTH, "Player %s, which sub-board would you like to play in?", playerSymbols[currentPlayer]);
			undoState = getInput(prompt, &subboardLoc);
			while (isSubboardFull(board[subboardLoc.row][subboardLoc.col]) && undoState == NORMAL) {
				printf("Invalid choice; sub-board %c is already full or won.\n", subboardLoc.name);
				undoState = getInput(prompt, &subboardLoc);
			}
		}
		if (undoState == NORMAL) {
			snprintf(prompt, PROMPT_LENGTH, "Player %s, which cell in sub-board %c would you like to mark?", playerSymbols[currentPlayer], subboardLoc.name);
			undoState = getInput(prompt, &cellLoc);
		}
		while ((board[subboardLoc.row][subboardLoc.col][cellLoc.row][cellLoc.col] != NUM_PLAYERS) && (undoState == NORMAL)) {
			printf("Invalid choice; sub-board %c, cell %c is already marked.\n", subboardLoc.name, cellLoc.name);
			undoState = getInput(prompt, &cellLoc);
		}
		if (undoState == UNDO_REQUESTED) {
			GameState restore = backup[!currentPlayer];
			if (restore.subboard.name == 0) {
				printf("Can't go back.\n");
				undoState = UNDO_FAILED;
			} else { // perform the undo operation
				board[restore.subboard.row][restore.subboard.col][restore.cell.row][restore.cell.col] = NUM_PLAYERS; // clear the space
				initGameState(&(backup[currentPlayer])); // invalidate the backup for this turn
			}
		} else { // process the user input
			board[subboardLoc.row][subboardLoc.col][cellLoc.row][cellLoc.col] = currentPlayer;
			backup[currentPlayer].subboard = subboardLoc;
			backup[currentPlayer].cell = cellLoc;
			switch (checkWin(board[subboardLoc.row][subboardLoc.col], &cellLoc, wins, &subboardLoc)) {
				case 2:
					gameOver = 1;
				case 1: // intentional spillover
					printf("Player %s wins sub-board %c.\n", playerSymbols[currentPlayer], subboardLoc.name);
			}
		}
		for (int bigRow = 0; bigRow < BOARD_SIZE; bigRow++) { // print the board
			for (int smallRow = 0; smallRow < BOARD_SIZE; smallRow++) {
				for (int bigCol = 0; bigCol < BOARD_SIZE; bigCol++) {
					for (int smallCol = 0; smallCol < BOARD_SIZE; smallCol++) {
						printf("%s", playerSymbols[board[bigRow][bigCol][smallRow][smallCol]]);
						if (smallCol < BOARD_SIZE - 1) { // no separator after the last space
							printf("|");
						}
					}
					if (bigCol < BOARD_SIZE - 1) {
						printf(" || "); // big column separator
					} else {
						printf("\n");
					}
				}
				if (smallRow < BOARD_SIZE - 1) {
					printf("-+-+- || -+-+- || -+-+-\n"); // small row separator
				}
			}
			if (bigRow < BOARD_SIZE - 1) {
				printf("      ||       ||      \n");
				printf("------++-------++------\n"); // big row separator
				printf("------++-------++------\n"); // TODO: programmatically generate separators??
				printf("      ||       ||      \n");
			}
		}
		if (undoState != UNDO_FAILED) {
			if (gameOver) {
				printf("Player %s wins!\n", playerSymbols[currentPlayer]);
			} else if (undoState == UNDO_REQUESTED) {
				if (backup[!currentPlayer].didChooseSubboard) {
					subboardLoc.name = 0;
				} else {
					subboardLoc = backup[!currentPlayer].subboard;
				}
			} else if (checkStalemate(board, wins, &subboardLoc)) {
				gameOver = 1;
				printf("Stalemate! All spaces on the board have been filled, but nobody won.\n");
			} else if (!isSubboardFull(board[cellLoc.row][cellLoc.col])) {
				subboardLoc = cellLoc;
			} else {
				subboardLoc.name = 0;
			}
			currentPlayer = !currentPlayer;
		}
	}
	return 0;
}
