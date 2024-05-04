# makefile
# ultimate-tic-tac-toe-c
# copyright Christopher Bowman 2024
# created Fri 3 May 2024
a.out: main.o functions.o
	gcc main.o functions.o
main.o: main.c main.h defs.h
	gcc -c -Wall main.c
functions.o: functions.c functions.h defs.h
	gcc -c -Wall functions.c
clean:
	rm main.o functions.o
