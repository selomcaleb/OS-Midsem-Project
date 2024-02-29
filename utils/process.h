#ifndef OS_MIDSEM_PROJECT_PROCESS_H
#define OS_MIDSEM_PROJECT_PROCESS_H

/**
 * The above type defines a structure for representing a process with attributes such as memory
 * requested, status (alive or dead), and process ID.
 * @property {int} memoryRequested - The `memoryRequested` property in the `Process` struct represents
 * the amount of memory that the process has requested for execution. This value indicates the memory
 * requirement of the process in the system.
 * @property {int} isAlive - The `isAlive` property in the `Process` struct is used to indicate whether
 * the process is alive or dead. A value of 0  represents that the process is dead, while a
 * value of 1 indicates that the process is alive.
 * @property {int} processID - The `processID` property represents the unique
 * identifier for a particular process. It is used to distinguish one process from another in the system.
 */
typedef struct {
    int memoryRequested;
    int isAlive; // 0 means dead, 1 means alive
    int processID;
} Process;

#endif //OS_MIDSEM_PROJECT_PROCESS_H
