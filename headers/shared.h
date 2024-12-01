#ifndef SHARED_H
#define SHARED_H

#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;

#define assert(c, msg)                                                         \
  if (!(c)) {                                                                  \
    printf("ERROR: %s", msg);                                                  \
    exit(EXIT_FAILURE);                                                        \
  }

typedef struct {
  char *label;
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
  DISPATCH = 1,
  EXECUTE = 2,
  WRITE_BACK = 3,
  COMMIT = 4,
} InstructionState;

typedef struct {
  InstructionType iType;
  Register *r1; // registrador de destino
  Register *r2;
  Register *r3;
  u8 a; // valor imediato para instruções load e store
} Instruction;

char *opCodeToString(InstructionType op);
char *instructionStateToString(InstructionState state);
void trim(char *s);
#endif