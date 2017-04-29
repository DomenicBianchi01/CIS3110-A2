all: programs

programs:
	gcc -Wall -std=c99 -Iinclude src/main.c src/parseFile.c src/cpu.c -o a2