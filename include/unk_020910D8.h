#ifndef POKEHEARTGOLD_UNK_020910D8_H
#define POKEHEARTGOLD_UNK_020910D8_H

#include "options.h"
#include "player_data.h"
#include "pokemon.h"
#include "task.h"

typedef struct UnkStruct_02091240 {
    Pokemon *mon;
    Options *options;
    PlayerProfile *profile;
    u16 unkC;
} UnkStruct_02091240;

void CallTask_HatchEggInParty(TaskManager *taskman, UnkStruct_02091240 *a1);

#endif // POKEHEARTGOLD_UNK_020910D8_H
