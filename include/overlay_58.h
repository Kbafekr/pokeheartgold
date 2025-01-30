#ifndef POKEHEARTGOLD_OVY_58_H
#define POKEHEARTGOLD_OVY_58_H

#include "overlay_manager.h"
#include "save.h"

typedef struct ApricornBoxArgs {
    u8 unk0;
    u8 unk1[0x7];
    u16 *unk8;
    u32 unkC;
    u32 unk10;
    BOOL *menuInputStatePtr;
    SaveData *saveData;
} ApricornBoxArgs;

BOOL ApricornBox_Init(OVY_MANAGER *man, int *state);
BOOL ApricornBox_Main(OVY_MANAGER *man, int *state);
BOOL ApricornBox_Exit(OVY_MANAGER *man, int *state);

#endif // POKEHEARTGOLD_OVY_58_H
