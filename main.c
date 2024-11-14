#include "headers/arc.h"
#include "headers/parser.h"
#include "headers/shared.h"

#define MAX_FILEPATH_LENGTH 30

extern Register registers[8];
extern ReorderBuffer rBuffer[8];
extern RegisterBank rBank[8];
extern ReservationStation rStation[7];

static char *stationNames[7] = {"load1", "load2", "add1", "add2",
                                "add3",  "mul1",  "mul2"};
static char *registerLabels[8] = {"r1", "r2", "r3", "r4",
                                  "r5", "r6", "r7", "r8"};

void printStations(ReservationStation *stations, int amount) {
  printf("Nome\tBusy\tOp\tVj\tVk\tQj\tQk\trd\ta\n");
  for (int i = 0; i < amount; i++) {
    char *qjName = (stations[i].qj == NULL) ? "-" : stations[i].qj->name;
    char *qkName = (stations[i].qk == NULL) ? "-" : stations[i].qk->name;
    char *rdLabel = (stations[i].rd == NULL) ? "-" : stations[i].rd->label;

    printf("%s\t%d\t\t%s\t%d\t%d\t%s\t%s\t%s\t%d\n", stations[i].name,
           (int)stations[i].busy, opCodeToString(stations[i].op),
           stations[i].vj, stations[i].vk, qjName, qkName, rdLabel,
           stations[i].a);
  }
}

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
  }
}

int main() {
  setupStations(rStation);
  setupRegisters(registers);
  char filepath[MAX_FILEPATH_LENGTH];

  printf("Digite o caminho para o arquivo de instruções:\n");
  fgets(filepath, MAX_FILEPATH_LENGTH, stdin);
  trim(filepath);
  
  FILE *file = fopen(filepath, "r");
  char **instructionsStr = readInstructionFile(file);

  char *inst = *instructionsStr;
  printf("String: %s", inst);

  Instruction instParsed = parseInstruction(inst);

  printf("Inst: %d %s %s %s %d\n", instParsed.iType, instParsed.r1->label,
         instParsed.r2->label, instParsed.r3->label, instParsed.a);

  setStation(&rStation[2], instParsed, NULL, NULL, 0, 0, 0);
  printStations(rStation, 7);

  return 0;
}