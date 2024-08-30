#ifndef POKEHEARTGOLD_OVY_18_H
#define POKEHEARTGOLD_OVY_18_H

#include "overlay_manager.h"
#include "player_data.h"
#include "pokedex.h"

typedef struct PokedexArgs {
    Pokedex *pokedex;
    PlayerProfile *playerProfile;
    u32 *unk_08;
    BOOL *unk_0C;
    int x;
    int y;
    u16 mapId;
    u16 mapMatrixId;
} PokedexArgs;

BOOL Pokedex_Init(OVY_MANAGER *man, int *state);
BOOL Pokedex_Main(OVY_MANAGER *man, int *state);
BOOL Pokedex_Exit(OVY_MANAGER *man, int *state);

#endif // POKEHEARTGOLD_OVY_18_H
