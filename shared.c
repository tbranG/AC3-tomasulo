#include "headers/shared.h"

char *opCodeToString(InstructionType op) {
  switch (op) {
  case ADD:
    return "add";
  case SUB:
    return "sub";
  case LW:
    return "lw";
  case SW:
    return "sw";
  case DIV:
    return "div";
  case MUL:
    return "mul";
  default:
    return "";
  }
}

char *instructionStateToString(InstructionState state) {
  switch (state) {
  case DISPATCH:
    return "dispatch";
  case COMMIT:
    return "commit  ";
  case EXECUTE:
    return "execute  ";
  case WRITE_BACK:
    return "write back";
  default:
    return "        ";
  }
}

void trim(char *s) {
  int i;

  while (isspace(*s))
    s++;
  for (i = strlen(s) - 1; (isspace(s[i])); i--)
    ;
  s[i + 1] = '\0';
}