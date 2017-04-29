#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parseFile.h"
#include "cpu.h"

Process * parseDataFile(int * threadSwitch, int * processSwitch) {

	char input[256];
	int numOfThreads = 0;
	int processNum = 0;
	int numOfProcesses = 0;
	int threadNum = 0;
	int arrivalTime = 0;
	int numberOfBursts = 0;
	int cpuBurstTime = 0;
	int ioBurstTime = 0;
	int burstCounter = 0;
	int processCounter = 0;
	int threadCounter = 1;
	int index = 0;
	bool getNumOfProcesses = true;
	bool getProcessInfo = false;
	bool getThreadInfo = false;
	bool getThreadBursts = false;

	Process * currentProcess = NULL;
	Process * processList = NULL;
	Thread * currentThread = NULL;
	Burst * currentBurst = NULL;

	clearArray(input, 256);

	while (fgets(input, 256, stdin) != NULL) {

		//Determine number of processes, value of thread switch, and value of process switch in the file
		if (getNumOfProcesses == true) {

			char temp[256];
			clearArray(temp, 256);
			int count = 0;

			for (int i = 0; i < strlen(input); i++) {

				strcat(temp, &input[i]);

				//When the first space is reached, that means we have parsed the number of processes
				if (input[i] == ' ' && count == 0) {

					count = count + 1;

					numOfProcesses = atoi(temp);
					clearArray(temp, 256);
				}
				//When the second space is reached, that means we have parsed the value of thread switch
				else if (input[i] == ' ' && count == 1) {

					count = count + 1;

					*threadSwitch = atoi(temp);
					clearArray(temp, 256);
				}
			}

			//When the end of the line is reached, we have parsed the value of process switch
			*processSwitch = atoi(temp);
			clearArray(temp, 256);

			getNumOfProcesses = false;
			getProcessInfo = true;
		}
		//Determine data regarding the process (number of threads, process number)
		else if (getProcessInfo == true) {

			char temp[256];
			clearArray(temp, 256);

			for (int i = 0; i < strlen(input); i++) {

				strcat(temp, &input[i]);

				//When the first space is reached, means we have parsed the process number. Everything after is the number of threads in the process
				if (input[i] == ' ') {

					getProcessInfo = false;
					processNum = atoi(temp);
					clearArray(temp, 256);
				}
			}

			numOfThreads = atoi(temp);
			clearArray(temp, 256);

			//Create a node that will hold all process information
			currentProcess = createProcess(processNum, numOfThreads);

			getThreadInfo = true;
			getProcessInfo = false;
		}
		//Determine data regarding the thread (number of bursts, arrival time, and thread number)
		else if (getThreadInfo == true) {

			char temp[256];
			clearArray(temp, 256);
			int count = 0;

			for (int i = 0; i < strlen(input); i++) {

				strcat(temp, &input[i]);

				//When the first space is reached, means we have parsed the thread number
				if (input[i] == ' ' && count == 0) {

					count = count + 1;

					threadNum = atoi(temp);
					clearArray(temp, 256);
				}
				//When the next space is reached, means we have parsed the arrival time of the thread. Everything after contains the number of bursts
				else if (input[i] == ' ' && count == 1) {

					count = count + 1;

					arrivalTime = atoi(temp);
					clearArray(temp, 256);
				}
			}

			numberOfBursts = atoi(temp);
			clearArray(temp, 256);

			getThreadInfo = false;
			getThreadBursts = true;
			//Create a node for the thread that was just parsed
			currentThread = createThread(threadNum, arrivalTime, 0, processNum);
		}
		//Determine cpu and io bursts for the thread
		else if (getThreadBursts == true) {

			burstCounter = burstCounter + 1;

			char temp[256];
			clearArray(temp, 256);
			int count = 0;

			for (int i = 0; i < strlen(input); i++) {

				strcat(temp, &input[i]);

				//When the first space is reached, means that the burst number has been parsed
				if (input[i] == ' ' && count == 0) {

					count = count + 1;

					index = atoi(temp);
					clearArray(temp, 256);
				}
				///When the next space is reached, means that the cpu burst time has been parsed. Everything after is the io burst time
				else if (input[i] == ' ' && count == 1) {

					count = count + 1;

					cpuBurstTime = atoi(temp);
					clearArray(temp, 256);
				}
			}

			ioBurstTime = atoi(temp);
			clearArray(temp, 256);

			//Given the burst count that was parsed when looking for the thread, if the counter equals the # of bursts, merge burst nodes and thread nodes with the process node (all info about the process has been parsed and is ready to be linked together)
			if (burstCounter == numberOfBursts) {

				getThreadBursts = false;
				cpuBurstTime = ioBurstTime;
				ioBurstTime = -1;

				//Given the thread count that was parsed when looking for the process, if the counter does not equal the # of threads, link the thread node to the process node
				if (threadCounter != numOfThreads) {

					getThreadInfo = true;
					threadCounter = threadCounter + 1;
					burstCounter = 0;

					currentProcess = addThreadToProcess(currentProcess, currentThread);
				}
				//Given the process count that was parsed from the first line of the text file, if the counter does not equal the # of processes, and proccess to a linked list of all procceses
				else if (processCounter != numOfProcesses) {

					getProcessInfo = true;
					threadCounter = 1;
					burstCounter = 0;

					//Link thread to process and add process to a list of processes
					currentProcess = addThreadToProcess(currentProcess, currentThread);
					processList = addProcessToBack(processList, currentProcess);
				}
			}

			//Create the burst node and link it to the thread
			currentBurst = createBurst(cpuBurstTime, ioBurstTime);
			currentThread = addBurstToThread(currentThread, currentBurst);
		}

		clearArray(input, 256);
	}

	return processList;
}

void clearArray(char string[], int length) {

	//Set entire array to null terminators
	for (int j = 0; j < length; j++) {
		
		string[j] = '\0';
	}
}
