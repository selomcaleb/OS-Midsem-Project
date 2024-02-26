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
