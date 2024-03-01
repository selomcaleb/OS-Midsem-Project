#include "utils/create_page_table.h"
#include "utils/create_processes.h"
#include "utils/page_table_entry.h"
#include "utils/process.h"
#include <stdio.h>

int main() {
    // Create the master page table
    PageTableEntry** masterPageTable = createMasterPageTable();
    printf("Master page table created\n");

    // create the processes
    Process* processes = createProcesses(3);
    printf("Processes created\n");


}