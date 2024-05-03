// functions.c
// ultimate-tic-tac-toe-c
// copyright Christopher Bowman 2024
// created Fri 3 May 2024
#include "functions.h"
int getInput(const char *prompt) {
	int input = -1;
	char isBadInput = 1; // bool
	while (isBadInput) {
		printf("%s ", prompt);
		scanf("%d", &input);
		if (input > 9 || input < 1) {
			printf("Invalid input. Please enter a number 1–9.\n");
		} else {
			isBadInput = 0;
		}
	}
	return input;
}