# Memory Management System with Paging Techniques

This project implements a memory management system using paging techniques in C. The system simulates processes accessing memory, handles page faults, and tracks memory utilization, page faults, and hit rate. It also provides options to analyze and optimize memory efficiency by comparing different page replacement algorithms.

## Objectives

- Understand the concepts of address spaces, address translation, and paging.
- Implement a memory management system using paging techniques.
- Simulate processes accessing memory and observe paging behavior.
- Analyze and optimize the system for memory efficiency.

## Design

### Define Memory Spaces

- Virtual Memory Size: 4096 bytes (4 KB)
- Physical Memory Size: 2048 bytes (2 KB)

### Page Size Calculation

- Chosen Page Size: 512 bytes

- Number of Pages = Virtual Memory Size / Page Size = 4096 bytes / 512 bytes = 8 pages
- Number of Frames = Physical Memory Size / Page Size = 2048 bytes / 512 bytes = 4 frames

### Data Structures

- Page Table Entry
- Page Table
- Physical Memory Frame

### Functionality

1. Address translation from virtual to physical addresses.
2. Page allocation and deallocation (simulating memory requests).
3. Handling page faults (simulating missing pages in memory).
4. Tracking free and allocated frames.

## Implementation

The code is written in C and consists of modules to perform the defined functionalities. It uses functions like `malloc` and `free` for memory allocation. Processes access memory by generating random memory addresses, and address translation is done using the page table. Page faults are handled by fetching the required page from secondary storage.

## Analysis and Optimization

Different workloads are simulated with varying process sizes and memory access patterns to analyze memory utilization, page faults, and hit rate. Various page replacement algorithms such as FIFO, LRU, and Clock are implemented and compared to optimize memory usage and reduce page faults. The trade-offs between different algorithms are discussed.

## Deliverables

- C code with clear comments and documentation.
- A report explaining the design, implementation, analysis, and optimization of the memory management system.
- Presentation of the project findings.

## Usage

## Contributors
- [Chudah Yakung](https://github.com/chudah1)
- [Oheneba Dade](https://github.com/selomcaleb)
- [Selom Caleb Arcmann-Ackummey](https://github.com/Oheneba-Dade)

   
