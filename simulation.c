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

int main() {
    // Create the master page table
    PageTableEntry** masterPageTable = createMasterPageTable();

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

        // Assign Frames To Each Page in the Page Table
        for (int j=0; j<5; j++) {
            int freeFrame = firstFreeFrame(&frameTable);
            frameTable.frames[freeFrame].pageNumber = j;
            frameTable.frames[freeFrame].frameNumber = freeFrame;
            frameTable.frames[freeFrame].processID = processes[i].processID;

        }
        TLB tlb;
        intializeTLB(&tlb);
        if (lookupPageNumber(&tlb, masterPageIndexBaseTen==-1)){
            printf("There is a page fault accessing the page number %d", masterPageIndexBaseTen);
            if (addToTLB(&tlb, masterPageIndexBaseTen, &pageTable)==false){
                updateTLB(&tlb, masterPageIndexBaseTen, &pageTable);
            }
        }



//         Add The Page Table To The Master Page Table
        masterPageTable[masterPageIndexBaseTen] = pageTable;
    }
    printFrameTable(&frameTable);

}