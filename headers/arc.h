#include "shared.h"

// Pré-declaração. Necessário pois a struct ReservationStation possui ponteiros
// para outras estações
typedef struct ReservationStation ReservationStation;

struct ReservationStation {
  char *name;
  bool busy;
  InstructionType op;     // tipo da operação
  Register *rd;           // registrador de destino
  u8 vj;                  // operando 1
  u8 vk;                  // operando 2
  ReservationStation *qj; // estação que produzirá o resultado 1
  ReservationStation *qk; // estação que produzirá o resultado 2
  u8 a;                   // Valor imediato para operações de load e store
};

typedef struct {
  Register *reg; // registrador
  u8 reord;      // qual instrução no buffer está utilizando o registrador
  bool busy;
} RegisterBank;

typedef struct {
  u8 entry; // identificação
  bool busy;
  Instruction inst;
  InstructionState state;
  u8 dest;  // registrador de destino
  u8 value; // valor final
} ReorderBuffer;

Register *getRegisterByLabel(char *label, Register *rList);

/// @brief Define uma estação de reserva
/// @param station referência da estação para escrita
/// @param inst instrução que será executada
/// @param qj Dependência de resultado 1
/// @param qk Dependência de resultado 2
void setStation(ReservationStation *station, Instruction inst,
                ReservationStation *qj, ReservationStation *qk, u8 vj, u8 vk,
                u8 a);

/// @brief Carrega uma instruçãn no buffer de reordenação
/// @param buffer referência do buffer
/// @param inst instrução para carregar
void setReordBuffer(ReorderBuffer *buffer, Instruction inst);

/// @brief TODO: adicionar descrição
/// @param bank referência da estrutura
/// @param entry qual entrada do buffer de reordenação está utilizando o
/// registrador
void setRegbank(RegisterBank *bank, u8 entry);