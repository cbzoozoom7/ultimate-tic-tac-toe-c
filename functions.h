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
	char isSubboardFull(const Subboard);
	char checkWin(Subboard, const BoardLocation *, Subboard, const BoardLocation *); // == 0 when the player did not win the subboard, 1 when the player did, & 2 when the player won the game.

#endif
