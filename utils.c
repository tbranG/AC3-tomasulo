#include "headers/utils.h"

extern Register registers[8];

static char *stationNames[7] = {"load1", "load2", "add1", "add2",
                                "add3",  "mul1",  "mul2"};
static char *registerLabels[8] = {"r1", "r2", "r3", "r4",
                                  "r5", "r6", "r7", "r8"};

char *instructionToString(Instruction *inst) {
  char *str = malloc(sizeof(char) * 30);
  strcat(str, opCodeToString(inst->iType));
  strcat(str, " ");
  strcat(str, inst->r1->label);
  strcat(str, " ");
  strcat(str, inst->r2->label);
  strcat(str, " ");
  strcat(str, inst->r3->label);
  strcat(str, "\0");

  return str;
}

#pragma region Print
void printStations(ReservationStation *stations, int amount) {
  printf("Nome\tBusy\tOp\tVj\tVk\tQj\t\tQk\t\trd\ta\n");
  for (int i = 0; i < amount; i++) {
    char *qjName = (stations[i].qj == NULL) ? "\t" : stations[i].qj->name;
    char *qkName = (stations[i].qk == NULL) ? "\t" : stations[i].qk->name;
    char *rdLabel = (stations[i].rd == NULL) ? "" : stations[i].rd->label;

    printf("%s\t%d\t\t%s\t%d\t%d\t%s\t%s\t%s\t%d\n", stations[i].name,
           (int)stations[i].busy, opCodeToString(stations[i].op),
           stations[i].vj, stations[i].vk, qjName, qkName, rdLabel,
           stations[i].a);
  }
}

void printReorderBuffer(ReorderBuffer *buffer, int amount) {
  printf("ID\tBusy\tInstrucao\t\tState\t\tDest\tValue\n");
  for (int i = 0; i < amount; i++) {
    char *inst = (buffer[i].inst == NULL) ? "-\t\t\t"
                                          : instructionToString(buffer[i].inst);
    char *destLabel = (buffer[i].dest == NULL) ? "-" : buffer[i].dest->label;

    printf("%d\t%d\t\t%s\t%s\t%s\t\t%d\n", buffer[i].entry, (int)buffer[i].busy,
           inst, instructionStateToString(buffer[i].state), destLabel,
           buffer[i].value);
  }
}
#pragma endregion Print

#pragma region Setup
void setupStations(ReservationStation *stations) {
  for (int i = 0; i < 7; i++) {
    stations[i].name = stationNames[i];
    stations[i].busy = false;
    stations[i].op = 0;
    stations[i].vj = 0;
    stations[i].vk = 0;
    stations[i].qj = NULL;
    stations[i].qk = NULL;
    stations[i].rd = NULL;
    stations[i].a = 0;
  }
}

void setupRegisters(Register *registers) {
  for (int i = 0; i < 8; i++) {
    registers[i].label = registerLabels[i];
    registers[i].value = i + 1; // inicializa cada registrador com um valor
                                // único
  }
}

void setupBuffers(ReorderBuffer *buffers) {
  for (int i = 0; i < 8; i++) {
    buffers[i].entry = i + 1;
    buffers[i].state = 0;
  }
}

void setupRegisterBank(RegisterBank *banks) {
  for (int i = 0; i < 8; i++) {
    banks[i].reg = &registers[i];
    banks[i].reord = 0;
    banks[i].busy = false;
  }
}
#pragma endregion Setup

void findDependencies(Instruction *iList, ReservationStation *sList,
                      Instruction *inst, ReservationStation *station,
                      int instCeil) {
  for (int i = 0; i < 7; i++) {
    if (sList[i].rd == inst->r2) {
      station->qj = &sList[i];
    }
    if (sList[i].rd == inst->r3) {
      station->qk = &sList[i];
    }
  }
}

bool executionFinished(ReorderBuffer *buffers, int instAmount) {
  bool response = true;

  for (int i = 0; i < instAmount; i++) {
    if (buffers[i].state != COMMIT) {
      response = false;
      break;
    }
  }

  return response;
}

u8 doOperation(InstructionType op, u8 vj, u8 vk) {
  switch (op) {
  case ADD:
    return vj + vk;
  case SUB:
    return vj - vk;
  case MUL:
    return vj * vk;
  case DIV:
    return vj / vk;
  default:
    return 0;
  }
}