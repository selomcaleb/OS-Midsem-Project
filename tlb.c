#include <stdio.h>
#include "utils/create_page_table.h"
#include <Kernel/stdbool.h>
#define TLB_SIZE 4

/**
 * The TLBEntry struct represents an entry in a Translation Lookaside Buffer with page number, frame
 * number, and LRU counter fields.
 * @property {int} page_number - The `page_number` property in the `TLBEntry` struct represents the
 * page number associated with a particular entry in the Translation Lookaside Buffer (TLB). The TLB is
 * a cache that stores mappings between virtual memory addresses and physical memory addresses to speed
 * up the translation process during memory access.
 * @property {int} frame_number - The `frame_number` property in the `TLBEntry` struct represents the
 * physical frame number where the corresponding page is stored in memory.
 * @property {int} lru_counter - The `lru_counter` in the `TLBEntry` struct is likely used to implement
 * a Least Recently Used (LRU) replacement policy in a Translation Lookaside Buffer (TLB). This counter
 * helps keep track of the order in which TLB entries are accessed, allowing the system to identify
 */
typedef struct{
	int page_number;
	PageTableEntry** pte;
	int lru_counter;	
}TLBEntry;

typedef struct{
	TLBEntry entries[TLB_SIZE];
	int next_lru_counter;
}TLB;


int hits = 0;
int pagefaults = 0;

/**
 * The function initializes a Translation Lookaside Buffer (TLB) by setting all entries to default
 * values.
 * 
 * @param tlb The function `initializeTLB` initializes a Translation Lookaside Buffer (TLB) by setting
 * all its entries to default values. The TLB is represented by a struct named `TLB`, and the function
 * takes a pointer to a `TLB` structure as a parameter.
 */
void intializeTLB(TLB* tlb){
	for(int i=0; i<TLB_SIZE; i++){
		tlb->entries[i].page_number = -1;
		tlb->entries[i].pte = NULL;
		tlb->entries[i].lru_counter = 0;
	}
}


/**
 * The function `lookupPageNumber` checks if a given page number is present in a Translation Lookaside
 * Buffer (TLB) and updates hit or page fault counts accordingly.
 * 
 * @param tlb The TLB (Translation Lookaside Buffer) is a cache that stores recently used
 * virtual-to-physical address translations. In the provided function, the TLB is a pointer to a
 * structure containing entries with page numbers.
 * @param page_number The `page_number` parameter in the `lookupPageNumber` function represents the
 * page number that we are trying to look up in the Translation Lookaside Buffer (TLB). The function
 * iterates through the TLB entries to check if there is a match with the provided `page_number`. If a
 * 
 * @return The function `lookupPageNumber` returns an integer value. If there is a hit in the TLB
 * (Translation Lookaside Buffer) for the given page number, it returns 1. If there is a page fault (no
 * matching entry in the TLB), it returns -1.
 */
int lookupPageNumber(TLB *tlb, int page_number){
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb->entries[i].page_number == page_number) {
            hits += 1;
            printf("There is a hit with page number %d\n", page_number);
            return 1;
        }
    }


    //printf("There is a page fault accessing page number %d\n", page_number);
    pagefaults += 1;
    return -1;
}


bool addToTLB(TLB* tlb, int page_number, PageTableEntry** pte){
	// check if the TLB is full
	for (int i = 0; i < TLB_SIZE; i++) {
		if (tlb->entries[i].page_number == -1) {
			tlb->entries[i].page_number = page_number;
			tlb->entries[i].pte = pte;
			tlb->entries[i].lru_counter = tlb->next_lru_counter++;
			return true;
		}
	}
	return false;

}

void updateTLB(TLB* tlb, int page_number,PageTableEntry** pte) {
    int lru_index = 0;
    // Find the LRU entry
    for (int i = 1; i < TLB_SIZE; i++) {
        if (tlb->entries[i].lru_counter < tlb->entries[lru_index].lru_counter) {
            lru_index = i;
        }
    }
    // Update the LRU entry with new page and frame numbers
    tlb->entries[lru_index].page_number = page_number;
    tlb->entries[lru_index].pte = pte ;
    // Reset LRU counter for the updated entry to mark it as the most recently used
    tlb->entries[lru_index].lru_counter = tlb->next_lru_counter++;
}


void displayStatics(){
	printf("The number of page faults are:%d\n", pagefaults);
	printf("The number of hits are:%d\n", hits);
}

