#include <stdint.h>
#include "dram.h"


typedef struct bus_s {
    dram_t dram;
} bus_t;


uint32_t bus_load(bus_t* bus, uint32_t addr, uint32_t size);
void bus_store(bus_t* bus, uint32_t addr, uint32_t size, uint32_t value);