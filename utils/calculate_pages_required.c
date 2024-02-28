#include "memory_values.h"

/**
 * The function calculates the number of pages required based on the given number of bytes and the page
 * size.
 * 
 * @param numBytes The `numBytes` parameter represents the total number of bytes that need to be
 * stored. The function `calculatePagesRequired` calculates the number of pages required to store these
 * bytes based on a predefined `PAGE_SIZE`. 
 * 
 * @return The function `calculatePagesRequired` returns the number of pages required to store the
 * given number of bytes, based on the `PAGE_SIZE` constant.
 */
int calculatePagesRequired(int numBytes) {
    int numPages = 0;
    if (numBytes % PAGE_SIZE == 0) {
        numPages = numBytes / PAGE_SIZE;
    } else {
        numPages = (numBytes / PAGE_SIZE) + 1;
    }
    return numPages;
}