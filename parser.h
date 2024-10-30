#include"utils.h"

typedef enum {
    ADD = 1,
    SUB = 2,
    LW = 3,
    SW = 4,
    DIV = 5,
    MUL = 6,
} InstructionType;

typedef struct {
    InstructionType iType;
    u8 r1;
    u8 r2;
    u8 r3;
} Instruction;

Instruction parseInstruction(char* instructionStr);
InstructionType getInstructionType(char* type);