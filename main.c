//main.c
//ultimate-tic-tac-toe-c
//copyright Christopher Bowman 2024
//created Fri 3 May 2024
#include "main.h"
int main(void) {
	char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][CELL_LENGTH]; // Think of them like nested 2D arrays, not a 4D array.
	char playerSymbols[][CELL_LENGTH] = {"\x1b[31mX\x1b[0m", "\x1b[33mO\x1b[0m"}; // {"X" in red, "O" in blue}
	int currentPlayer = 0; // bool used as index for playerSymbols
	char gameOver = 0; // bool used to end the game
	for (int bigRow = 0; bigRow < BOARD_SIZE; bigRow++) { // Initialize the game board with spaces
		for (int bigCol = 0; bigCol < BOARD_SIZE; bigCol++) {
			for (int smallRow = 0; smallRow < BOARD_SIZE; smallRow++) {
				for (int smallCol = 0; smallCol < BOARD_SIZE; smallCol++) {
					strcpy(board[bigRow][bigCol][smallRow][smallCol], " ");
				}
			}
		}
	}
	BoardLocation subboardLoc;
	subboardLoc.name = 0;
	while (!gameOver) {
		printf("1|2|3\n");
		printf("-+-+-\n");
		printf("4|5|6\n");
		printf("-+-+-\n");
		printf("7|8|9\n");
		char prompt[PROMPT_LENGTH];
		if (subboardLoc.name == 0) {
			snprintf(prompt, PROMPT_LENGTH, "Player %s, which sub-board would you like to play in?", playerSymbols[currentPlayer]);
			getInput(prompt, &subboardLoc);
			while (isSubboardFull(board[subboardLoc.row][subboardLoc.col])) {
				printf("Invalid choice; sub-board %c is already full or won.\n", subboardLoc.name);
				getInput(prompt, &subboardLoc);
			}
		}
		snprintf(prompt, PROMPT_LENGTH, "Player %s, which cell in sub-board %c would you like to mark?", playerSymbols[currentPlayer], subboardLoc.name);
		BoardLocation cellLoc;
		getInput(prompt, &cellLoc);
		while (strcmp(board[subboardLoc.row][subboardLoc.col][cellLoc.row][cellLoc.col], " ") != 0) {
			printf("Invalid choice; sub-board %c, cell %c is already marked.\n", subboardLoc.name, cellLoc.name);
			getInput(prompt, &cellLoc);
		}
		strcpy(board[subboardLoc.row][subboardLoc.col][cellLoc.row][cellLoc.col], playerSymbols[currentPlayer]);
		for (int bigRow = 0; bigRow < BOARD_SIZE; bigRow++) { // print the board
			for (int smallRow = 0; smallRow < BOARD_SIZE; smallRow++) {
				for (int bigCol = 0; bigCol < BOARD_SIZE; bigCol++) {
					for (int smallCol = 0; smallCol < BOARD_SIZE; smallCol++) {
						printf("%s", board[bigRow][bigCol][smallRow][smallCol]);
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
		gameOver = currentPlayer; // TODO: Check for wins
		currentPlayer = !currentPlayer;
		if (!isSubboardFull(board[cellLoc.row][cellLoc.col])) {
			subboardLoc = cellLoc;
		} else {
			subboardLoc.name = 0;
		}
	}
	return 0;
}
