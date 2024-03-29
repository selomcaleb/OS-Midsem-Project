#ifndef OS_MIDSEM_PROJECT_MEMORY_VALUES_H
#define OS_MIDSEM_PROJECT_MEMORY_VALUES_H
// defined in bytes

#define PHYSICAL_MEMORY_SIZE 1024
#define VIRTUAL_MEMORY_SIZE 4096
#define PAGE_SIZE 16

//calculate the number of pages and frames
#define NUM_PAGES VIRTUAL_MEMORY_SIZE / PAGE_SIZE
#define NUM_FRAMES PHYSICAL_MEMORY_SIZE / PAGE_SIZE

#endif //OS_MIDSEM_PROJECT_MEMORY_VALUES_H
