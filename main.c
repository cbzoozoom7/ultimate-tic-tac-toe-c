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
	while (!gameOver) {
		printf("1|2|3\n");
		printf("-+-+-\n");
		printf("4|5|6\n");
		printf("-+-+-\n");
		printf("7|8|9\n");
		char prompt[PROMPT_LENGTH];
		snprintf(prompt, PROMPT_LENGTH, "Player %s, which board would you like to play in?", playerSymbols[currentPlayer]);
		BoardLocation *userBoard = malloc(sizeof(BoardLocation));
		getInput(prompt, userBoard);
		while (isSmallBoardFull(board[userBoard->row][userBoard->col])) {
			printf("Invalid choice; board %c is already full or won.\n", userBoard->name);
			getInput(prompt, userBoard);
		}
		snprintf(prompt, PROMPT_LENGTH, "Player %s, which cell in board %c would you like to mark?", playerSymbols[currentPlayer], userBoard->name);
		BoardLocation *userCell = malloc(sizeof(BoardLocation));
		getInput(prompt, userCell);
		while (strcmp(board[userBoard->row][userBoard->col][userCell->row][userCell->col], " ") != 0) {
			printf("Invalid choice; board %c, cell %c is already marked.\n", userBoard->name, userBoard->name);
			getInput(prompt, userCell);
		}
		strcpy(board[userBoard->row][userBoard->col][userCell->row][userCell->col], playerSymbols[currentPlayer]);
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
		free(userBoard);
		free(userCell);
	}
	return 0;
}
