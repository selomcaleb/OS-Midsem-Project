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
#include <unistd.h>

#define MASTER_PAGE_SIZE 16
#define OFFSET_SIZE 32


void displayStatistics(FrameTable *frameTable, int numberAccess, int hits, int pageFaults, int processID) {
    double hit_rate = round(((double)hits / numberAccess) * 100);
    int framesOccupied = memoryUtilizedByProcess(frameTable, processID);
    double memoryUtilized = round(((double)framesOccupied / frameTable->capacity) * 100);

    printf("Printing TLB Statistics For This Page Table From Process With ID = %d\n", processID);
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");
    printf("| Process ID | Total Accesses | Hits | Hit Rate | Page Faults | Memory Utilization |\n");
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");
    printf("|     %4d   |      %6d     | %4d | %6.2f%% |    %6d    |       %6.2f%%     |\n",
           processID, numberAccess, hits, hit_rate, pageFaults, memoryUtilized);
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");
}

int main() {
    srand(time(NULL));
    // Create the master page table
   MasterPageTable masterPageTable;
    intializeMasterTable(&masterPageTable);

    //initialize the TLB
    TLB tlb;
    intializeTLB(&tlb);


    // Create a frame table
    FrameTable frameTable;
    initializeFrameTable(&frameTable);

    printf("+-------------------------------Simulation Starting-------------------------------+\n");
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");
    printf("Master Page Table: Size = %d\n", MASTER_PAGE_SIZE);
    printf("Total Physical Memory: Size = %d\n", PHYSICAL_MEMORY_SIZE);
    printf("Total Virtual Memory: Size = %d\n", VIRTUAL_MEMORY_SIZE);
    printf("Page Size = %d\n", PAGE_SIZE);
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");

    // Create the processes
    int NUM_PROCESSES = 8;

    Process *processes = createProcesses(NUM_PROCESSES);
    printf("+------------+----------------+------+----------+-------------+-------------------+\n");

    // Loop through the processes (Simulating FCFS)
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process with ID = %d Created...\n", processes[i].processID);
        int memoryRequested = processes[i].memoryRequested;
        int numPagesRequired = calculatePagesRequired(memoryRequested);
        printf("The Number of Pages Required for This Process with ID = %d are %d\n", processes[i].processID, numPagesRequired);

        // First generate the master page index (randomly)
        sleep(1);
        int masterPageIndexBaseTen = rand() % MASTER_PAGE_TABLE_SIZE;
        sleep(1);

        int masterPageIndexBaseTwo = generatePageIndex(masterPageIndexBaseTen);

        // Create Page Table
        printf("Creating Page Table of Size = %d\n", numPagesRequired);
        PageTableEntry *pageTable = createPageTable(numPagesRequired);

        //Add The Page Table To The Master Page Table
        MasterEntry masterEntry;
        masterEntry.page_number = masterPageIndexBaseTen;
        masterEntry.pte =  pageTable;
        masterPageTable.entries[masterPageIndexBaseTen] = masterEntry;

        // Inner Page Indexes Allocated
        int pageIndexesAllocated[numPagesRequired];

        // Offsets Allocated
        int offsetsAllocated[numPagesRequired];

        // assign index to each page entry in the page table
        for (int j = 0; j < numPagesRequired; j++) {
            int innerPageIndexBaseTen = j;
            int innerPageIndexBaseTwo = generatePageIndex(innerPageIndexBaseTen);
            pageIndexesAllocated[j] = innerPageIndexBaseTwo;
            sleep(1);
            int offsetBaseTen = rand() * numPagesRequired;
            sleep(1);
            int offsetBaseTwo = generateOffset(offsetBaseTen);
            offsetsAllocated[j] = offsetBaseTwo;

            // Generate random logical address for each page
            printf("Page Entry #%d has a logical address of ", innerPageIndexBaseTen);
            printGeneratedAddress(masterPageIndexBaseTwo, innerPageIndexBaseTwo, offsetBaseTwo);
        }
        printf("+------------+----------------+------+----------+-------------+-------------------+\n");

        printf("Assigning Frames To Each Page in the Page Table\n");
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
            pageTable[k].frame_number=freeFrame;
            printf("Assigned Page Entry #%d to Frame Number #%d\n", k, freeFrame);
        }

        printf("Added New Page Table to Master Page Table. Index in Master Page Table = %d\n", masterPageIndexBaseTen);
        printf("+------------+----------------+------+----------+-------------+-------------------+\n");


        int pageFaults = 0;
        int hits = 0;
        int numberAccess = 0;
        printf("Trying To Access Page Table From The TLB...\n");
        for (int l = 0; l < sizeof(pageIndexesAllocated) / sizeof(pageIndexesAllocated[0]); l++) {
            //perform TLB lookup

            int lookup = lookupPageNumber(&tlb, masterPageIndexBaseTen);
            // Increment numberAccess by 1 whether it is a page fault or a hit.
            numberAccess += 1;
            if (lookup == -1) {
                pageFaults += 1;
                printf("There is a Page Fault Accessing the Page Table with Index = %d From The TLB\n", masterPageIndexBaseTen);
                printf("Now Adding to the TLB...\n");
                if (addToTLB(&tlb, masterPageIndexBaseTen, &pageTable) == 0) {
                    printf("Could not add to TLB\n");
                    updateTLB(&tlb, masterPageIndexBaseTen, &pageTable);

                    // access the frame
                    MasterEntry entry = masterPageTable.entries[masterPageIndexBaseTen];
                    int frameNumber =entry.pte[l].frame_number;
                    printf("The Frame Number for Page Entry #%d of Process Number %d is: %d\n", pageIndexesAllocated[l],
                           processes[i].processID, frameNumber);
                }
            } else {
                hits += 1;
                MasterEntry entry = masterPageTable.entries[masterPageIndexBaseTen];
                int frameNumber =entry.pte[l].frame_number;
                printf("The Frame Number for Page Entry #%d of Process Number %d is: %d\n", pageIndexesAllocated[l],
                       processes[i].processID, frameNumber);
            }
        }

        sleep(1);
        int randomValueForExtraMemoryAccess = rand() * 10;
        sleep(1);
        // No need for extra memory
        if (randomValueForExtraMemoryAccess >= 7) {
            printf("+------------+----------------+------+----------+-------------+-------------------+\n");
            printFrameTable(&frameTable);
            displayStatistics(&frameTable, numberAccess, hits, pageFaults, processes[i].processID);
            printf("\n");
            printf("\n");
        }

        else {
            // Request For Memory
            printf("+------------+----------------+------+----------+-------------+-------------------+\n");
            printf("Process with ID = %d is Requesting Extra Memory of Size = %d\n", processes[i].processID, processes[i].memoryRequested + 32);
            int newMemoryRequested = processes[i].memoryRequested + 32;
            int newNumPagesRequired = calculatePagesRequired(newMemoryRequested);
            printf("The Number of Pages in the New Page Table Required for This Process with ID = %d are %d\n", processes[i].processID, newNumPagesRequired);
            printf("+------------+----------------+------+----------+-------------+-------------------+\n");

            // Create Page Table
            printf("Creating Page Table of Size = %d\n", newNumPagesRequired);
            PageTableEntry *newPageTable = createPageTable(newNumPagesRequired);

            printf("+------------+----------------+------+----------+-------------+-------------------+\n");

            printf("Assigning Frames To Each Page in the Page Table\n");
            // first check if there are enough free frames for this process pages coming in
            int newFreeFrames = trackNumberFreeFrames(&frameTable);

            if (newFreeFrames < newNumPagesRequired) {
                printf("No free frames available\n");
                break;
            }

            //Assign Frames To Each Page in the Page Table
            for (int k = 0; k < newNumPagesRequired; k++) {
                int freeFrame = firstFreeFrame(&frameTable);
                frameTable.frames[freeFrame].pageNumber = k;
                frameTable.frames[freeFrame].frameNumber = freeFrame;
                frameTable.frames[freeFrame].processID = processes[i].processID;

                //updating inner page table
                pageTable[k].frame_number=freeFrame;
                printf("Assigned Page Entry #%d to Frame Number #%d\n", k, freeFrame);
            }
            printf("+------------+----------------+------+----------+-------------+-------------------+\n");
            printf("+------------+----------------+------+----------+-------------+-------------------+\n");
        }
    }
    printf("+-------------------------------Simulation Ended-------------------------------+\n");
}