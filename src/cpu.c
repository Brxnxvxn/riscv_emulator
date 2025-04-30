#include "../inc/cpu.h"

void cpu_add(uint32_t inst, cpu_t* cpu)
{


}


void cpu_addi(uint32_t inst, cpu_t* cpu)
{
    uint8_t rd_index = (inst & 0xF80) >> 7;
    uint8_t rs1_index = (inst & 0xF8000) >> 15;
    uint32_t imm = (inst & 0xFFF00000) >> 20;
    
    cpu->bus.dram.mem[rd_index] = cpu->bus.dram.mem[rs1_index] + (int32_t) imm;

}


void decode_i_type(uint32_t inst, cpu_t* cpu)
{
    //parse func3
    uint8_t func3 = (inst & 0x7000) >> 12;

    
    switch(func3) {

        case ADDI:
            cpu_addi(inst, cpu);

            break;
    }

}

void decode_r_type(uint32_t inst, cpu_t* cpu)
{

    //parse func3
    uint8_t func3 = (inst & 0x7000) >> 12;

    switch(func3) {
        case ADD_OR_SUB:
            //parse func7 [31:25]
            uint16_t func7 = (inst & 0xFE000000) >> 25;

            if (func7 == 0)
                cpu_add(inst, cpu);
            else
                cpu_sub();
            break;
        
        case SLL:
            cpu_sll();

    }


    if (func3 == 0)
        cpu_add(inst);
}


void decode_inst(uint32_t inst, cpu_t* cpu) 
{
    //find opcode  [6:0]
    uint8_t opcode = inst & 0x7F;

    switch(opcode) {
        case R_TYPE_OP:
            decode_r_type(inst, cpu);
            break;
        case I_TYPE_OP:
            decode_i_type(inst, cpu);
            break;

    }

}


