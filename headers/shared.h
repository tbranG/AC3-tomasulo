#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

typedef uint8_t u8;

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
    u8 r1;
    u8 r2;
    u8 r3;
} Instruction;

#endif