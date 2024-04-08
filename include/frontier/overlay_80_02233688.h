#ifndef POKEHEARTGOLD_OVERLAY_80_02233688
#define POKEHEARTGOLD_OVERLAY_80_02233688

#include "frontier/overlay_80_0222BDF4.h"
#include "frontier/overlay_80_022340E8.h"
#include "battle_arcade_game_board.h"

BOOL FrtCmd_ArcadeAlloc(FrontierContext *ctx);
BOOL FrtCmd_ArcadeInit(FrontierContext  *ctx);
BOOL FrtCmd_ArcadeFree(FrontierContext *ctx);
BOOL ov80_0223371C(FrontierContext *ctx);
BOOL ov80_02233770(FrontierContext *ctx);
BOOL FrtCmd_ArcadeStartBattle(FrontierContext *ctx);
BOOL FrtCmd_ArcadeSetPartyBeforeBattle(FrontierContext *ctx);
BOOL FrtCmd_ArcadeSetPartyAfterBattle(FrontierContext *ctx);
BOOL FrtCmd_ArcadeAction(FrontierContext *ctx);
BOOL FrtCmd_ArcadeGetBattleResult(FrontierContext *ctx);
BOOL FrtCmd_ArcadeSendBuffer(FrontierContext *ctx);
BOOL FrtCmd_ArcadeReceiveBuffer(FrontierContext *ctx);
BOOL FrtCmd_ArcadePrintMsg(FrontierContext *ctx);
BOOL FrtCmd_ArcadeSetEvent(FrontierContext *ctx);
BOOL ov80_022340A8(FrontierContext *ctx);

#endif
