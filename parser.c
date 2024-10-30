#include<string.h>
#include"parser.h"

Instruction parseInstruction(char* instructionStr){
    // 
}

InstructionType getInstructionType(char* type){
    if (strcmp(type, "add") == 0)
        return ADD;
    else if (strcmp(type, "sub") == 0)
        return SUB;
    else if (strcmp(type, "lw") == 0)
        return LW;
    else if (strcmp(type, "sw") == 0)
        return SW;
    else if (strcmp(type, "div") == 0)
        return DIV;
    else if (strcmp(type, "mul") == 0)
        return MUL;
    else
        return -1; 
}