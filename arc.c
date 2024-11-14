#include "headers/arc.h"
#include "headers/shared.h"

Register registers[8];
ReorderBuffer rBuffer[8];
RegisterBank rBank[8];
ReservationStation rStation[7];

Register *getRegisterByLabel(char *label, Register *rList) {
  if (strcmp(label, "r1") == 0)
    return &rList[0];
  else if (strcmp(label, "r2") == 0)
    return &rList[1];
  else if (strcmp(label, "r3") == 0)
    return &rList[2];
  else if (strcmp(label, "r4") == 0)
    return &rList[3];
  else if (strcmp(label, "r5") == 0)
    return &rList[4];
  else if (strcmp(label, "r6") == 0)
    return &rList[5];
  else if (strcmp(label, "r7") == 0)
    return &rList[6];
  else if (strcmp(label, "r8") == 0)
    return &rList[7];
  else
    return NULL;
}

void setStation(ReservationStation *station, Instruction inst,
                ReservationStation *qj, ReservationStation *qk, u8 vj, u8 vk,
                u8 a) {
  assert(station != NULL,
         "Nao foi possivel definir a estacao, seu valor eh igual a NULL");

  station->busy = true;
  station->op = inst.iType;
  station->rd = inst.r1;

  if (inst.iType == LW || inst.iType == SW) {
    station->a = a;
  } else {
    if (qj != NULL) {
      station->qj = qj;
    } else {
      station->vj = vj;
    }

    if (qk != NULL) {
      station->qk = qk;
    } else {
      station->vk = vk;
    }
  }
}

void setReordBuffer(ReorderBuffer *buffer, Instruction inst) {
  assert(buffer != NULL,
         "Nao foi possivel definir o buffer, seu valor eh igual a NULL");
}
