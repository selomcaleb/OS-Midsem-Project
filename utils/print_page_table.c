#include <stdlib.h>
#include <stdio.h>
#include "page_table_entry.h"
#include "create_page_table.h"

void print_page_table(PageTableEntry* pageTable) {
    printf("Page Table:\n");
    for (int i = 0; i < sizeof(pageTable) / sizeof(pageTable[0]); i++) {
        printf("Page %d - Frame Number: %d, Valid: %d\n", i, pageTable[i].frame_number, pageTable[i].valid);
    }
}