#include "../inc/bus.h"


uint32_t bus_load(bus_t* bus, uint32_t addr, uint32_t size)
{

    return dram_load(&(bus->dram), addr, size);
}


void bus_store(bus_t* bus, uint32_t addr, uint32_t size, uint32_t value) 
{
    dram_store(&(bus->dram), addr, size, value);
}