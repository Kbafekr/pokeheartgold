#ifndef POKEHEARTGOLD_VOLTORB_FLIP_H
#define POKEHEARTGOLD_VOLTORB_FLIP_H

#include "options.h"
#include "overlay_manager.h"
#include "player_data.h"
#include "save.h"

typedef struct VoltorbFlipArgs {
    Options *options;
    u16 *coins;
    BOOL *menuInputStatePtr;
    PlayerProfile *profile;
    SaveData *saveData;
} VoltorbFlipArgs;

BOOL VoltorbFlip_Init(OVY_MANAGER *man, int *state);
BOOL VoltorbFlip_Exit(OVY_MANAGER *man, int *state);
BOOL VoltorbFlip_Main(OVY_MANAGER *man, int *state);

#endif //POKEHEARTGOLD_VOLTORB_FLIP_H
