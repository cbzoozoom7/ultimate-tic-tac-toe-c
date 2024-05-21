// main.h
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#ifndef MAIN_H
	#define MAIN_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "defs.h"
	#include "functions.h"
	#define PROMPT_LENGTH 70
	typedef enum {
		NORMAL = 0,
		UNDO_REQUESTED = 1,
		UNDO_FAILED = -1
	} UndoStatus;
	
#endif
