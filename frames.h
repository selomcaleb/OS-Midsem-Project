#ifndef OS_MIDSEM_PROJECT_FRAMES_H
#define OS_MIDSEM_PROJECT_FRAMES_H

#include "utils/memory_values.h"

// Define the structure for the frame
typedef struct {
    int frameNumber;
    int pageNumber;
    int processID;
} FrameEntry;

typedef struct {
    int capacity;
    FrameEntry frames[NUM_FRAMES];
} FrameTable;

void initializeFrameTable(FrameTable* frameTable);
int trackNumberFreeFrames(FrameTable* frameTable);
int trackNumberAllocatedFrames(FrameTable* frameTable);
int frameIsAllocated(FrameTable* frameTable, int frame);
int firstFreeFrame(FrameTable* frameTable);
void printFrameTable(FrameTable *frameTable);

#endif //OS_MIDSEM_PROJECT_FRAMES_H
