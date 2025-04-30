#include <stdint.h>
#include "bus.h"

typedef struct cpu_s {
    uint32_t regs[32];
    uint32_t PC;
    bus_t bus;
} cpu_t;

enum opcode {
    R_TYPE_OP     = 0b0110011,
    I_TYPE_OP     = 0b0010011,
    S_TYPE_OP     = 0b0100011,
    L_TYPE_OP     = 0b0000011,
    LUI_TYPE_OP   = 0b0110111,
    AUIPC_TYPE_OP = 0b0010111,
    JAL_TYPE_OP   = 0b1101111,
    JALR_TYPE_OP  = 0b1100011,
};

enum i_type_op {
    ADDI         = 0,
    SLTI         = 2,
    SLTIU        = 3,
    XORI         = 4,
    ORI          = 6,
    ANDI         = 7,
    SLLI         = 1,
    SRLI_OR_SRAI = 5,
};

enum r_type_op {
    ADD_OR_SUB    = 0,
    SLL           = 1,
    SLT           = 2,
    SLTU          = 3,
    XOR           = 4,
    SRL_OR_SRA    = 5,
    OR            = 6,
    AND           = 7,
};


uint32_t fetch(cpu_t* cpu);
void execute(cpu_t* cpu, uint32_t inst);
void cpu_init(cpu_t* cpu);

