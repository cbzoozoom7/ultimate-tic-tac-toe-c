// functions.h
// ultimate-tic-tac-toe-c
// Copyright Christopher Bowman 2024
// created Fri 3 May 2024
#ifndef FUNCTIONS_H
	#define FUNCTIONS_H
	#include <stdio.h>
	#include <string.h>
	#include "defs.h"
	void getInput(const char *, BoardLocation *);
	char ***getSubboard(const char [BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][CELL_LENGTH], const BoardLocation *);
	char *getCell(const char [BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][CELL_LENGTH], const BoardLocation *, const BoardLocation *);
	char isSubboardFull(const char [BOARD_SIZE][BOARD_SIZE][CELL_LENGTH]);

#endif
