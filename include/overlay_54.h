#ifndef POKEHEARTGOLD_OVY_54_H
#define POKEHEARTGOLD_OVY_54_H

#include "options.h"
#include "overlay_manager.h"

typedef struct OptionsMenuArgs {
    u8 unk0[0x4];
    Options *options;
    BOOL *menuInputStatePtr;
} OptionsMenuArgs;

BOOL OptionsMenu_Init(OVY_MANAGER *man, int *state);
BOOL OptionsMenu_Main(OVY_MANAGER *man, int *state);
BOOL OptionsMenu_Exit(OVY_MANAGER *man, int *state);

#endif //POKEHEARTGOLD_OVY_54_H
