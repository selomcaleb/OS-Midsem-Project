#include <stdio.h>

// defined in bytes

#define PHYSICAL_MEMORY_SIZE 1024
#define VIRTUAL_MEMORY_SIZE 4096
#define PAGE_SIZE 512

//calculate the number of pages and frames
#define NUM_PAGES VIRTUAL_MEMORY_SIZE / PAGE_SIZE
#define NUM_FRAMES PHYSICAL_MEMORY_SIZE / PAGE_SIZE


typedef struct {
    int frame_number;
    int valid;
} PageTableEntry;

PageTableEntry page_table[VIRTUAL_MEMORY_SIZE];

typedef struct {
    int data;
} PhysicalMemoryFrame;


PhysicalMemoryFrame physical_memory[PHYSICAL_MEMORY_SIZE];


//function for page allocation
void allocate_page(int page_number){
    int frame_number = allocate_frame();
    if (frame_number == -1) {
        printf("Failed to allocate a frame for page %d due to lack of available frames.\n", page_number);
        return; 
    }
    page_table[page_number].frame_number = frame_number;
    page_table[page_number].valid = 1;
}

//function for page deallocation
void deallocate_page(int page_number){

}


int page_faults = 0;

int num_frames = 0; //supposed to equal NUM_FRAMES

int allocated_frames = 0;

//void handlePageFault(int page_number){
//	page_faults+=1;
//	int frame_number = rand()%NUM_FRAMES;
//	page_table[page_number] = frame_number;
//	page_table[page_number].valid = 1;
//	printf("Loading data from secondary storage for page %d to frame %d in memory", page_number, frame_number );
//}





