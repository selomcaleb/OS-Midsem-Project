//
// Created by Oheneba Dade on 01/03/2024.
//

#ifndef OS_MIDSEM_PROJECT_GENERATE_RANDOM_ADDRESS_H
#define OS_MIDSEM_PROJECT_GENERATE_RANDOM_ADDRESS_H

int generatePageIndex(int num);
int generateOffset(int num);
int binaryToDecimal(int binary);
void printBinary(int num);
void printGeneratedAddress(int masterPageIndex, int innerPageIndex, int offSet);

#endif //OS_MIDSEM_PROJECT_GENERATE_RANDOM_ADDRESS_H
