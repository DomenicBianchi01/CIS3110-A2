#ifndef __DBIANCHI_CPU__
#define __DBIANCHI_CPU__

struct Thread {

	int ID;
	int processID;
	int status;
	int arrivalTime;
	int serviceTime;
	int finishTime;
	int ioTime;

	struct Burst * burstList;
	struct Thread * next;
};
typedef struct Thread Thread;

struct Event {

	int type;
	int time;
	int matchingIO;
	int threadNum;
	int processID;

	struct Event * next;
};
typedef struct Event Event;

struct Process {

	int ID;
	int numOfThreads;

	struct Thread * threadList;
	struct Process * next;
};
typedef struct Process Process;

struct Burst {

	int cpu;
	int io;

	struct Burst * next;
};
typedef struct Burst Burst;

struct Verbose {

	int time;
	char string[1000];

	struct Verbose * next;
};
typedef struct Verbose Verbose;

/**
 * createProcess
 * Creates a node containing data specific to a process
 * IN: int processNum, int numOfThreads
 * OUT: Process
 * POST: A process node is returned
 * ERROR: If the text file is not formatted correctly, an error will occur because parsing will fail
 **/
Process * createProcess(int processNum, int numOfThreads);

/**
 * createThread
 * Creates a node containing data specific to a thread
 * IN: int threadNum, int arrivalTime, int status, int processID
 * OUT: Thread
 * POST: A thread node is returned
 * ERROR: If the text file is not formatted correctly, an error will occur because parsing will fail
 **/
Thread * createThread(int threadNum, int arrivalTime, int status, int processID);

/**
 * createThreadWithBursts
 * Creates a thread node containing nformation specific to the thread, including burst information
 * IN: int threadNum, int arrivalTime, int status, int processID, Burst * burst
 * OUT: Thread
 * POST: A thread node is returned
 * ERROR: If the text file is not formatted correctly, an error will occur because parsing will fail
 **/
Thread * createThreadWithBursts(int threadNum, int arrivalTime, int status, int processID, Burst * burst);

/**
 * createBurst
 * Creates a burst node containing all the burst information (cpu and io burst times) for a thread
 * IN: int cpu, int io
 * OUT: Burst
 * POST: A burst node is returned
 * ERROR: If the text file is not formatted correctly, an error will occur because parsing will fail
 **/
Burst * createBurst(int cpu, int io);

/**
 * createEvent
 * Creates an event node that is used to tell the simulation what to do
 * IN: int type, int time, int matchingIO, int num, int processID
 * OUT: Event
 * POST: An event node is returned
 * ERROR: If for some reason the clock is incorrect, the event timming will be off
 **/
Event * createEvent(int type, int time, int matchingIO, int num, int processID);

/**
 * createVerboseString
 * Creates a node that contains a string with information regarding verbose mode
 * IN: int time, char string[]
 * OUT: Verbose
 * POST: A verbose node is returned
 * ERROR: If malloc fails, the string will not be saved
 **/
Verbose * createVerboseString(int time, char string[]);

/**
 * addBurstToThread
 * Links a burst node to its corresponding thread
 * IN: Thread * currentThread, Burst * toAdd
 * OUT: Thread
 * POST: A thread node with its linked burst node(s) is returned
 * ERROR: If the burst node was not malloced correctly, an error may occur
 **/
Thread * addBurstToThread(Thread * currentThread, Burst * toAdd);

/**
 * addThreadToProcess
 * Links a thread node to its corresponding process
 * IN: Process * currentProcess, Thread * toAdd
 * OUT: Process
 * POST: A process node with its linked thread node(s) is returned
 * ERROR: If the thread node was not malloced correctly, an error may occur
 **/
Process * addThreadToProcess(Process * currentProcess, Thread * toAdd);

/**
 * addBurstToBack
 * Adds a burst node to the back of a list of bursts
 * IN: Burst * theList, Burst * toBeAdded
 * OUT: Burst
 * POST: A list of bursts is returned
 * ERROR: If malloc failed for the burst node that was to be added, an error may occur
 **/
Burst * addBurstToBack(Burst * theList, Burst * toBeAdded);

/**
 * addThreadToBack
 * Adds a thread node to the back of a list of threads
 * IN: Thread * theList, Thread * toBeAdded
 * OUT: Thread
 * POST: A list of threads is returned
 * ERROR: If malloc failed for the thread node that was to be added, an error may occur
 **/
Thread * addThreadToBack(Thread * theList, Thread * toBeAdded);

/**
 * addProcessToBack
 * Adds a process node to the back of a list of processes
 * IN: Process * theList, Process * toBeAdded
 * OUT: Process
 * POST: A list of processes is returned
 * ERROR: If malloc failed for the process node that was to be added, an error may occur
 **/
Process * addProcessToBack(Process * theList, Process * toBeAdded);

/**
 * addString
 * Adds a string node to the back of a list of strings (for verbose mode)
 * IN: Verbose * theList, Verbose * toBeAdded
 * OUT: Verbose
 * POST: A list of strings is returned
 * ERROR: If malloc failed for the verbose node that was to be added, an error may occur
 **/
Verbose * addString(Verbose * theList, Verbose * toBeAdded);

/**
 * addEventToQueue2
 * Adds an event node to the event queue using insertion sort (sorted by arrival times)
 * IN: Event * theList, Event * toBeAdded
 * OUT: Event
 * POST: A list of events is returned (in the form of a sorted queue)
 * ERROR: If malloc failed for the event node that was to be added, an error may occur
 **/
Event * addEventToQueue2(Event * theList, Event * toBeAdded);

/**
 * addThreadToQueue
 * Adds a thread node to the back of the ready queue
 * IN: Thread * theList, Thread * toBeAdded
 * OUT: Thread
 * POST: A list of threads is returned (in the form of a queue)
 * ERROR: If malloc failed for the thread node that was to be added, an error may occur
 **/
Thread * addThreadToQueue(Thread * theList, Thread * toBeAdded);

/**
 * simulation
 * Conducts the CPU simulation
 * IN: Process * processNode, int * clock, int * totalOffset, Verbose ** toPrint, int threadSwitch, int processSwitch, int quantum, bool verbos, bool roundRobin
 * OUT: None
 * POST: CPU simulation is complete and results are printed to the trminal
 * ERROR: If the proper events are created for some reason, errors will occur
 **/
void simulation(Process * processNode, int * clock, int * totalOffset, Verbose ** toPrint, int threadSwitch, int processSwitch, int quantum, bool verbos, bool roundRobin);

/**
 * processNewThread
 * Assign a thread to the CPU to be processed
 * IN: Thread ** cpuProcess, Thread ** readyQueue, Event ** eventQueue, Verbose * toPrint, int * oldProcessNum, int * totalOffset, int * clock, bool roundRobin, bool verbos, int processSwitch, int threadSwitch, int quantum
 * OUT: None
 * POST: A new thready has been assigned to the CPU and any events required have also been created
 * ERROR: If malloc fails at any time during the simulation, errors will occur
 **/
void processNewThread(Thread ** cpuProcess, Thread ** readyQueue, Event ** eventQueue, Verbose * toPrint, int * oldProcessNum, int * totalOffset, int * clock, bool roundRobin, bool verbos, int processSwitch, int threadSwitch, int quantum);

/**
 * calculateUtilAndTurnaround
 * Calculate the CPU utilization and average turnaround after the simulation is complete
 * IN: Process * head, int * processCount, double * cpuUtilization, int * totalTurnover
 * OUT: None
 * POST: CPU util and turnaround has been calculated
 **/
void calculateUtilAndTurnaround(Process * head, int * processCount, double * cpuUtilization, int * totalTurnover);

/**
 * calculateAndDisplayBasicStats
 * Calculate the CPU utilization and average turnaround after the simulation is complete and display the results
 * IN: double cpuUtilization, int turnaroundTotal, int processCount, int quantum, int clock, bool roundRobin
 * OUT: None
 * POST: Basic stats have been calculated
 **/
void calculateAndDisplayBasicStats(double cpuUtilization, int turnaroundTotal, int processCount, int quantum, int clock, bool roundRobin);

/**
 * printVerboseMove
 * Display the text for verbose mode to the terminal screen
 * IN: verbose * toPrint
 * OUT: None
 * POST: Verbose mode information printed to terminal screen
 **/
void printVerboseMode(Verbose * toPrint);

/**
 * printDetailMove
 * Display the text for detail mode to the terminal screen
 * IN: Process * head
 * OUT: None
 * POST: Verbose mode information printed to terminal screen
 **/
void printDetailMode(Process * head);

#endif
