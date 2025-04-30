#include <stdint.h>

#define DRAM_SIZE  1024*1024
#define DRAM_BASE  0x00000000


typedef struct dram_s {
    uint8_t mem[DRAM_SIZE];
} dram_t;

//Functions
void dram_store(dram_t* dram, uint32_t addr, uint32_t size, uint32_t value);
uint32_t dram_load(dram_t* dram, uint32_t addr, uint32_t size);

