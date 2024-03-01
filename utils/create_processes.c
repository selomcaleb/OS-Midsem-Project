#include "process.h"
#include <stdlib.h>
#include <time.h>

int memorySizes[] = {64, 80, 96, 112, 128, 144, 160}; //divisible by the Page Size = 16
int numSizes = sizeof(memorySizes) / sizeof(memorySizes[0]);

/**
 * The function creates an array of processes with specified attributes such as process ID, status, and
 * requested memory size.
 * 
 * @param numProcesses The `numProcesses` parameter in the `createProcesses` function represents the
 * number of processes that will be created and initialized. This function dynamically allocates memory
 * for an array of `Process` structures based on the specified number of processes. Each process is
 * then assigned a unique process ID, a status of 0 (indicating that the process is not alive), and a
 * randomly generated memory size from the `memorySizes` array.
 * 
 * @return The function `createProcesses` is returning a pointer to an array of `Process` structures.
 */
Process* createProcesses(int numProcesses) {
    Process* processes = (Process*)malloc(numProcesses * sizeof(Process));
    srand(time(NULL));
    for (int i=0; i<numProcesses; i++) {
        processes[i].processID = i+1;
        processes[i].isAlive = 0;
        processes[i].memoryRequested = memorySizes[rand() % numSizes];
    }
    return processes;
}
