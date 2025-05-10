#include "../inc/cpu.h"

uint8_t rd(uint32_t inst)
{
    return (inst & 0xF80) >> 7;
}

uint8_t rs1(uint32_t inst)
{
    return (inst & 0xF8000) >> 15;
}

uint8_t rs2(uint32_t inst)
{
    return (inst & 0x1F00000) >> 20;
}


// *************** ISA FUNCTIONS *****************

// ************ R_TYPE_FUNCTIONS ***************
void cpu_add(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] + cpu->regs[rs2(inst)];
}

void cpu_sub(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] - cpu->regs[rs2(inst)];
}

void cpu_sll(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] << cpu->regs[rs2(inst)];
}

void cpu_slt(uint32_t inst, cpu_t* cpu)
{
    if (cpu->regs[rs1(inst)] < (int32_t)cpu->regs[rs2(inst)])
        cpu->regs[rd(inst)] = 1;
    else
        cpu->regs[rd(inst)] = 0;
}

void cpu_sltu(uint32_t inst, cpu_t* cpu)
{
    if (cpu->regs[rs1(inst)] < cpu->regs[rs2(inst)])
        cpu->regs[rd(inst)] = 1;
    else
        cpu->regs[rd(inst)] = 0;
}

void cpu_xor(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] ^ cpu->regs[rs2(inst)];
}

void cpu_srl(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] >> cpu->regs[rs2(inst)];
}

void cpu_sra(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = (int32_t)cpu->regs[rs1(inst)] >> cpu->regs[rs2(inst)];
}

void cpu_and(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] & cpu->regs[rs2(inst)];
}

void cpu_or(uint32_t inst, cpu_t* cpu)
{
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] | cpu->regs[rs2(inst)];
}

/* ************ I_TYPE_FUNCTIONS *************** */
void cpu_addi(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFF00000) >> 20;
    
    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] + (int32_t) imm;
}

void cpu_slti(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    if (cpu->regs[rs1(inst)] < (int32_t) imm)
        cpu->regs[rd(inst)] = 1;
    else 
        cpu->regs[rd(inst)] = 0;
}

void cpu_sltiu(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    if (cpu->regs[rs1(inst)] < imm)
        cpu->regs[rd(inst)] = 1;
    else 
        cpu->regs[rd(inst)] = 0;
}

void cpu_xori(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] ^ (int32_t)imm;
}

void cpu_ori(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] | (int32_t)imm;
}

void cpu_andi(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] & (int32_t)imm;
}

void cpu_slli(uint32_t inst, cpu_t* cpu)
{
    uint8_t shamt = (inst & 0x1F00000) >> 20;

    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] << shamt;

}

void cpu_srli(uint32_t inst, cpu_t* cpu)
{
    uint8_t shamt = (inst & 0x1F00000) >> 20;

    cpu->regs[rd(inst)] = cpu->regs[rs1(inst)] >> shamt;

}

void cpu_srai(uint32_t inst, cpu_t* cpu)
{
    uint8_t shamt = (inst & 0x1F00000) >> 20;

    cpu->regs[rd(inst)] = (int32_t)cpu->regs[rs1(inst)] >> shamt;

}

/* ******** BRANCH FUNCTIONS ********** */
void cpu_lui(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFFFF000) >> 12;

    cpu->regs[rd(inst)] = imm << 12;
}

void cpu_auipc(uint32_t inst, cpu_t* cpu)
{
    uint32_t imm = (inst & 0xFFFFF000) >> 12;

    cpu->regs[rd(inst)] = cpu->PC + imm << 12;

}


/* ******** JUMP FUNCTIONS ********* */
void cpu_jal(uint32_t inst, cpu_t* cpu)
{

    //parse JAL imm[20|10:1|11|19:12] <==> inst[31|30:21|20|19:12] the LSB is implied
    uint32_t imm = ( (inst & 0x80000000) >> 11 ) | ( (inst & 0x7FE00000) >>  20) | ( (inst & 0x00100000) >> 9) | ( (inst & 0x000FF000));

    //save next inst in pc in rd reg
    cpu->regs[rd(inst)] = cpu->PC;

    //set PC to current + offset (imm)
    cpu->PC = cpu->PC +  (int32_t)imm - 4;

    //may need to add check for address misalignment

}

void cpu_jalr(uint32_t inst, cpu_t* cpu)
{

    //parse JALR IMM
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //save next inst in pc in rd reg
    cpu->regs[rd(inst)] = cpu->PC;

    //set PC to rs1 + offset (imm)
    cpu->PC = cpu->regs[rs1(inst)] + (int32_t)imm;

    //may need to add check for address misalignment

}

/* -------- Load Functions ---------   */
void cpu_lw(uint32_t inst, cpu_t* cpu) 
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //load word into register
    cpu->regs[rd(inst)] = bus_load(&(cpu->bus), cpu->regs[rs1(inst)] + (int32_t)imm,  4);
}

void cpu_lb(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //load byte into register
    cpu->regs[rd(inst)] = bus_load(&(cpu->bus), cpu->regs[rs1(inst)] + (int32_t)imm,  1);
}

void cpu_lbu(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //load byte unsigned into register
    cpu->regs[rd(inst)] = bus_load(&(cpu->bus), cpu->regs[rs1(inst)] + imm,  1);
}

void cpu_lh(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //load half-word into register
    cpu->regs[rd(inst)] = bus_load(&(cpu->bus), cpu->regs[rs1(inst)] + (int32_t)imm,  2);
}

void cpu_lhu(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //load half-word unsigned into register
    cpu->regs[rd(inst)] = bus_load(&(cpu->bus), cpu->regs[rs1(inst)] + imm,  2);
}

/* -------- Store Functions ---------   */
void cpu_sw(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //store word into memory
    bus_store(&(cpu->bus), cpu->regs[rs1(inst)] + imm, 4, cpu->regs[rs2(inst)]);
}

void cpu_sh(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //store half-word into memory
    bus_store(&(cpu->bus), cpu->regs[rs1(inst)] + imm, 2, cpu->regs[rs2(inst)]);
}

void cpu_sb(uint32_t inst, cpu_t* cpu)
{
    //parse imm
    uint32_t imm = (inst & 0xFFF00000) >> 20;

    //store byte into memory
    bus_store(&(cpu->bus), cpu->regs[rs1(inst)] + imm, 1, cpu->regs[rs2(inst)]);
}


void decode_s_type(uint32_t inst, cpu_t* cpu)
{
    //parse func3 [14:12]
    uint8_t func3 = (inst & 0x7000) >> 12;

    switch(func3) {
        
        case SW:
            cpu_sw(inst, cpu);
            break;
        case SB:
            cpu_sb(inst, cpu);
            break;
        case SH:
            cpu_sh(inst, cpu);
            break;
            
    }

}

void decode_l_type(uint32_t inst, cpu_t* cpu)
{
    //parse func3 [14:12]
    uint8_t func3 = (inst & 0x7000) >> 12;

    switch(func3) {

        case LB:
            cpu_lb(inst, cpu);
            break;
        case LW:
            cpu_lw(inst, cpu);
            break;
        case LH:
            cpu_lh(inst, cpu);
            break;
        case LBU:
            cpu_lbu(inst, cpu);
            break;
        case LHU:
            cpu_lhu(inst, cpu);
            break;
    }
}

void decode_i_type(uint32_t inst, cpu_t* cpu)
{
    //parse func3
    uint8_t func3 = (inst & 0x7000) >> 12;

    
    switch(func3) {

        case ADDI:
            cpu_addi(inst, cpu);
            break;
        case SLTI:
            cpu_slti(inst, cpu);
            break;
        case SLTIU:
            cpu_sltiu(inst, cpu);
            break;
        case XORI:
            cpu_xori(inst, cpu);
            break;
        case ORI:
            cpu_ori(inst, cpu);
            break;
        case ANDI:
            cpu_andi(inst, cpu);
            break;
        case SLLI:
            cpu_slli(inst, cpu);
            break;
        case SRLI_OR_SRAI:

            //parse func7 [31:25]
            uint16_t func7 = (inst & 0xFE000000) >> 25;

            if (func7 == 0)
                cpu_srli(inst, cpu);
            else 
                cpu_srai(inst, cpu);
            
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
                cpu_sub(inst, cpu);
            break;
        
        case SLL:
            cpu_sll(inst, cpu);
        
        case SLT:
            cpu_slt(inst, cpu);
        
        case SLTU:
            cpu_sltu(inst, cpu);
        
        case XOR:
            cpu_xor(inst, cpu);
        
        case SRL_OR_SRA:
            //parse func7 [31:25]
            uint16_t func7 = (inst & 0xFE000000) >> 25;

            if (func7 == 0)
                cpu_srl(inst, cpu);
            else
                cpu_sra(inst, cpu);
            break;
        
        case AND:
            cpu_and(inst, cpu);
            break;
        
        case OR:
            cpu_or(inst, cpu);
            break;

    }
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
        case LUI_TYPE_OP:
            cpu_lui(inst, cpu);
            break;
        case AUIPC_TYPE_OP:
            cpu_auipc(inst, cpu);
            break;
        case JAL_TYPE_OP:
            cpu_jal(inst, cpu);
            break;
        case JALR_TYPE_OP:
            cpu_jalr(inst, cpu);
            break;

    }

}


