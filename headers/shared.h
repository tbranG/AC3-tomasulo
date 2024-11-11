#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

typedef uint8_t u8;

typedef struct {
    char* label;
    u8 value;
} Register;

typedef enum {
    ADD = 1,
    SUB = 2,
    LW = 3,
    SW = 4,
    DIV = 5,
    MUL = 6,
} InstructionType;

typedef enum {
    DISPATCH,
    EXECUTE,
    WRITE_BACK,
    COMMIT,
} InstructionState;

typedef struct {
    InstructionType iType;
    char* r1; //registrador de destino
    char* r2;
    char* r3;
    u8 a; //valor imediato para instruções load e store
} Instruction;

#endif