#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 10

// Define the structure for the frame
typedef struct {
    int frameNumber;
    int pageNumber;
} FrameEntry;

typedef struct {
    int capacity;
    FrameEntry frames[NUM_FRAMES];
} FrameTable;

void initializeFrameTable(FrameTable* frameTable) {
    frameTable->capacity = NUM_FRAMES;
    int capacity = frameTable->capacity;
    printf("capacity is %d\n", capacity);

    for (int i = 0; i < capacity; i++) {
        frameTable->frames[i].frameNumber = i;
        frameTable->frames[i].pageNumber = -1;
    }
}

int trackNumberFreeFrames(FrameTable* frameTable) {
    int freeCount = 0;
    for (int i = 0; i < frameTable->capacity; i++) {
        if (frameTable->frames[i].pageNumber == -1) {
            freeCount += 1;
        }
    }
    return freeCount;
}

int trackNumberAllocatedFrames(FrameTable* frameTable){
	int allocatedCount = 0;
	for (int i=0; i< frameTable->capacity;i++){
		if (frameTable->frames[i].pageNumber != -1){
			allocatedCount+=1;
		}

	}
	return allocatedCount;
}

int frameIsAllocated(FrameTable* frameTable, int frame){
	if (frameTable->frames[frame].pageNumber!=-1){
		return 0;
	}
	return 1;
}
int main() {
    FrameTable frameTable;
    initializeFrameTable(&frameTable);
    printf("The number of free frames is %d\n", trackNumberFreeFrames(&frameTable));
	frameTable.frames[0].pageNumber = 100;
	int allocated = frameIsAllocated(&frameTable, 0);
	if (allocated == 0){
		printf("Frame has been allocated\n");
	}
	printf("The number of free frames is %d\n", trackNumberFreeFrames(&frameTable));
	printf("The number of allocated frames is %d\n", trackNumberAllocatedFrames(&frameTable));

    return 0;
}
