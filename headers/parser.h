#include"shared.h"

char** readInstructionFile(FILE* inputFile);
Instruction parseInstruction(char* instructionStr);

/// @brief Obtém a operação (op code) por meio de uma string (ex: "add", "sub", "div")
/// @param type string para realizar o parsing da instrução. OBS: Deve ser minuscula.
InstructionType getInstructionType(char* type);