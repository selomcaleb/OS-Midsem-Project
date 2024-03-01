#ifndef OS_MIDSEM_PROJECT_CREATE_PAGE_TABLE_H
#define OS_MIDSEM_PROJECT_CREATE_PAGE_TABLE_H
#include "page_table_entry.h"

PageTableEntry* createPageTable(int numPages);
PageTableEntry** createMasterPageTable();

#endif //OS_MIDSEM_PROJECT_CREATE_PAGE_TABLE_H
