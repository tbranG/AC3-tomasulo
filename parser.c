#include"utils.h"
#include"parser.h"

//define um tamanho máximo para as instruções de 30 caracteres. Necessário para usar o fgets
#define MAX_INST_LENGTH 30

char** readInstructionFile(FILE* inputFile)
{
    if (inputFile == NULL || feof(inputFile)) {
        printf("ERROR: Couldn't parse instruction file.");
        exit(0);
    }

    u8 numInst = 0;
    char** instList = malloc(sizeof(char*));

    do {
        char* inst = malloc(MAX_INST_LENGTH * sizeof(char));
        fgets(inst, MAX_INST_LENGTH, inputFile);

        instList[numInst] = inst;
        instList = realloc(instList, (++numInst + 1) * sizeof(char*));

    } while (!feof(inputFile));

    //Flag de final de arquivo
    instList[numInst] = "EOF";

    return instList;
}

Instruction parseInstruction(char* instructionStr){

    //utiliza o strtok para realizar um splice da string de entrada
    //e pegar os componentes OPERACAO R1, R2, R3

    char* token = strtok(instructionStr, " ");
    InstructionType op = getInstructionType(token);

    token = strtok(0, " ");
    char* secToken = strtok(token, ",");

    if(op == SW || op == LW){
        //TODO: terminar
    } else {
        u8 r1 = secToken[1] - 48;
        secToken = strtok(0, ",");

        u8 r2 = secToken[1] - 48;
        secToken = strtok(0, ",");

        u8 r3 = secToken[1] - 48;
        secToken = NULL;

        Instruction inst = {
            op,
            r1,
            r2,
            r3
        };

        return inst;
    }
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