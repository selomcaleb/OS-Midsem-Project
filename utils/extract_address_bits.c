/**
 * The function `extractAddressBits` takes a virtual address as input, extracts the outer index, inner
 * index, and offset from the address, and returns them as an array of integers.
 * 
 * @param virtual_address `virtual_address` is an unsigned short integer that represents a virtual
 * memory address. The function `extractAddressBits` takes this virtual address as input and extracts
 * specific parts of it to return as an array of integers. Virtual Addresses in this simulation are 16 bit addresses.
 * 
 * @return The function `extractAddressBits` is returning a pointer to an array of integers that
 * contains the extracted values of the outer index, inner index, and offset from the given virtual
 * address.
 */
int* extractAddressBits(unsigned short virtual_address) {
    // Create an array to store the extracted values
    static int result[3];

    // Extracting the outer index (first 4 bits)
    unsigned short outer_index = (virtual_address & 0xF000) >> 12;

    // Extracting the inner index (next 4 bits)
    unsigned short inner_index = (virtual_address & 0x0F00) >> 8;

    // Extracting the offset (last 8 bits)
    unsigned short offset = virtual_address & 0x00FF;

    result[0] = outer_index;
    result[1] = inner_index;
    result[2] = offset;

    return result;
}
