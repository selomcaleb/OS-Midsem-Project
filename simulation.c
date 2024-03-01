#include "utils/create_page_table.h"
#include "utils/create_processes.h"
#include "utils/page_table_entry.h"
#include "utils/process.h"
#include "utils/calculate_pages_required.h"
#include "utils/generate_random_address.h"
#include "frames.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tlb.h"
#include <math.h>
#define STARLINE "**************************\n"
#define MASTER_PAGE_SIZE 16
#define OFFSET_SIZE 32


//function to display statistics

void displayStatistics(FrameTable *frameTable, int numberAccess, int hits, int pageFaults, int processID){
    double hit_rate = round(((double)hits/numberAccess)*100);
    int framesOccupied = memoryUtilizedByProcess(frameTable, processID);
    double memoryUtilized = round(((double)framesOccupied/frameTable->capacity)*100);
    printf("Total number of times process %d tried to access memory is %d:\n",processID, numberAccess);
    printf("The number of  hits for accessing process %d pages are:%d\n", processID, hits);
    printf("The hit rate for process number %d is :%.2f%%\n", processID, hit_rate);
    printf("The number of page faults for process %d is %d:\n",processID, pageFaults);
    printf("The memory utilized by process %d is %.2f%%\n", processID, memoryUtilized);
}
int main() {

    // Create the master page table
    PageTableEntry **masterPageTable = createMasterPageTable();

    //intialize the TLB
    TLB tlb;
    intializeTLB(&tlb);


    // Create a frame table
    FrameTable frameTable;
    initializeFrameTable(&frameTable);

    printf("Master page table created\n");
    printf(STARLINE);

    // Create the processes
    int NUM_PROCESSES = 6;

    Process *processes = createProcesses(NUM_PROCESSES);
    printf("Processes created\n");
    printf(STARLINE);

    // Loop through the processes (Simulating FCFS)
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int memoryRequested = processes[i].memoryRequested;
        int numPagesRequired = calculatePagesRequired(memoryRequested);
        printf("The number of pages required for process %d are %d\n", i, numPagesRequired);
        printf("");
        printf("");

        // Generate random logical address for each page

        // First generate the master page index (randomly)
        srand(time(NULL));
        int masterPageIndexBaseTen = rand() % MASTER_PAGE_SIZE;



        // Create Page Table
        PageTableEntry *pageTable = createPageTable(numPagesRequired);

        //Add The Page Table To The Master Page Table
        masterPageTable[masterPageIndexBaseTen] = pageTable;

        // Inner Page Indexes Allocated
        int pageIndexesAllocated[numPagesRequired];

        // Offsets Allocated
        int offsetsAllocated[numPagesRequired];

        // assign index to each page entry in the page table
        for (int j = 0; j < numPagesRequired; j++) {
            int innerPageIndexBaseTen = rand() % numPagesRequired;
            int innerPageIndexBaseTwo = generatePageIndex(innerPageIndexBaseTen);
            pageIndexesAllocated[j] = innerPageIndexBaseTwo;
            int offsetBaseTen = rand() * 32;
            int offsetBaseTwo = generatePageIndex(offsetBaseTen);
            offsetsAllocated[j] = offsetBaseTwo;
        }


        // first check if there are enough free frames for this process pages coming in
        int freeFrames = trackNumberFreeFrames(&frameTable);

        if (freeFrames < numPagesRequired) {
            printf("No free frames available\n");
            break;
        }


        //Assign Frames To Each Page in the Page Table
        for (int k = 0; k < numPagesRequired; k++) {
            int freeFrame = firstFreeFrame(&frameTable);
            frameTable.frames[freeFrame].pageNumber = k;
            frameTable.frames[freeFrame].frameNumber = freeFrame;
            frameTable.frames[freeFrame].processID = processes[i].processID;

            //updating inner page table
            pageTable[k].frame_number =freeFrame;
        }

        int pageFaults = 0;
        int hits = 0;
        int numberAccess = 0;

        for (int l = 0; l < sizeof(pageIndexesAllocated) / sizeof(pageIndexesAllocated[0]); l++) {
            //perform TLB lookup

            int lookup = lookupPageNumber(&tlb, masterPageIndexBaseTen);
            // Increment numberAccess by 1 whether it is a page fault or a hit.
            numberAccess += 1;
            if (lookup == -1) {
                pageFaults += 1;
                printf("There is a page fault accessing the page number %d\n", masterPageIndexBaseTen);
                if (addToTLB(&tlb, masterPageIndexBaseTen, &pageTable) == 0) {
                    printf("Could not add to TLB\n");
                    updateTLB(&tlb, masterPageIndexBaseTen, &pageTable);
                    // access the frame
                    PageTableEntry *entry = masterPageTable[masterPageIndexBaseTen];

                    int frameNumber = entry->frame_number;
                    printf("The frame number for page number %d of process number %d is: %d\n", pageIndexesAllocated[l],
                           processes[i].processID, frameNumber);
                }
            } else {
                hits += 1;
                PageTableEntry* entry = masterPageTable[masterPageIndexBaseTen];
                int frameNumber = entry->frame_number;
                printf("The frame number for page number %d of process number %d is: %d\n", pageIndexesAllocated[l],processes[i].processID, frameNumber);

            }

        }
        printFrameTable(&frameTable);
        displayStatistics(&frameTable, numberAccess, hits, pageFaults, processes[i].processID);
        printf("\n");
        printf("\n");


    }

}