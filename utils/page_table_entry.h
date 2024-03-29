#ifndef OS_MIDSEM_PROJECT_STRUCT_H
#define OS_MIDSEM_PROJECT_STRUCT_H
#define MASTER_PAGE_TABLE_SIZE 16

/**
 * The above type defines a structure representing an entry in a page table with fields for frame
 * number and validity.
 * @property {int} frame_number - The `frame_number` property in the `PageTableEntry` struct typically
 * represents the physical frame number where the corresponding page is stored in memory. This value is
 * used by the operating system to quickly locate the page in physical memory when needed.
 * @property {int} valid - The `valid` property in the `PageTableEntry` struct typically represents
 * whether the corresponding page in memory is currently valid or not.
 */
typedef struct {
    int frame_number;
    int valid;
} PageTableEntry;

typedef struct {
    int capacity;
    PageTableEntry *entries;
} PageTable;


typedef struct{
    int page_number;
    PageTableEntry* pte;
}MasterEntry;

typedef struct{
    MasterEntry entries[MASTER_PAGE_TABLE_SIZE];
}MasterPageTable;

#endif //OS_MIDSEM_PROJECT_STRUCT_H


