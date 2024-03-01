#include <stdlib.h>
#include "page_table_entry.h"

#define MASTER_PAGE_TABLE_SIZE 16

/**
 * The function creates a page table with a specified number of entries, initializing each entry with
 * default values.
 * 
 * @param numPages The `numPages` parameter specifies the number of pages for which the page table
 * needs to be created.
 * 
 * @return A pointer to an array of PageTableEntry structures is being returned.
 */
PageTableEntry* createPageTable(int numPages) {
    PageTableEntry* pageTable = malloc(numPages * sizeof(PageTableEntry));
    for (int i = 0; i < numPages; i++) {
        pageTable[i].frame_number = -1;
        pageTable[i].valid = 0;
    }
    return pageTable;
}

/**
 * The function creates a master page table, which is an array of pointers to PageTableEntry.
 *
 * @return A pointer to an array of pointers to PageTableEntry is being returned.
 */
//PageTable* createMasterPageTable() {
//    PageTable* masterPageTable = malloc(MASTER_PAGE_TABLE_SIZE * sizeof(PageTableEntry*));
//    if (masterPageTable == NULL) {
//        // Handle memory allocation failure
//        return NULL;
//    }
//    for (int i = 0; i < MASTER_PAGE_TABLE_SIZE; i++) {
//        // Initialize each entry to NULL
//        masterPageTable[i] = NULL;
//    }
//    return masterPageTable;
//}

PageTable* createMasterPageTable(int capacity) {
    PageTable* pageTable = malloc(sizeof(PageTable));
    if (pageTable != NULL) {
        pageTable->capacity = capacity;
        pageTable->entries = malloc(capacity * sizeof(PageTableEntry));
        if (pageTable->entries == NULL) {
            free(pageTable); // Free previously allocated memory
            return NULL; // Memory allocation failed for entries
        }
        // Initialize entries or set them to NULL if needed
    }
    return pageTable;
}

void intializeMasterTable(MasterPageTable* masterPageTable){
    for(int i=0; i<MASTER_PAGE_TABLE_SIZE; i++){
        masterPageTable->entries[i].page_number = -1;
        masterPageTable->entries[i].pte = NULL;
    }
}
