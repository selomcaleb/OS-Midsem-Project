#ifndef OS_MIDSEM_PROJECT_TLB_H
#define OS_MIDSEM_PROJECT_TLB_H

#include "utils/create_page_table.h"
#include <Kernel/stdbool.h>

#define TLB_SIZE 4
typedef struct{
    int page_number;
    PageTableEntry** pte;
    int lru_counter;
}TLBEntry;

typedef struct{
    TLBEntry entries[TLB_SIZE];
    int next_lru_counter;
}TLB;

void intializeTLB(TLB* tlb);
int lookupPageNumber(TLB *tlb, int page_number);
bool addToTLB(TLB* tlb, int page_number, PageTableEntry** pte);
void updateTLB(TLB* tlb, int page_number,PageTableEntry** pte);
void displayStatics();

#endif //OS_MIDSEM_PROJECT_TLB_H
