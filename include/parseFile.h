#include "cpu.h"

#ifndef __DBIANCHI_PARSEFILE__
#define __DBIANCHI_PARSEFILE__

/**
 * parseDataFile
 * Gets data from a text file (stdin) and creates nodes of processes, threads, and bursts
 * IN: int * threadSwitch, int * processSwitch
 * OUT: Process
 * POST: A list of processes is returned
 * ERROR: If the text file is not formatted correctly, an error will occur
 **/
Process * parseDataFile(int * threadSwitch, int * processSwitch);

/**
 * clearArray
 * Clears all the elements of a char array so the array can be re-used for other purposes elsewhere in the program
 * IN: char string[], int length
 * OUT: None
 * POST: Empties character array
 * ERROR: If the length variable (int length) is shorter than the actually length of the char array, not all elements of the array will be cleared which will result in errors when the array is re-used else where in the program
 **/
void clearArray(char string[], int length);


#endif
