// defs.h
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#ifndef DEFS_H
	#define DEFS_H
	#define BOARD_SIZE 3
	#define CELL_LENGTH 11 // = length of (color + player symbol + color reset + null terminator)
	#define NUM_PLAYERS 2
	typedef struct { // stores the indices and name of a location on the board
		signed char row;
		signed char col;
		char name;
	} BoardLocation;
	typedef signed char Subboard[BOARD_SIZE][BOARD_SIZE];
	typedef struct {
		BoardLocation subboard;
		BoardLocation cell;
		char didChooseSubboard; // bool that the specifies whether the play could choose the subboard
	} GameState;

#endif
