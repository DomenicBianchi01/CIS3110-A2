#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cpu.h"
#include "parseFile.h"

Process * createProcess(int processNum, int numOfThreads) {

	Process * current;

	//Malloc memory for the Process node
	current = malloc(sizeof(Process));

	//If the malloc fails, do not create the node
	if (current == NULL)  {

		free(current);
		return NULL;
	}

	current->ID = processNum;
	current->numOfThreads = numOfThreads;
	current->threadList = NULL;
	current->next = NULL;

	return current;
}

Verbose * createVerboseString(int time, char string[]) {

	Verbose * current;

	//Malloc memory for the Verbose node
	current = malloc(sizeof(Verbose));

	//If the malloc fails, do not create the node
	if (current == NULL)  {

		free(current);
		return NULL;
	}

	current->time = time;
	strcpy(current->string, string);

	return current;
}

Thread * createThread(int threadNum, int arrivalTime, int status, int processID) {

	Thread * current;

	//Malloc memory for the Thread node
	current = malloc(sizeof(Thread));

	//If the malloc fails, do not create the node
	if (current == NULL)  {

		free(current);
		return NULL;
	}

	current->ID = threadNum;
	current->processID = processID;
	current->arrivalTime = arrivalTime;
	current->status = status;
	current->serviceTime = 0;
	current->finishTime = 0;
	current->ioTime = 0;
	current->burstList = NULL;
	current->next = NULL;

	return current;
}

Thread * createThreadWithBursts(int threadNum, int arrivalTime, int status, int processID, Burst * burst) {

	Thread * current;

	//Malloc memory for the Thread node
	current = malloc(sizeof(Thread));

	//If the malloc fails, do not create the node
	if (current == NULL)  {

		free(current);
		return NULL;
	}

	current->ID = threadNum;
	current->processID = processID;
	current->arrivalTime = arrivalTime;
	current->status = status;
	current->serviceTime = 0;
	current->finishTime = 0;
	current->ioTime = 0;
	current->burstList = burst;
	current->next = NULL;

	return current;
}

Burst * createBurst(int cpu, int io) {

	Burst * current;

	//Malloc memory for the Burst node
	current = malloc(sizeof(Burst));

	//If the malloc fails, do not create the node
	if (current == NULL)  {

		free(current);
		return NULL;
	}

	current->cpu = cpu;
	current->io = io;
	current->next = NULL;

	return current;
}

Event * createEvent(int type, int time, int ioTime, int num, int processID) {

	Event * current;

	//Malloc memory for the Event node
	current = malloc(sizeof(Event));

	//If the malloc fails, do not create the node
	if (current == NULL)  {

		free(current);
		return NULL;
	}

	current->type = type;
	current->time = time;
	current->matchingIO = ioTime;
	current->threadNum = num;
	current->processID = processID;
	current->next = NULL;

	return current;
}

Thread * addBurstToThread(Thread * currentThread, Burst * toAdd) {

	//Add the node to the end of the list
	currentThread->burstList = addBurstToBack(currentThread->burstList, toAdd);

	return currentThread;
}

Process * addThreadToProcess(Process * currentProcess, Thread * toAdd) {

	//Add the node to the end of the list
	currentProcess->threadList = addThreadToBack(currentProcess->threadList, toAdd);

	return currentProcess;
}

Verbose * addString(Verbose * theList, Verbose * toBeAdded) {

	Verbose * listStart = theList;
	bool inserted = false;

	//If no list exists
	if (theList == NULL) {

		return toBeAdded;
	}

	//Add to front
	if (theList->time > toBeAdded->time) {

		toBeAdded->next = theList;
		return toBeAdded;
	}

	//Insertion sort
	while (theList->next != NULL) {

		if (theList->next->time > toBeAdded->time) {

			toBeAdded->next = theList->next;
			theList->next = toBeAdded;
			inserted = true;
			break;
		}

		theList = theList->next;
	}

	if (inserted == false) {

		theList->next = toBeAdded;
	}

	return listStart;
}

Burst * addBurstToBack(Burst * theList, Burst * toBeAdded) {

	Burst * temp;

	//If no list exists
	if (theList == NULL) {

		return toBeAdded;
	}
	//Go to the end of the list
	else if (theList->next != NULL) {

		temp = addBurstToBack(theList->next, toBeAdded);
	}
	//Add to back of the list
	else {

		theList->next = toBeAdded;
	}

	return theList;
}

Thread * addThreadToBack(Thread * theList, Thread * toBeAdded) {

	Thread * temp;

	//If no list exists
	if (theList == NULL) {

		return toBeAdded;
	}
	//Go to the end of the list
	else if (theList->next != NULL) {

		temp = addThreadToBack(theList->next, toBeAdded);
	}
	//Add to the back of the list
	else {

		theList->next = toBeAdded;
	}

	return theList;
}

Event * addEventToQueue2(Event * theList, Event * toBeAdded) {

	Event * listStart = theList;
	bool inserted = false;

	//If no list exists
	if (theList == NULL) {

		return toBeAdded;
	}

	//Add to front
	if (theList->time > toBeAdded->time) {

		toBeAdded->next = theList;
		return toBeAdded;
	}

	//Insertion sort
	while (theList->next != NULL) {

		if (theList->next->time > toBeAdded->time) {

			toBeAdded->next = theList->next;
			theList->next = toBeAdded;
			inserted = true;
			break;
		}

		theList = theList->next;
	}

	if (inserted == false) {

		theList->next = toBeAdded;
	}

	return listStart;
}

Process * addProcessToBack(Process * theList, Process * toBeAdded) {

	Process * temp;

	//If no list exists
	if (theList == NULL) {

		return toBeAdded;
	}
	//Go to the end of the list
	else if (theList->next != NULL) {

		temp = addProcessToBack(theList->next, toBeAdded);
	}
	//Add to the back of the list
	else {

		theList->next = toBeAdded;
	}

	return theList;
}

Thread * addThreadToQueue(Thread * theList, Thread * toBeAdded) {

	Thread * temp;

	//If no list exists
	if (theList == NULL) {

		return toBeAdded;
	}
	//Go to the end of the list
	else if (theList->next != NULL) {

		temp = addThreadToQueue(theList->next, toBeAdded);
	}
	//Add to the back of the list
	else {

		theList->next = toBeAdded;
	}

	return theList;
}

void calculateUtilAndTurnaround(Process * head, int * processCount, double * cpuUtilization, int * totalTurnover) {

	//Loop through all processes
	while (head != NULL) {

		Thread * threadList = head->threadList;
		int startTime = -1;
		int endTime = -1;

		*processCount = *processCount + 1;

		//Loop through all threads in the current process
		while (threadList != NULL) {

			//Get the serivce time of the thread
			*cpuUtilization = *cpuUtilization + (double)threadList->serviceTime;

			//Find the thread that arrived the soonest
			if (threadList->arrivalTime < startTime || startTime == -1) {

				startTime = threadList->arrivalTime;
			}

			//Find the thread that arrived the latest
			if (threadList->finishTime > endTime) {

				endTime = threadList->finishTime;
			}

			threadList = threadList->next;
		}

		*totalTurnover = *totalTurnover + (endTime - startTime);

		head = head->next;
	}
}

void calculateAndDisplayBasicStats(double cpuUtilization, int totalTurnover, int processCount, int quantum, int clock, bool roundRobin) {

	cpuUtilization = ((cpuUtilization)/clock)*100;
	totalTurnover = totalTurnover/processCount;

	//Display the mode the program is being run in and print the basic stats
	if (roundRobin == true) {

		printf("\nRound Robin (quantum = %d time units)\n\n", quantum);
	}
	else {

		printf("\nFirst Come First Serve\n\n");
	}

	printf("\nTotal time required is %d time units\n", clock);
	printf("Average turnaround time is %d time units\n", totalTurnover);
	printf("CPU Utilization: %.02f%%\n\n", cpuUtilization);
}

void printVerboseMode(Verbose * toPrint) {

	//Print all strings in the list
	while (toPrint != NULL) {

		printf("%s\n", toPrint->string);
		Verbose * temp = toPrint;
		toPrint = toPrint->next;
		free(temp);
	}
}

void printDetailMode(Process * head) {

	//Loop through all processes
	while (head != NULL) {

		Thread * threadList = head->threadList;

		//Loop through all threads in the current process and print out detailed information about the thread
		while (threadList != NULL) {

			printf("Thread %d of Process %d\n", threadList->ID, threadList->processID);
			printf("Arrival Time: %d\n", threadList->arrivalTime);
			printf("Service Time: %d\n", threadList->serviceTime);
			printf("IO Time: %d\n", threadList->ioTime);
			printf("Turnaround Time: %d\n", threadList->finishTime - threadList->arrivalTime);
			printf("Finish Time: %d\n", threadList->finishTime);
			printf("\n");

			threadList = threadList->next;
		}

		head = head->next;
	}
}

void processNewThread(Thread ** cpuProcess, Thread ** readyQueue, Event ** eventQueue, Verbose * toPrint, int * oldProcessNum, int * totalOffset, int * clock, bool roundRobin, bool verbos, int proccesSwitch, int threadSwitch, int quantum) {

	Event * eventToAdd = NULL;

	//Assign the cpu a new thread (from the front of the ready queue)
	*cpuProcess = *readyQueue;
	*readyQueue = (*readyQueue)->next;

	//Determine if a process switch and/or thread switch is required
	if (*oldProcessNum != (*cpuProcess)->processID) {

		*clock = *clock + proccesSwitch + threadSwitch;
		*totalOffset = *totalOffset + proccesSwitch + threadSwitch;
	}
	else {

		*clock = *clock + threadSwitch;
		*totalOffset = *totalOffset + threadSwitch;
	}

	*oldProcessNum = (*cpuProcess)->processID;

	//Create an event for time slice
	if (roundRobin == true && (*cpuProcess)->burstList->cpu > quantum) {

		eventToAdd = createEvent(5, quantum+*clock, (*cpuProcess)->burstList->io, (*cpuProcess)->ID, (*cpuProcess)->processID);
		*eventQueue = addEventToQueue2(*eventQueue, eventToAdd);
	}
	//Create an event for interrupt
	else if ((*cpuProcess)->burstList->io != -1) {
		eventToAdd = createEvent(2, (*cpuProcess)->burstList->cpu+*clock, (*cpuProcess)->burstList->io, (*cpuProcess)->ID, (*cpuProcess)->processID);
		*eventQueue = addEventToQueue2(*eventQueue, eventToAdd);
	}
	//Create an event for Completion
	else {
		eventToAdd = createEvent(4, (*cpuProcess)->burstList->cpu+*clock, -1, (*cpuProcess)->ID, (*cpuProcess)->processID);
		*eventQueue = addEventToQueue2(*eventQueue, eventToAdd);
	}

	//Create string for verbos mode (if mode is enabled)
	if (verbos == true) {

		char temp[1000];
		char temp2[100];
		clearArray(temp, 1000);
		clearArray(temp2, 100);
		strcat(temp, "At time ");
		sprintf(temp2, "%d", *clock);
		strcat(temp, temp2);
		clearArray(temp2, 100);
		strcat(temp, ": Thread ");
		sprintf(temp2, "%d", (*cpuProcess)->ID);
		strcat(temp, temp2);
		clearArray(temp2, 100);
		strcat(temp, " of Process ");
		sprintf(temp2, "%d", (*cpuProcess)->processID);
		strcat(temp, temp2);
		strcat(temp, " moves from Ready to Running");

		Verbose * string = createVerboseString(*clock, temp);
		*toPrint = *addString(toPrint, string);
	}
}

void simulation(Process * processNode, int * clock, int * totalOffset, Verbose ** toPrint, int threadSwitch, int proccesSwitch, int quantum, bool verbos, bool roundRobin) {

	int oldProcessNum = 0;
	Thread * readyQueue = NULL;
	Thread * list = NULL;
	Thread * saveList = NULL;
	Thread * cpuProcess = NULL;
	Thread * threadNode = NULL;
	Process * saveProcessList = processNode;
	Event * eventQueue = NULL;
	Event * eventToAdd = NULL;

	//Load all thread arrival events into the event queue
	while (saveProcessList != NULL) {

		threadNode = saveProcessList->threadList;

		while (threadNode != NULL) {

			//Create thread arrival event
			eventToAdd = createEvent(1, threadNode->arrivalTime+*clock, 0, threadNode->ID, threadNode->processID);
			eventQueue = addEventToQueue2(eventQueue, eventToAdd);

			Burst * tempList = threadNode->burstList;

			//Calculate total service time and io time
			while (tempList != NULL) {

				threadNode->serviceTime = threadNode->serviceTime + tempList->cpu;
				threadNode->ioTime = threadNode->ioTime + tempList->io;
				tempList = tempList->next;
			}

			threadNode->ioTime = threadNode->ioTime + 1;

			Thread * threadToAdd = createThreadWithBursts(threadNode->ID, threadNode->arrivalTime, threadNode->status, threadNode->processID, threadNode->burstList);
			list = addThreadToBack(list, threadToAdd);

			threadNode = threadNode->next;
		}

		saveProcessList = saveProcessList->next;
	}

	saveList = list;

	threadNode = processNode->threadList;

	//Main simualation loop. Simulation ends when there are no more events in the event queue
	while (eventQueue != NULL) {

		//Pop off next event from event queue
		Event * currentEvent = eventQueue;
		eventQueue = eventQueue->next;

		//Set the clock to the event time
		*clock = currentEvent->time;

		//If event is a thread arrival
		if (currentEvent->type == 1) {

			list = saveList;

			while (list != NULL) {

				//Search for the matching thread in the master thread list
				if (currentEvent->threadNum == list->ID && currentEvent->processID == list->processID) {

					if (verbos == true) {

						char temp[1000];
						char temp2[100];
						clearArray(temp, 1000);
						clearArray(temp2, 100);
						strcat(temp, "At time ");
						sprintf(temp2, "%d", *clock);
						strcat(temp, temp2);
						clearArray(temp2, 100);
						strcat(temp, ": Thread ");
						sprintf(temp2, "%d", list->ID);
						strcat(temp, temp2);
						clearArray(temp2, 100);
						strcat(temp, " of Process ");
						sprintf(temp2, "%d", list->processID);
						strcat(temp, temp2);
						strcat(temp, " moves from New to Ready");

						Verbose * string = createVerboseString(*clock, temp);
						*toPrint = addString(*toPrint, string);
					}

					//Add the thread to the ready queue
					Thread * threadToAdd = createThreadWithBursts(list->ID, list->arrivalTime, list->status, list->processID, list->burstList);
					readyQueue = addThreadToQueue(readyQueue, threadToAdd);

					//If the cpu isn't doing anything, assign the thread that was just added to the ready queue to the cpu
					if (cpuProcess == NULL) {

						processNewThread(&cpuProcess, &readyQueue, &eventQueue, *toPrint, &oldProcessNum, totalOffset, clock, roundRobin, verbos, proccesSwitch, threadSwitch, quantum);
					}
				}

				list = list->next;
			}
		}
		//If event is an interupt
		else if (currentEvent->type == 2) {

			if (verbos == true) {

				char temp[1000];
				char temp2[100];
				clearArray(temp, 1000);
				clearArray(temp2, 100);
				strcat(temp, "At time ");
				sprintf(temp2, "%d", *clock);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, ": Thread ");
				sprintf(temp2, "%d", currentEvent->threadNum);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, " of Process ");
				sprintf(temp2, "%d", currentEvent->processID);
				strcat(temp, temp2);
				strcat(temp, " moves from Running to Blocked");

				Verbose * string = createVerboseString(*clock, temp);
				*toPrint = addString(*toPrint, string);
			}

			cpuProcess = NULL;

			//Create event for io completion
			eventToAdd = createEvent(3, currentEvent->matchingIO+*clock, currentEvent->matchingIO+*clock, currentEvent->threadNum, currentEvent->processID);
			eventQueue = addEventToQueue2(eventQueue, eventToAdd);

			//Assign a new thread to the CPU
			if (readyQueue != NULL) {

				processNewThread(&cpuProcess, &readyQueue, &eventQueue, *toPrint, &oldProcessNum, totalOffset, clock, roundRobin, verbos, proccesSwitch, threadSwitch, quantum);
			}
		}
		//If event is a interupt complete (io completion)
		else if (currentEvent->type == 3) {

			if (verbos == true) {

				char temp[1000];
				char temp2[100];
				clearArray(temp, 1000);
				clearArray(temp2, 100);
				strcat(temp, "At time ");
				sprintf(temp2, "%d", *clock);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, ": Thread ");
				sprintf(temp2, "%d", currentEvent->threadNum);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, " of Process ");
				sprintf(temp2, "%d", currentEvent->processID);
				strcat(temp, temp2);
				strcat(temp, " moves from Blocked to Ready");

				Verbose * string = createVerboseString(*clock, temp);
				*toPrint = addString(*toPrint, string);
			}

			list = saveList;

			while (list != NULL) {

				//Search for the matching thread in the master thread list
				if (currentEvent->threadNum == list->ID && currentEvent->processID == list->processID) {

					//Remove front element of burst linked list (old burst data)
					Burst * temp = list->burstList;
					list->burstList = list->burstList->next;
					free(temp);

					break;
				}

				list = list->next;
			}

			//Add thread to ready queue
			Thread * threadToAdd = createThreadWithBursts(list->ID, list->arrivalTime, list->status, list->processID, list->burstList);
			readyQueue = addThreadToQueue(readyQueue, threadToAdd);

			//If the cpu isn't doing anything, assign the thread that was just added to the ready queue to the cpu
			if (cpuProcess == NULL) {

				processNewThread(&cpuProcess, &readyQueue, &eventQueue, *toPrint, &oldProcessNum, totalOffset, clock, roundRobin, verbos, proccesSwitch, threadSwitch, quantum);
			}
		}
		//If event is thread complete
		else if (currentEvent->type == 4) {

			if (verbos == true) {

				char temp[1000];
				char temp2[100];
				clearArray(temp, 1000);
				clearArray(temp2, 100);
				strcat(temp, "At time ");
				sprintf(temp2, "%d", *clock);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, ": Thread ");
				sprintf(temp2, "%d", currentEvent->threadNum);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, " of Process ");
				sprintf(temp2, "%d", currentEvent->processID);
				strcat(temp, temp2);
				strcat(temp, " moves from Running to Terminated");

				Verbose * string = createVerboseString(*clock, temp);
				*toPrint = addString(*toPrint, string);
			}

			cpuProcess = NULL;

			saveProcessList = processNode;
			Thread * thread = NULL;

			//Find the thread that just completed and record its finish time
			while (saveProcessList != NULL) {

				thread = saveProcessList->threadList;

				while (thread != NULL) {

					if (currentEvent->threadNum == thread->ID && currentEvent->processID == thread->processID) {

						thread->finishTime = *clock;
					}

					thread = thread->next;
				}

				saveProcessList = saveProcessList->next;
			}

			saveProcessList = processNode;

			//Assign new thread to cpu
			if (readyQueue != NULL) {

				processNewThread(&cpuProcess, &readyQueue, &eventQueue, *toPrint, &oldProcessNum, totalOffset, clock, roundRobin, verbos, proccesSwitch, threadSwitch, quantum);
			}
		}
		//If event is a Time Slice
		else if (currentEvent->type == 5) {

			if (verbos == true) {

				char temp[1000];
				char temp2[100];
				clearArray(temp, 1000);
				clearArray(temp2, 100);
				strcat(temp, "At time ");
				sprintf(temp2, "%d", *clock);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, ": Thread ");
				sprintf(temp2, "%d", currentEvent->threadNum);
				strcat(temp, temp2);
				clearArray(temp2, 100);
				strcat(temp, " of Process ");
				sprintf(temp2, "%d", currentEvent->processID);
				strcat(temp, temp2);
				strcat(temp, " moves from Running to Ready");

				Verbose * string = createVerboseString(*clock, temp);
				*toPrint = addString(*toPrint, string);
			}

			//Update CPU burst and add thread back to ready queue
			cpuProcess->burstList->cpu = cpuProcess->burstList->cpu - quantum;
			Thread * threadToAdd = createThreadWithBursts(cpuProcess->ID, cpuProcess->arrivalTime, cpuProcess->status, cpuProcess->processID, cpuProcess->burstList);
			readyQueue = addThreadToQueue(readyQueue, threadToAdd);

			cpuProcess = NULL;

			//Assign a new thread to the cpu
			if (readyQueue != NULL) {

				processNewThread(&cpuProcess, &readyQueue, &eventQueue, *toPrint, &oldProcessNum, totalOffset, clock, roundRobin, verbos, proccesSwitch, threadSwitch, quantum);
			}
		}

		free(currentEvent);
	}
}
