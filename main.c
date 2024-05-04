//main.c
//ultimate-tic-tac-toe-c
//copyright Christopher Bowman 2024
//created Fri 3 May 2024
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
					strcpy(board[bigRow][bigCol][smallRow][smallCol], "X");
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
		int inputBoardRow, inputBoardCol;
		int inputBoard = getInput(prompt, &inputBoardRow, &inputBoardCol);
		while (isSmallBoardFull(board[inputBoardRow][inputBoardCol])) {
			printf("Invalid choice; board %d is already full or won.\n", inputBoard);
			inputBoard = getInput(prompt, &inputBoardRow, &inputBoardCol);
		}
		snprintf(prompt, PROMPT_LENGTH, "Player %s, which cell in board %d would you like to mark?", playerSymbols[currentPlayer], inputBoard);
		int inputCellRow, inputCellCol;
		int inputCell = getInput(prompt, &inputCellRow, &inputCellCol);
		while (strcmp(board[inputBoardRow][inputBoardCol][inputCellRow][inputCellCol], " ") != 0) {
			printf("Invaild choice; board %d, cell %d is already marked.\n", inputBoard, inputCell);
			inputCell = getInput(prompt, &inputCellRow, &inputCellCol);
		}
		strcpy(board[inputBoardRow][inputBoardCol][inputCellRow][inputCellCol], playerSymbols[currentPlayer]);
		// TODO: Print board
		currentPlayer = !currentPlayer;
		gameOver = 1; // TODO: Check for wins
	}
	return 0;
}
