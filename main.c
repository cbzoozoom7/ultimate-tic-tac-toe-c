//main.c
//ultimate-tic-tac-toe-c
//Copyright Christopher Bowman 2024
//Created Fri 3 May 2024
#include "main.h"
int main(void) {
	char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
	for (int bigRow = 0; bigRow < BOARD_SIZE; bigRow++) {
		for (int bigCol = 0; bigCol < BOARD_SIZE; bigCol++) {
			for (int smallRow = 0; smallRow < BOARD_SIZE; smallRow++) {
				for (int smallCol = 0; smallCol < BOARD_SIZE; smallCol++) {
					board[bigRow][bigCol][smallRow][smallCol] = '0';
				}
			}
		}
	}
}
