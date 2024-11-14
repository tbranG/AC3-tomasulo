#include"headers/shared.h"
#include"headers/arc.h"
#include"headers/parser.h"

extern Register registers[8];

//define um tamanho máximo para as instruções de 30 caracteres. Necessário para usar o fgets
#define MAX_INST_LENGTH 30

char** readInstructionFile(FILE* inputFile)
{
    assert(!(inputFile == NULL || feof(inputFile)), "Nao foi possivel ler o arquivo de instrucoes.")

    u8 numInst = 0;
    char** instList = malloc(sizeof(char*));

    do {
        char* inst = malloc(MAX_INST_LENGTH * sizeof(char));
        char* buffer = fgets(inst, MAX_INST_LENGTH, inputFile);

        assert(buffer != NULL, "Um erro ocorreu na leitura de uma instrucao. Abortando.");
        
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
        char* r1 = secToken;
        secToken = strtok(0, ",");

        char* r2 = secToken;
        secToken = strtok(0, ",");

        char* r3 = secToken;
        trim(r3);
        

        Instruction inst = {
            op,
            getRegisterByLabel(r1, registers),
            getRegisterByLabel(r2, registers),
            getRegisterByLabel(r3, registers),
            0
        };

        assert(inst.r1 != NULL, "Nao foi possivel encontrar o registrador de destino.");
        assert(inst.r2 != NULL && inst.r3 != NULL, "Nao foi encontrar um dos registradores");
        
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