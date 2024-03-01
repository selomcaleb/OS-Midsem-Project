#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "create_page_table.h"

/**
 * The function `generatePageIndex` converts a decimal number to a 4-bit binary number.
 * 
 * @param num The `num` parameter in the `generatePageIndex` function is an integer value that is used
 * to generate a binary index. The function takes this integer `num` and converts it into a 4-bit
 * binary representation by extracting the individual bits from `num` and constructing the binary
 * number.
 * 
 * @return The function `generatePageIndex` takes an integer `num` as input, converts it to a 4-bit
 * binary number by extracting each bit from `num`, and then returns the binary number as an integer.
 * 4-bit because we are representing page indices as 4 bit numbers.
 */
int generatePageIndex(int num) {
    int binary = 0;
    for (int i = 3; i >= 0; i--) {
        binary = (binary << 1) | ((num >> i) & 1);
    }
    return binary;
}

/**
 * The function `generateOffset` converts a decimal number to a 12-bit binary number.
 * 
 * @param num Thank you for providing the code snippet. Could you please clarify what specific
 * information or value you would like to know about the `num` parameter that is being passed to the
 * `generateOffset` function?
 * 
 * @return The function `generateOffset` takes an integer `num` as input, converts it to a 12-bit
 * binary number by extracting each bit from `num`, and then returns the 12-bit binary number as an
 * integer.
 * 12-bit because we are representing offsets as 12 bit numbers.
 */
int generateOffset(int num) {
    int binary = 0;
    for (int i = 11; i >= 0; i--) {
        binary = (binary << 1) | ((num >> i) & 1);
    }
    return binary;
}

/**
 * The function binaryToDecimal converts a binary number to its decimal equivalent.
 *
 * @param binary The `binary` parameter in the `binaryToDecimal` function represents a binary number
 * that you want to convert to its decimal equivalent. This function converts a binary number (passed
 * as an integer) to a decimal number and returns the decimal value.
 *
 * @return The function `binaryToDecimal` returns the decimal equivalent of the input binary number.
 */
int binaryToDecimal(int binary) {
    int decimal = 0;
    int power = 1; // Initialize the power of 2

    while (binary > 0) {
        decimal += (binary % 10) * power;
        binary /= 10;
        power *= 2;
    }

    return decimal;
}

void printBinary(int num) {
    // Start from the most significant bit and print each bit
    for (int i = 3; i >= 0; i--) {
        // Use bitwise AND to check if the i-th bit is set
        if (num & (1 << i))
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}