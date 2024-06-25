#ifndef POKEHEARTGOLD_OVY_73_H
#define POKEHEARTGOLD_OVY_73_H

#include "game_stats.h"
#include "options.h"
#include "overlay_manager.h"
#include "save.h"
#include "script.h"

typedef struct UnkStruct_0203F4F8 {
    SaveData *saveData;
    struct UnkStruct_0205AC88 *unk4;
    Options *options;
    GAME_STATS *gameStats;
    u32 *unk10;
} UnkStruct_0203F4F8;

BOOL ov73_021E5900(OVY_MANAGER *man, int *state);
BOOL ov73_021E5AB8(OVY_MANAGER *man, int *state);
BOOL ov73_021E5BAC(OVY_MANAGER *man, int *state);

BOOL ov73_021E7E4C(OVY_MANAGER *man, int *state);
BOOL ov73_021E7FB8(OVY_MANAGER *man, int *state);
BOOL ov73_021E808C(OVY_MANAGER *man, int *state);

#endif //POKEHEARTGOLD_OVY_73_H
