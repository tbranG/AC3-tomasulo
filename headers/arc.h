#include"shared.h"

typedef struct {
    char* name;
    bool busy;
    InstructionType op;
    u8 rd;
    u8 vj;
    u8 vk;
    u8 qj;
    u8 qk;
    u8 a;   //Valor imediato para operações de load e store
} ReservationStation;

typedef struct {
    u8 reg;
    u8 reord;
    bool busy;
} RegisterBank;

typedef struct {
    u8 entry;
    bool busy;
    Instruction inst;
    InstructionState state;
    u8 dest;
    u8 value;
} ReorderBuffer;