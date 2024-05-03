//main.c
//ultimate-tic-tac-toe-c
//Copyright Christopher Bowman 2024
//Created Fri 3 May 2024
#include "main.h"
int main(void) {
	char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][CELL_LENGTH]; // Think of them like nested 2D arrays, not a 4D array.
	char playerSymbols[][CELL_LENGTH] = {"\x1b[31mX\x1b[0m", "\x1b[33mO\x1b[0m"}; // {"X" in red, "O" in blue}
	int currentPlayer = 0; // index for playerSymbols
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
		printf("Player %s, which board would you like to play in? ", playerSymbols[currentPlayer]);
		gameOver = 1;
	}
}
