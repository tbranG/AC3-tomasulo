#include "headers/shared.h"
#include "headers/utils.h"

#define MAX_FILEPATH_LENGTH 30

extern Register registers[8];
extern ReorderBuffer rBuffer[8];
extern RegisterBank rBank[8];
extern ReservationStation rStation[7];

static int instAmount = 0;

int main() {
  setupStations(rStation);
  setupRegisters(registers);
  setupBuffers(rBuffer);
  setupRegisterBank(rBank);

  char filepath[MAX_FILEPATH_LENGTH];

  printf("Digite o caminho para o arquivo de instruções:\n");
  fgets(filepath, MAX_FILEPATH_LENGTH, stdin);

  trim(filepath);
  FILE *file = fopen(filepath, "r");

  char **instructionsStr = readInstructionFile(file);
  Instruction *instructions = malloc(sizeof(Instruction));

  // Carregando as instruções ------------------------------------
  int i = 0;
  char *inst = instructionsStr[i];

  do {
    Instruction tmp = parseInstruction(inst);

    instructions[instAmount].iType = tmp.iType;
    instructions[instAmount].r1 = tmp.r1;
    instructions[instAmount].r2 = tmp.r2;
    instructions[instAmount].r3 = tmp.r3;

    instructions =
        realloc(instructions, (++instAmount + 1) * sizeof(Instruction));

    inst = instructionsStr[++i];

  } while (strcmp(inst, "EOF") != 0);
  //--------------------------------------------------------------

  // Carregando instruções no buffer de reordenação
  for (int i = 0; i < instAmount; i++) {
    setReordBuffer(&rBuffer[i], &instructions[i]);
  }

  // loop principal
  while (!executionFinished(rBuffer, instAmount)) {
    // Para cada instrução no buffer de reordenação
    for (int i = 0; i < instAmount; i++) {
      // Se a instrução não estiver no estado de commit
      if (rBuffer[i].state == 0) {
        InstructionType op = rBuffer[i].inst->iType;
        int p = 0;

        // verificando se existem estações disponíveis para a instrução
        if (op == LW || op == SW) {
          if (!rStation[0].busy) {
            p = 0;
          } else if (!rStation[1].busy) {
            p = 1;
          }
        } else if (op == ADD || op == SUB) {
          if (!rStation[2].busy) {
            p = 2;
          } else if (!rStation[3].busy) {
            p = 3;
          } else if (!rStation[4].busy) {
            p = 4;
          }
        } else {
          if (!rStation[5].busy) {
            p = 5;
          } else if (!rStation[6].busy) {
            p = 6;
          }
        }

        setStation(&rStation[p], instructions[i], NULL, NULL, 0, 0, 0);
        findDependencies(instructions, rStation, &instructions[i], &rStation[p],
                         0);
        rBuffer[i].station = &rStation[p];
        rBuffer[i].state = DISPATCH;
      }
      // caso a instrução já estiver sido commitada, tente executar
      else if (rBuffer[i].state == DISPATCH) {
        if (rBuffer[i].station->qj == NULL && rBuffer[i].station->qk == NULL) {
          rBuffer[i].station->vj = rBuffer[i].inst->r2->value;
          rBuffer[i].station->vk = rBuffer[i].inst->r3->value;
          rBuffer[i].state = EXECUTE;
        }
      } else if (rBuffer[i].state == EXECUTE) {
        u8 result =
            doOperation(rBuffer[i].inst->iType, rBuffer[i].inst->r2->value,
                        rBuffer[i].inst->r3->value);
        rBuffer[i].value = result;
        rBuffer[i].inst->r1->value = result;

        // verificar se alguma estação depende desse valor
        for (int j = 0; j < 7; j++) {
          if (rStation[j].qj == rBuffer[i].station) {
            rStation[j].vj = rBuffer[i].value;
            rStation[j].qj = NULL;
          }
          if (rStation[j].qk == rBuffer[i].station) {
            rStation[j].vk = rBuffer[i].value;
            rStation[j].qk = NULL;
          }
        }

        rBuffer[i].station->busy = false;
        rBuffer[i].station->op = 0;
        rBuffer[i].station->rd = NULL;
        rBuffer[i].station->vj = 0;
        rBuffer[i].station->vk = 0;
        rBuffer[i].station->qj = 0;
        rBuffer[i].station->qk = 0;
        rBuffer[i].station->a = 0;
        rBuffer[i].station = NULL;

        rBuffer[i].state = WRITE_BACK;
      } else if (rBuffer[i].state == WRITE_BACK) {
        rBuffer[i].inst->r1->value = rBuffer[i].value;
        rBuffer[i].state = COMMIT;
      }
    }

    printf("--Buffer de reordenacao--\n");
    printReorderBuffer(rBuffer, 8);
    printf("\n--Estacoes de reserva--\n");
    printStations(rStation, 7);
    printf("\n");

    printf("\nPressione qualquer tecla para continuar...");
    getc(stdin);

    printf("-------------------------------------------------------------\n");
  }

  return 0;
}