#ifndef POKEHEARTGOLD_FIELD_MOVE_H
#define POKEHEARTGOLD_FIELD_MOVE_H

#include "script.h"
#include "party_menu.h"

void *PartyMenu_GetFieldMoveFunc(u16 funcType, u16 fieldMoveIdx);
void FieldSystem_MakeFieldMoveCheckData(FieldSystem *fieldSystem, struct FieldMoveCheckData *checkData);

#endif //POKEHEARTGOLD_FIELD_MOVE_H
