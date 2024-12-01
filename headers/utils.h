#include "shared.h"
#include "arc.h"
#include "parser.h"

void printStations(ReservationStation *stations, int amount);
void printReorderBuffer(ReorderBuffer *buffer, int amount);

void setupStations(ReservationStation *stations);
void setupRegisters(Register *registers);
void setupBuffers(ReorderBuffer *buffers);
void setupRegisterBank(RegisterBank *banks);

void findDependencies(Instruction *iList, ReservationStation *sList, Instruction *inst, ReservationStation *station, int instCeil);
bool executionFinished(ReorderBuffer *buffers, int instAmount);
u8 doOperation(InstructionType op, u8 vj, u8 vk);