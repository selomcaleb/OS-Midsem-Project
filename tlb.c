#include <stdio.h>
#define TLB_SIZE 4;

typedef struct{
	int page_number;
	int frame_number;
	int lru_counter;
	
}TLBEntry;

typedef struct{
	TLBEntry entries[TLB_SIZE];
}TLB;


int hits = 0;
int pagefaults = 0;

void intializeTLB(TLB* tlb){
	for(int i=0; i<TLB_SIZE; i++){
		tlb->entries[i].page_number = -1;
		tlb->entries[i].frame_number = -1;
		tlb->entries[i].lru_counter = 0;
	}
}


int lookupPageNumber(TLB *tlb, int page_number){
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb->entries[i].page_number == page_number) {
            hits += 1;
            printf("There is a hit with page number %d\n", page_number);
            return 1;
        }
    }


    printf("There is a page fault accessing page number %d\n", page_number);
    pagefaults += 1;
    return -1;
}

