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
#define STARLINE "**************************\n"
#define MASTER_PAGE_SIZE 16


//function to display statistics

void displayStatistics(FrameTable *frameTable, int numberAccess, int hits, int pageFaults, int processID){
    double hit_rate = (hits/numberAccess)*100;
    int framesOccupied = memoryUtilizedByProcess(frameTable, processID);
    double memoryUtilized = (framesOccupied/frameTable->capacity)*100;
    printf("Total number of times process %d tried to access memory is %d:\n",processID, numberAccess);
    printf("The number of  hits for accessing process %d pages are:\n", processID, hits);
    printf("The hit rate for process number %f is :\n", processID, hit_rate);
    printf("The number of page faults for process %d is %d:\n",processID, pageFaults);
    printf("The memory utilized by process %d is %d\n", processID, memoryUtilized);
}
int main() {

    // Create the master page table
    PageTableEntry** masterPageTable = createMasterPageTable();

    //intialize the TLB
    TLB tlb;
    intializeTLB(&tlb);


    // Create a frame table
    FrameTable frameTable;
    initializeFrameTable(&frameTable);

    printf("Master page table created\n");
    printf(STARLINE);

    // Create the processes
    int NUM_PROCESSES = 3;

    Process* processes = createProcesses(NUM_PROCESSES);
    printf("Processes created\n");
    printf(STARLINE);

    // Loop through the processes (Simulating FCFS)
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int memoryRequested = processes[i].memoryRequested;
        int numPagesRequired = calculatePagesRequired(memoryRequested);

        // Generate random logical address for each page

        // First generate the master page index (randomly)
        srand(time(NULL));
        int masterPageIndexBaseTen = rand() % MASTER_PAGE_SIZE;

        // Create Page Table
        PageTableEntry* pageTable = createPageTable(numPagesRequired);
        
        // first check if there are enough free frames for this process pages coming in
        int freeFrames = trackNumberFreeFrames(&frameTable);

        // if(freeFrames<numPagesRequired){printf("No free frames available"); break}

        // Assign Frames To Each Page in the Page Table
        for (int j=0; j<5; j++) {
            int freeFrame = firstFreeFrame(&frameTable);
            frameTable.frames[freeFrame].pageNumber = j;
            frameTable.frames[freeFrame].frameNumber = freeFrame;
            frameTable.frames[freeFrame].processID = processes[i].processID;

        }
        //perform TLB lookup 
        if (lookupPageNumber(&tlb, masterPageIndexBaseTen==-1)){
            printf("There is a page fault accessing the page number %d", masterPageIndexBaseTen);
            if (addToTLB(&tlb, masterPageIndexBaseTen, &pageTable)==false){
                updateTLB(&tlb, masterPageIndexBaseTen, &pageTable);
            }
        }



        //Add The Page Table To The Master Page Table
        masterPageTable[masterPageIndexBaseTen] = pageTable;
    }
    printFrameTable(&frameTable);

}