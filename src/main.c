/**********************
 Assignment #2
 Domenic Bianchi
 0921557
 February 27, 2017
 This program simulates how a CPU would behave when having to deal with multiple processes and threads using both First Come First Serve and Round Robin algorithms
 ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parseFile.h"
#include "cpu.h"

int main(int argc, char * argv[]) {

	int threadSwitch = 0;
	int processSwitch = 0;
	int clock = 0;
	int processCount = 0;
	int quantum = 0;
	int totalSwitch = 0;
	int totalTurnover = 0;
	double cpuUtilization = 0;
	bool verbose = false;
	bool detail = false;
	bool roundRobin = false;
	Process * head = NULL;
	Verbose * toPrint = NULL;

	//Determine which flags have been set and should be run with the program
	for (int i = 1; argv[i] != NULL; i++) {

		if (strcmp(argv[i], "-d") == 0) {

			detail = true;
		}
		else if (strcmp(argv[i], "-v") == 0) {

			verbose = true;
		}
		else if (strcmp(argv[i], "-r") == 0) {

			roundRobin = true;
			quantum = atoi(argv[i+1]);
		}
	}

	//Read input file to get data required for simulation
	head = parseDataFile(&threadSwitch, &processSwitch);

	//Conduct the simulation
	simulation(head, &clock, &totalSwitch, &toPrint, threadSwitch, processSwitch, quantum, verbose, roundRobin);
	//Calculate the cpu util and average turnaround
	calculateUtilAndTurnaround(head, &processCount, &cpuUtilization, &totalTurnover);
	//Print the cpu util, average turnaround, and total run time
	calculateAndDisplayBasicStats(cpuUtilization, totalTurnover, processCount, quantum, clock, roundRobin);

	//If verbose and/or detail mode have been selected, print out the required text
	if (verbose == true) {

		printVerboseMode(toPrint);
	}

	if (detail == true) {

		printDetailMode(head);
	}

	return 0;
}
