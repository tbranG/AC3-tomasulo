#include"shared.h"

char** readInstructionFile(FILE* inputFile);
Instruction parseInstruction(char* instructionStr);
InstructionType getInstructionType(char* type);