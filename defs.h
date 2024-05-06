// defs.h
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#ifndef DEFS_H
	#define DEFS_H
	#define BOARD_SIZE 3
	#define CELL_LENGTH 11 // = length of (color + player symbol + color reset + null terminator)
	typedef struct { // stores the indices and name of a location on the board
		char name;
		int row;
		int col;
	} BoardLocation;
	typedef char cell[CELL_LENGTH];
	typedef cell subboard[BOARD_SIZE][BOARD_SIZE];

#endif
