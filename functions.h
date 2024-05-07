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
	char isSubboardFull(const int [BOARD_SIZE][BOARD_SIZE]);

#endif
