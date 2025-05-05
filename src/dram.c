#include "../inc/dram.h"

uint32_t dram_load(dram_t* dram, uint32_t addr, uint32_t size)
{

    //implemented in little endian
    uint32_t word;

    for(int i = 0; i < size; i++) {

        //store each byte in word
        word |= (dram->mem[addr + i] << (8 * i));

    }

    return word;
}

void dram_store(dram_t* dram, uint32_t addr, uint32_t size, uint32_t value)
{

    //implemented in little endian

    for(int i = 0; i < size; i++) {

        //parse each byte
        uint8_t byte = value & 0x000000FF;

        //store into memory
        dram->mem[addr + i] = byte;

    }
}