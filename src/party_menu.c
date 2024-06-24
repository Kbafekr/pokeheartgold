#include "constants/maps.h"
#include "global.h"
#include "bag.h"
#include "party_menu.h"
#include "gf_gfx_loader.h"
#include "field_system.h"
#include "msgdata/msg.naix"
#include "font.h"
#include "overlay_94.h"
#include "render_text.h"
#include "sound_02004A44.h"
#include "system.h"
#include "unk_02005D10.h"
#include "unk_0200FA24.h"
#include "unk_020183F0.h"
#include "unk_020210A0.h"
#include "unk_020290B4.h"
#include "unk_02066EDC.h"
#include "party_context_menu.h"
#include "party_menu_list_items.h"
#include "unk_0203A3B0.h"
#include "unk_02080BB4.h"
#include "unk_0208805C.h"
#include "party_menu_sprites.h"
#include "unk_02074944.h"
#include "unk_02088288.h"
#include "use_item_on_mon.h"
#include "vram_transfer_manager.h"
#include "constants/moves.h"
#include "msgdata/msg/msg_0300.h"

FS_EXTERN_OVERLAY(OVY_94);

typedef struct UnkStruct_0207A22C {
    u16 unk_0;
    u16 unk_2;
    u16 unk_4;
    u16 unk_6;
    u16 unk_8;
    u16 unk_A;
} UnkStruct_0207A22C;

static BOOL PartyMenuApp_Init(OVY_MANAGER *manager, int *pState);
static BOOL PartyMenuApp_Main(OVY_MANAGER *manager, int *pState);
static void sub_02079230(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_Init(PartyMenuStruct *partyMenu);
static int sub_02079308(PartyMenuStruct *partyMenu);
static int sub_020793C0(PartyMenuStruct *partyMenu);
static int sub_02079400(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_HandleInput(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_WaitTextPrinter(PartyMenuStruct *partyMenu);
static int sub_020794EC(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_YesNoMenuInit(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_YesNoMenuHandleInput(PartyMenuStruct *partyMenu);
static int sub_02079550(PartyMenuStruct *partyMenu);
static BOOL PartyMenuApp_Exit(OVY_MANAGER *manager, int *pState);
static void sub_020796B8(void *cbData);
static void sub_02079700(void);
static void sub_02079720(BgConfig *bgConfig);
static void sub_02079758(BgConfig *bgConfig);
static void sub_020798C4(BgConfig *bgConfig);
GF3DVramMan *sub_0207997C(HeapID heapId);
static void sub_0207999C(void);
static void sub_02079A0C(GF3DVramMan *gf3dVramMan);
static void sub_02079A14(PartyMenuStruct *partyMenu, NARC *narc);
static BOOL sub_0207A880(PartyMenuStruct *partyMenu, u8 partySlot);
PartyMenuStruct *sub_02079BD8(OVY_MANAGER *manager);
static void sub_02079CE4(PartyMenuStruct *partyMenu);
static void sub_02079D38(PartyMenuStruct *partyMenu);
static u8 PartyMenu_IsMonDrawStateActive(PartyMenuStruct *partyMenu, u8 partySlot);
static void PartyMenu_MonSuperContestEligibilityCheck(PartyMenuStruct *partyMenu, Pokemon *mon, u8 partySlot);
static u32 Pokemon_CountRibbonsByCategory(Pokemon *mon, u8 contestStat);
static void sub_0207A174(PartyMenuStruct *partyMenu, u8 partySlot, u8 x, u8 y, u8 a4);
static void PartyMenu_DrawPanelsAndPush(PartyMenuStruct *partyMenu);
static void PartyMenu_DrawPanels_Default(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1);
static void PartyMenu_DrawPanels_UseEvoStone(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1);
static void PartyMenu_DrawPanels_UseTMHM(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1);
static void PartyMenu_Setup_SuperContestEntry(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1);
static void PartyMenu_DrawPanels_FrontierFacilityEntry(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1);
static void sub_0207A780(PartyMenuStruct *partyMenu, u8 partySlot, s16 x, s16 y);
static void sub_0207A89C(PartyMenuStruct *partyMenu);
static u8 sub_0207A8FC(PartyMenuStruct *partyMenu);
static void PartyMenu_MoveCursorSpriteTo(PartyMenuStruct *partyMenu, int selection, int x, int y);
static void PartyMenu_MoveCursorSpriteTo_WithSfx(PartyMenuStruct *partyMenu, int selection, int x, int y);
static BOOL PartyMenu_HandleDpadInput(PartyMenuStruct *partyMenu);
static u8 PartyMenu_GetSelectionInDirection(PartyMenuStruct *partyMenu, u8 *px, u8 *py, u8 direction);
static u8 PartyMenu_GetNewSelectionFromTable(PartyMenuStruct *partyMenu, u8 *px, u8 *py, const u8 *table);
static void sub_0207AC20(PartyMenuStruct *partyMenu);
static int sub_0207AC70(PartyMenuStruct *partyMenu, BOOL a1);
static int PartyMenu_GetTouchButtonInput(PartyMenuStruct *partyMenu);
static u8 sub_0207ADB8(PartyMenuStruct *partyMenu);
static void sub_0207AFC4(PartyMenuStruct *partyMenu);
static u8 sub_0207B0B0(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B1BC(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B1C8(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B200(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B23C(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B32C(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B28C(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207B2DC(PartyMenuStruct *partyMenu, u8 *buf);
static u8 sub_0207BCC0(u16 move);
static int PartyMenu_SoftboiledTryTargetCheck(PartyMenuStruct *partyMenu);
static void sub_0207B51C(PartyMenuStruct *partyMenu, u8 selection, BOOL active);
static u8 sub_0207B600(PartyMenuStruct *partyMenu);
static int sub_0207B7E0(PartyMenuStruct *partyMenu);
static u8 sub_0207BA78(PartyMenuStruct *partyMenu);
static u8 sub_0207BB14(PartyMenuStruct *partyMenu);
static u8 sub_0207BB88(PartyMenuStruct *partyMenu);
static void sub_0207BBFC(u8 a0, s16 *px, s16 *py);
static BOOL PartyMenu_Subtask_HandleContextMenuInput(PartyMenuStruct *partyMenu, int *pState);
static int PartyMenu_Subtask_Softboiled(PartyMenuStruct *partyMenu);
static u8 PartyMenu_SoftboiledTargetCheck(PartyMenuStruct *partyMenu);
static BOOL PartyMenu_SoftboiledHPTransferStep(PartyMenuStruct *partyMenu, u8 partySlot, s8 delta);
static u8 sub_0207C0DC(PartyMenuStruct *partyMenu);
static int sub_0207C288(PartyMenuStruct *partyMenu);
static u8 sub_0207C3D0(PartyMenuStruct *partyMenu);
static int sub_0207C400(PartyMenuStruct *partyMenu);
static int sub_0207C5D4(PartyMenuStruct *partyMenu, Pokemon *mon, s32 *transformResult);
static void PartyMenu_SwapMonHeldItem(PartyMenuStruct *partyMenu, Pokemon *mon, u32 oldItemId, u32 newItemId);
static int PartyMenu_Subtask_PrintItemSwapMessage(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_PrintGriseousOrbMessage(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_WaitFormChange(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_PrintAskSwitchItems(PartyMenuStruct *partyMenu);
static int PartyMenu_Subtask_SwitchItemsHandleYesNoInput(PartyMenuStruct *partyMenu);
static int sub_0207C8B4(PartyMenuStruct *partyMenu);
static int sub_0207C908(PartyMenuStruct *partyMenu);
static int sub_0207CA30(PartyMenuStruct *partyMenu);

const OVY_MGR_TEMPLATE gOverlayTemplate_PartyMenu = {
    PartyMenuApp_Init,
    PartyMenuApp_Main,
    PartyMenuApp_Exit,
    FS_OVERLAY_ID_NONE,
};

static const UnkStruct_0207A22C _0210150C[2][6] = {
    {
        { 0x0000, 0x0000, 0x001E, 0x0010, 0x0010, 0x000E },
        { 0x0010, 0x0001, 0x009E, 0x0018, 0x0090, 0x0016 },
        { 0x0000, 0x0006, 0x001E, 0x0040, 0x0010, 0x003E },
        { 0x0010, 0x0007, 0x009E, 0x0048, 0x0090, 0x0046 },
        { 0x0000, 0x000C, 0x001E, 0x0070, 0x0010, 0x006E },
        { 0x0010, 0x000D, 0x009E, 0x0078, 0x0090, 0x0076 },
    }, {
        { 0x0000, 0x0000, 0x001E, 0x0010, 0x0010, 0x000E },
        { 0x0010, 0x0000, 0x009E, 0x0010, 0x0090, 0x000E },
        { 0x0000, 0x0006, 0x001E, 0x0040, 0x0010, 0x003E },
        { 0x0010, 0x0006, 0x009E, 0x0040, 0x0090, 0x003E },
        { 0x0000, 0x000C, 0x001E, 0x0070, 0x0010, 0x006E },
        { 0x0010, 0x000C, 0x009E, 0x0070, 0x0090, 0x006E },
    }
};

static const UnkStruct_02020654 _0210140C[8] = {
    { 0x40, 0x19, 0x00, 0x00, 0x07, 0x02, 0x07, 0x01 },
    { 0xC0, 0x21, 0x00, 0x00, 0x07, 0x03, 0x00, 0x02 },
    { 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x01, 0x03 },
    { 0xC0, 0x51, 0x00, 0x00, 0x01, 0x05, 0x02, 0x04 },
    { 0x40, 0x79, 0x00, 0x00, 0x02, 0x07, 0x03, 0x05 },
    { 0xC0, 0x81, 0x00, 0x00, 0x03, 0x07, 0x04, 0x07 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0xA8, 0x00, 0x00, 0x05, 0x01, 0x05, 0x00 },
};

static const UnkStruct_02020654 _0210144C[8] = {
    { 0x40, 0x19, 0x00, 0x00, 0x04, 0x02, 0x01, 0x01 },
    { 0xC0, 0x19, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00 },
    { 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x03, 0x03 },
    { 0xC0, 0x49, 0x00, 0x00, 0x01, 0x05, 0x02, 0x02 },
    { 0x40, 0x79, 0x00, 0x00, 0x02, 0x00, 0x05, 0x05 },
    { 0xC0, 0x79, 0x00, 0x00, 0x03, 0x07, 0x04, 0x04 },
    { 0xE0, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0xA8, 0x00, 0x00, 0x05, 0x01, 0xFF, 0xFF },
};

static const UnkStruct_02020654 _0210148C[8] = {
    { 0x40, 0x19, 0x00, 0x00, 0x07, 0x02, 0x07, 0x01 },
    { 0xC0, 0x21, 0x00, 0x00, 0x07, 0x03, 0x00, 0x02 },
    { 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x01, 0x03 },
    { 0xC0, 0x51, 0x00, 0x00, 0x01, 0x05, 0x02, 0x04 },
    { 0x40, 0x79, 0x00, 0x00, 0x02, 0x06, 0x03, 0x05 },
    { 0xC0, 0x81, 0x00, 0x00, 0x03, 0x06, 0x04, 0x06 },
    { 0xE0, 0xA8, 0x00, 0x00, 0x05, 0x07, 0x05, 0x07 },
    { 0xE0, 0xB8, 0x00, 0x00, 0x06, 0x01, 0x06, 0x00 },
};

static const UnkStruct_02020654 _021014CC[8] = {
    { 0x40, 0x19, 0x00, 0x00, 0x05, 0x02, 0x05, 0x01 },
    { 0xC0, 0x21, 0x00, 0x00, 0x05, 0x03, 0x00, 0x02 },
    { 0x40, 0x49, 0x00, 0x00, 0x00, 0x04, 0x01, 0x03 },
    { 0xC0, 0x51, 0x00, 0x00, 0x01, 0x05, 0x02, 0x04 },
    { 0x40, 0x79, 0x00, 0x00, 0x02, 0x00, 0x03, 0x05 },
    { 0xC0, 0x81, 0x00, 0x00, 0x03, 0x00, 0x04, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

static const u16 sFieldMoves[16] = {
    MOVE_CUT,
    MOVE_FLY,
    MOVE_SURF,
    MOVE_STRENGTH,
    MOVE_ROCK_SMASH,
    MOVE_WATERFALL,
    MOVE_ROCK_CLIMB,
    MOVE_WHIRLPOOL,
    MOVE_FLASH,
    MOVE_TELEPORT,
    MOVE_DIG,
    MOVE_SWEET_SCENT,
    MOVE_CHATTER,
    MOVE_HEADBUTT,
    MOVE_MILK_DRINK,
    MOVE_SOFTBOILED,
};

static BOOL PartyMenuApp_Init(OVY_MANAGER *manager, int *pState) {
    PartyMenuStruct *partyMenu;
    NARC * narc;

    Main_SetVBlankIntrCB(NULL, NULL);
    HBlankInterruptDisable();
    GfGfx_DisableEngineAPlanes();
    GfGfx_DisableEngineBPlanes();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);
    G2_BlendNone();
    G2S_BlendNone();
    GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
    SetKeyRepeatTimers(4, 8);
    CreateHeap(HEAP_ID_3, HEAP_ID_PARTY_MENU, 0x30000);

    narc = NARC_New(NARC_a_0_2_1, HEAP_ID_PARTY_MENU);
    partyMenu = sub_02079BD8(manager);
    BeginNormalPaletteFade(2, 3, 3, RGB_BLACK, 6, 1, HEAP_ID_PARTY_MENU);
    sub_02079CE4(partyMenu);
    sub_02079700();
    sub_02079758(partyMenu->bgConfig);
    sub_02079A14(partyMenu, narc);
    sub_020210BC();
    sub_02021148(4);
    sub_02004EC4(57, 0, 0);
    PartyMenu_SetContextMenuStaticStrings(partyMenu);
    PartyMenu_AddAllWindows(partyMenu);
    sub_0207EB24(partyMenu);
    sub_0207EDD4(partyMenu);
    sub_02079D38(partyMenu);
    PartyMenu_DrawPanelsAndPush(partyMenu);
    sub_0207B51C(partyMenu, partyMenu->partyMonIndex, TRUE);
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_USE_ITEM || partyMenu->args->context == PARTY_MENU_CONTEXT_EVO_STONE) {
        if (!sub_020817C4(partyMenu->args->itemId)) {
            sub_0207DAC4(partyMenu, msg_0300_00033, TRUE);
        }
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_TM_HM) {
        sub_0207DAC4(partyMenu, msg_0300_00034, TRUE);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_9 || partyMenu->args->context == PARTY_MENU_CONTEXT_14) {
        sub_0207DAC4(partyMenu, msg_0300_00032, TRUE);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_7 || partyMenu->args->context == PARTY_MENU_CONTEXT_8 || partyMenu->args->context == PARTY_MENU_CONTEXT_11 || partyMenu->args->context == PARTY_MENU_CONTEXT_12) {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_2 || partyMenu->args->context == PARTY_MENU_CONTEXT_17) {
        sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_15) {
        sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_21) {
        sub_0207DAC4(partyMenu, msg_0300_00184, TRUE);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_22) {
        sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
        sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
    } else if (partyMenu->args->context != PARTY_MENU_CONTEXT_10) {
        sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
    } else {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
    }
    sub_0207A89C(partyMenu);
    sub_02002B8C(TRUE);
    Main_SetVBlankIntrCB(sub_020796B8, partyMenu);
    sub_0203A994(2);
    FontID_Alloc(4, HEAP_ID_PARTY_MENU);
    NARC_Delete(narc);
    return TRUE;
}

static BOOL PartyMenuApp_Main(OVY_MANAGER *manager, int *pState) {
    PartyMenuStruct *partyMenu = (PartyMenuStruct *)OverlayManager_GetData(manager);

    switch (*pState) {
    case PARTY_MENU_STATE_INIT:
        *pState = PartyMenu_Subtask_Init(partyMenu);
        break;
    case PARTY_MENU_STATE_1:
        *pState = sub_02079308(partyMenu);
        break;
    case PARTY_MENU_STATE_HANDLE_CONTEXT_MENU_INPUT:
        if (PartyMenu_Subtask_HandleContextMenuInput(partyMenu, pState) == TRUE) {
            *pState = PARTY_MENU_STATE_1;
        }
        break;
    case PARTY_MENU_STATE_3:
        *pState = sub_02080B74(partyMenu);
        break;
    case PARTY_MENU_STATE_4:
        *pState = sub_020793C0(partyMenu);
        break;
    case PARTY_MENU_STATE_5:
        *pState = partyMenu->unk_C54(partyMenu);
        break;
    case PARTY_MENU_STATE_SELECT_MOVE:
        *pState = PartyMenu_Subtask_SelectMove(partyMenu);
        break;
    case PARTY_MENU_STATE_7:
        *pState = sub_02081820(partyMenu);
        break;
    case PARTY_MENU_STATE_8:
        *pState = sub_02079400(partyMenu);
        break;
    case PARTY_MENU_STATE_PRINT_ASK_SWITCH_ITEMS:
        *pState = PartyMenu_Subtask_PrintAskSwitchItems(partyMenu);
        break;
    case PARTY_MENU_STATE_YESNO_ASK_SWITCH_ITEMS:
        *pState = PartyMenu_Subtask_SwitchItemsHandleYesNoInput(partyMenu);
        break;
    case PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE:
        *pState = PartyMenu_Subtask_PrintItemSwapMessage(partyMenu);
        break;
    case PARTY_MENU_STATE_PRINT_TAKE_GRISEOUS_ORB_MESSAGE:
        *pState = PartyMenu_Subtask_PrintGriseousOrbMessage(partyMenu);
        break;
    case PARTY_MENU_STATE_WAIT_FORM_CHANGE:
        *pState = PartyMenu_Subtask_WaitFormChange(partyMenu);
        break;
    case PARTY_MENU_STATE_14:
        *pState = sub_0207C908(partyMenu);
        break;
    case PARTY_MENU_STATE_HANDLE_INPUT:
        *pState = PartyMenu_Subtask_HandleInput(partyMenu);
        break;
    case PARTY_MENU_STATE_16:
        *pState = sub_0207C400(partyMenu);
        break;
    case PARTY_MENU_STATE_17:
        *pState = sub_0207F694(partyMenu);
        break;
    case PARTY_MENU_STATE_18:
        *pState = sub_0207F6E8(partyMenu);
        break;
    case PARTY_MENU_STATE_19:
        *pState = sub_0207F720(partyMenu);
        break;
    case PARTY_MENU_STATE_20:
        *pState = sub_0207FA08(partyMenu);
        break;
    case PARTY_MENU_STATE_21:
        *pState = sub_02079550(partyMenu);
        break;
    case PARTY_MENU_STATE_22:
        *pState = sub_02082370(partyMenu);
        break;
    case PARTY_MENU_STATE_23:
        *pState = sub_02080610(partyMenu);
        break;
    case PARTY_MENU_STATE_WAIT_TEXT_PRINTER:
        *pState = PartyMenu_Subtask_WaitTextPrinter(partyMenu);
        break;
    case PARTY_MENU_STATE_25:
        *pState = sub_020794EC(partyMenu);
        break;
    case PARTY_MENU_STATE_YES_NO_INIT:
        *pState = PartyMenu_Subtask_YesNoMenuInit(partyMenu);
        break;
    case PARTY_MENU_STATE_YES_NO_HANDLE_INPUT:
        *pState = PartyMenu_Subtask_YesNoMenuHandleInput(partyMenu);
        break;
    case PARTY_MENU_STATE_SELECT_SWITCH_MON: {
        u8 x = sub_0207B600(partyMenu);
        if (x == 0) {
            *pState = PARTY_MENU_STATE_29;
        } else if (x == 3) {
            *pState = PARTY_MENU_STATE_1;
        }
        break;
    }
    case PARTY_MENU_STATE_29:
        if (sub_0207FD6C(partyMenu) == TRUE) {
            *pState = PARTY_MENU_STATE_1;
        }
        break;
    case PARTY_MENU_STATE_SOFTBOILED:
        *pState = PartyMenu_Subtask_Softboiled(partyMenu);
        break;
    case PARTY_MENU_STATE_FORM_CHANGE_ANIM:
        if (PartyMenu_AnimateIconFormChange(partyMenu) == TRUE) {
            PartyMenu_FormChangeScene_End(partyMenu);
            *pState = PARTY_MENU_STATE_25;
        }
        else {
            *pState = PARTY_MENU_STATE_FORM_CHANGE_ANIM;
        }
        break;
    case PARTY_MENU_STATE_BEGIN_EXIT:
        sub_020880CC(1, HEAP_ID_PARTY_MENU);
        *pState = PARTY_MENU_STATE_WAIT_EXIT_FADE_OUT;
        break;
    case PARTY_MENU_STATE_WAIT_EXIT_FADE_OUT:
        if (IsPaletteFadeFinished() == TRUE) {
            partyMenu->args->partySlot = partyMenu->partyMonIndex;
            return TRUE;
        }
        break;
    }

    sub_0207F178(partyMenu);
    sub_0207F2F8(partyMenu);
    sub_0207AC20(partyMenu);
    sub_02079230(partyMenu);
    sub_0200D020(partyMenu->spriteGfxHandler);
    return FALSE;
}

void sub_02079224(PartyMenuStruct *partyMenu, BOOL a1) {
    partyMenu->unk_C7C = a1;
}

static void sub_02079230(PartyMenuStruct *partyMenu) {
    if (partyMenu->unk_C7C) {
        partyMenu->unk_C78 += 12;
        if (partyMenu->unk_C78 > 40) {
            partyMenu->unk_C78 = 40;
        }
        sub_0207F334(partyMenu, partyMenu->unk_C78);
    } else {
        partyMenu->unk_C78 -= 12;
        if (partyMenu->unk_C78 < 0) {
            partyMenu->unk_C78 = 0;
        }
        sub_0207F334(partyMenu, partyMenu->unk_C78);
    }
}

static int PartyMenu_Subtask_Init(PartyMenuStruct *partyMenu) {
    if (IsPaletteFadeFinished() == TRUE) {
        if (partyMenu->args->context == PARTY_MENU_CONTEXT_USE_ITEM || partyMenu->args->context == PARTY_MENU_CONTEXT_EVO_STONE) {
            if (sub_020817C4(partyMenu->args->itemId) == TRUE) {
                partyMenu->afterTextPrinterState = PARTY_MENU_STATE_INIT;
                return PARTY_MENU_STATE_7;
            } else {
                return PARTY_MENU_STATE_4;
            }
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_TM_HM) {
            return PARTY_MENU_STATE_21;
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_7) {
            return sub_020822CC(partyMenu);
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_8) {
            return sub_02081ED0(partyMenu);
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_11 || partyMenu->args->context == PARTY_MENU_CONTEXT_12) {
            return PARTY_MENU_STATE_14;
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_9) {
            return PARTY_MENU_STATE_8;
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_10) {
            return PARTY_MENU_STATE_16;
        } else {
            return PARTY_MENU_STATE_1;
        }
    } else {
        return PARTY_MENU_STATE_INIT;
    }
}

static int sub_02079308(PartyMenuStruct *partyMenu) {
    switch (sub_0207ADB8(partyMenu)) {
    case 0:
        switch (partyMenu->args->context) {
        case PARTY_MENU_CONTEXT_3:
        case PARTY_MENU_CONTEXT_20:
            partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
            return PARTY_MENU_STATE_BEGIN_EXIT;
        case PARTY_MENU_CONTEXT_14:
            sub_02082868(partyMenu);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        case PARTY_MENU_CONTEXT_19:
            return sub_0207CA30(partyMenu);
        default:
            sub_02079224(partyMenu, 1);
            return PARTY_MENU_STATE_HANDLE_CONTEXT_MENU_INPUT;
        }
    case 4:
        return sub_0207B7E0(partyMenu);
    case 3:
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
        return PARTY_MENU_STATE_BEGIN_EXIT;
    case 2:
        if (partyMenu->args->context != PARTY_MENU_CONTEXT_15) {
            partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_1;
            return PARTY_MENU_STATE_BEGIN_EXIT;
        } else {
            thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
            return sub_020807AC(partyMenu);
        }
    }
    return PARTY_MENU_STATE_1;
}

static int sub_020793C0(PartyMenuStruct *partyMenu) {
    u8 x = sub_0207C0DC(partyMenu);
    if (x == 0 || x == 2) {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
        return sub_0207C288(partyMenu);
    } else if (x == 3) {
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
        return PARTY_MENU_STATE_BEGIN_EXIT;
    } else {
        return PARTY_MENU_STATE_4;
    }
}

static int sub_02079400(PartyMenuStruct *partyMenu) {
    u8 x = sub_0207C0DC(partyMenu);
    if (x == 0 || x == 2) {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
        return sub_0207C400(partyMenu);
    } else if (x == 3) {
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
        return PARTY_MENU_STATE_BEGIN_EXIT;
    } else {
        return PARTY_MENU_STATE_8;
    }
}

static int PartyMenu_Subtask_HandleInput(PartyMenuStruct *partyMenu) {
    u32 func = PartyMenu_HandleInput_TopLevel(partyMenu, partyMenu->contextMenuCursor);
    switch (func) {
    case LIST_CANCEL:
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
        sub_0200E5D4(&partyMenu->windows[PARTY_MENU_WINDOW_ID_35], TRUE);
        ClearWindowTilemapAndScheduleTransfer(&partyMenu->windows[PARTY_MENU_WINDOW_ID_35]);
        sub_02079224(partyMenu, FALSE);
        sub_0207CB20(partyMenu);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
        return PARTY_MENU_STATE_1;
    default: {
        int result;
        ((PartyMenuStruct_SubC90_UnkFunc)func)(partyMenu, &result);
        return result;
    }
    case LIST_NOTHING_CHOSEN:
        return PARTY_MENU_STATE_HANDLE_INPUT;
    }
}

static int PartyMenu_Subtask_WaitTextPrinter(PartyMenuStruct *partyMenu) {
    if (TextPrinterCheckActive(partyMenu->textPrinterId) == FALSE) {
        return partyMenu->afterTextPrinterState;
    } else {
        return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
    }
}

static int sub_020794EC(PartyMenuStruct *partyMenu) {
    return PARTY_MENU_STATE_BEGIN_EXIT;
}

static int PartyMenu_Subtask_YesNoMenuInit(PartyMenuStruct *partyMenu) {
    sub_0207DBCC(partyMenu);
    return PARTY_MENU_STATE_YES_NO_HANDLE_INPUT;
}

static int PartyMenu_Subtask_YesNoMenuHandleInput(PartyMenuStruct *partyMenu) {
    switch (YesNoPrompt_HandleInput(partyMenu->yesNoPrompt)) {
    case YESNORESPONSE_YES:
        YesNoPrompt_Destroy(partyMenu->yesNoPrompt);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        return partyMenu->yesCallback(partyMenu);
    case YESNORESPONSE_NO:
        YesNoPrompt_Destroy(partyMenu->yesNoPrompt);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        return partyMenu->noCallback(partyMenu);
    default:
        return PARTY_MENU_STATE_YES_NO_HANDLE_INPUT;
    }
}

static int sub_02079550(PartyMenuStruct *partyMenu) {
    u8 x = sub_0207C0DC(partyMenu);
    if (x == 0 || x == 2) {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
        if (partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg != 1) {
            return sub_02082134(partyMenu);
        } else {
            sub_0207DAEC(partyMenu, -1, TRUE);
            partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_25;
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00102, partyMenu->formattedStrBuf);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
    } else if (x == 3) {
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
        return PARTY_MENU_STATE_BEGIN_EXIT;
    } else {
        return PARTY_MENU_STATE_21;
    }
}

static BOOL PartyMenuApp_Exit(OVY_MANAGER *manager, int *pState) {
    u32 i;
    PartyMenuStruct *partyMenu = (PartyMenuStruct *)OverlayManager_GetData(manager);
    sub_02002B8C(FALSE);
    Main_SetVBlankIntrCB(NULL, NULL);
    sub_0207EFA4(partyMenu);
    PartyMenu_RemoveAllWindows(partyMenu);
    sub_020798C4(partyMenu->bgConfig);
    sub_02021238();
    GF_DestroyVramTransferManager();
    for (i = 0; i < PARTY_SIZE; ++i) {
        String_Delete(partyMenu->monsDrawState[i].nickname);
    }
    String_Delete(partyMenu->formattedStrBuf);
    String_Delete(partyMenu->unformattedStrBuf);
    for (i = 0; i < 20; ++i) {
        String_Delete(partyMenu->contextMenuStrings[i]);
    }
    DestroyMsgData(partyMenu->msgData);
    MessagePrinter_Delete(partyMenu->msgPrinter);
    MessageFormat_Delete(partyMenu->msgFormat);
    if (partyMenu->pokedex != NULL) {
        sub_0207495C(partyMenu->pokedex);
    }
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_0) {
        sub_02004B10();
    }
    FontID_Release(4);
    OverlayManager_FreeData(manager);
    DestroyHeap(HEAP_ID_PARTY_MENU);
    sub_0203A964();
    return TRUE;
}

static void sub_020796B8(void *cbData) {
    PartyMenuStruct *partyMenu = (PartyMenuStruct *)cbData;

    BgSetPosTextAndCommit(partyMenu->bgConfig, GF_BG_LYR_SUB_0, BG_POS_OP_SET_Y, partyMenu->unk_C78);
    BgSetPosTextAndCommit(partyMenu->bgConfig, GF_BG_LYR_SUB_2, BG_POS_OP_SET_Y, partyMenu->unk_C78);
    DoScheduledBgGpuUpdates(partyMenu->bgConfig);
    GF_RunVramTransferTasks();
    thunk_OamManager_ApplyAndResetBuffers();
    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static TouchscreenHitbox _02110128[][8] = {
    {
        { .rect = { 0x00, 0x30, 0x00, 0x80 } },
        { .rect = { 0x08, 0x38, 0x80, 0x00 } },
        { .rect = { 0x30, 0x60, 0x00, 0x80 } },
        { .rect = { 0x38, 0x68, 0x80, 0x00 } },
        { .rect = { 0x60, 0x90, 0x00, 0x80 } },
        { .rect = { 0x68, 0x98, 0x80, 0x00 } },
        { .rect = { 0x98, 0xC0, 0xC8, 0x00 } },
        { .rect = { TOUCHSCREEN_RECTLIST_END } },
    }, {
        { .rect = { 0x00, 0x30, 0x00, 0x80 } },
        { .rect = { 0x00, 0x30, 0x80, 0x00 } },
        { .rect = { 0x30, 0x60, 0x00, 0x80 } },
        { .rect = { 0x30, 0x60, 0x80, 0x00 } },
        { .rect = { 0x60, 0x90, 0x00, 0x80 } },
        { .rect = { 0x60, 0x90, 0x80, 0x00 } },
        { .rect = { 0x98, 0xC0, 0xC8, 0x00 } },
        { .rect = { TOUCHSCREEN_RECTLIST_END } },
    }
};

static TouchscreenHitbox _02110104[] = {
    { .rect = { 0x00, 0x30, 0x00, 0x80 } },
    { .rect = { 0x08, 0x38, 0x80, 0x00 } },
    { .rect = { 0x30, 0x60, 0x00, 0x80 } },
    { .rect = { 0x38, 0x68, 0x80, 0x00 } },
    { .rect = { 0x60, 0x90, 0x00, 0x80 } },
    { .rect = { 0x68, 0x98, 0x80, 0x00 } },
    { .rect = { 0xB0, 0xC0, 0xC8, 0x00 } },
    { .rect = { 0xA0, 0xB0, 0xC8, 0x00 } },
    { .rect = { TOUCHSCREEN_RECTLIST_END } },
};

static void sub_02079700(void) {
    GraphicsBanks graphicsBanks = {
        .bg = GX_VRAM_BG_128_A,
        .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
        .subbg = GX_VRAM_SUB_BG_128_C,
        .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
        .obj = GX_VRAM_OBJ_64_E,
        .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
        .subobj = GX_VRAM_SUB_OBJ_16_I,
        .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
        .tex = GX_VRAM_TEX_0_B,
        .texpltt = GX_VRAM_TEXPLTT_01_FG,
    };
    GfGfx_SetBanks(&graphicsBanks);
}

static void sub_02079720(BgConfig *bgConfig) {
    BgTemplate bgTemplate = {
        .x = 0,
        .y = 0,
        .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
        .baseTile = 0,
        .size = GF_BG_SCR_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = GX_BG_AREAOVER_XLU,
        .mosaic = 0,
    };
    InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_0, &bgTemplate, GF_BG_TYPE_TEXT);
    BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_0);
}

static void sub_02079758(BgConfig *bgConfig) {
    {
        GraphicsModes graphicsModes = {
            .dispMode = GX_DISPMODE_GRAPHICS,
            .bgMode = GX_BGMODE_0,
            .subMode = GX_BGMODE_0,
            ._2d3dMode = GX_BG0_AS_2D,
        };
        SetBothScreensModesAndDisable(&graphicsModes);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_0, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_0);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_1, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_1);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_2, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_MAIN_2);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_3, &bgTemplate, GF_BG_TYPE_TEXT);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_2, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_SUB_2);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_0, &bgTemplate, GF_BG_TYPE_TEXT);
        BgClearTilemapBufferAndCommit(bgConfig, GF_BG_LYR_SUB_0);
    }

    {
        BgTemplate bgTemplate = {
            .x = 0,
            .y = 0,
            .bufferSize = GF_BG_BUF_SIZE_256x256_4BPP,
            .baseTile = 0,
            .size = GF_BG_SCR_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = GX_BG_AREAOVER_XLU,
            .mosaic = 0,
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_1, &bgTemplate, GF_BG_TYPE_TEXT);
    }

    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, HEAP_ID_PARTY_MENU);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_0, 0x20, 0, HEAP_ID_PARTY_MENU);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_2, 0x20, 0, HEAP_ID_PARTY_MENU);
}

static void sub_020798C4(BgConfig *bgConfig) {
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_ALL, GF_PLANE_TOGGLE_OFF);
    GfGfx_EngineBTogglePlanes((GXPlaneMask)(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ), GF_PLANE_TOGGLE_OFF);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_2);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_1);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_0);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_3);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_2);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_0);
    FreeToHeapExplicit(HEAP_ID_PARTY_MENU, bgConfig);
}

void sub_0207991C(PartyMenuStruct *partyMenu, int a1) {
    if (a1 == FALSE) {
        ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_OFF);
        FreeBgTilemapBuffer(partyMenu->bgConfig, GF_BG_LYR_MAIN_0);
        GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);
        partyMenu->unk_C84 = sub_0207997C(HEAP_ID_PARTY_MENU);
    } else {
        GfGfx_EngineATogglePlanes(GX_PLANEMASK_BG0, GF_PLANE_TOGGLE_OFF);
        sub_02079A0C(partyMenu->unk_C84);
        GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_2D);
        sub_02079720(partyMenu->bgConfig);
        BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, HEAP_ID_PARTY_MENU);
    }
}

GF3DVramMan *sub_0207997C(HeapID heapId) {
    return GF_3DVramMan_Create(heapId, GF_3D_TEXALLOC_LNK, 1, GF_3D_PLTTALLOC_LNK, 2, sub_0207999C);
}

static void sub_0207999C(void) {
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
    G3X_AlphaTest(FALSE, 0);
    G3X_AlphaBlend(TRUE);
    G3X_EdgeMarking(FALSE);
    G3X_SetFog(FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(RGB_BLACK, 0, 0x7FFF, 0x3F, FALSE);
    G3_ViewPort(0, 0, 255, 191);
}

static void sub_02079A0C(GF3DVramMan *gf3dVramMan) {
    GF_3DVramMan_Delete(gf3dVramMan);
}

static void sub_02079A14(PartyMenuStruct *partyMenu, NARC *narc) {
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 15, partyMenu->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 17, partyMenu->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, HEAP_ID_PARTY_MENU);

    void *nclrFile = NARC_AllocAndReadWholeMember(narc, 16, HEAP_ID_PARTY_MENU);
    NNSG2dPaletteData *plttData;
    NNS_G2dGetUnpackedPaletteData(nclrFile, &plttData);
    u16 *plttBuf = AllocFromHeap(HEAP_ID_PARTY_MENU, plttData->szByte);
    memcpy(plttBuf, plttData->pRawData, plttData->szByte);
    plttBuf[0] = RGB_BLACK;
    BG_LoadPlttData(GF_PAL_LOCATION_MAIN_OBJEXT, plttBuf, plttData->szByte, 0);
    FreeToHeap(plttBuf);
    memcpy(partyMenu->unk_554, (u8 *)plttData->pRawData + 0x60, 0x100);
    FreeToHeap(nclrFile);
    LoadFontPal1(GF_PAL_LOCATION_MAIN_BG, (enum GFPalSlotOffset)0x1A0, HEAP_ID_PARTY_MENU);
    LoadFontPal1(GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)0x40, HEAP_ID_PARTY_MENU);
    LoadUserFrameGfx1(partyMenu->bgConfig, GF_BG_LYR_MAIN_0, 1, 14, 0, HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 26, partyMenu->bgConfig, GF_BG_LYR_MAIN_0, 10, 0, FALSE, HEAP_ID_PARTY_MENU);
    LoadUserFrameGfx2(partyMenu->bgConfig, GF_BG_LYR_MAIN_0, 42, 15, Options_GetFrame(partyMenu->args->options), HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 3, partyMenu->bgConfig, GF_BG_LYR_SUB_0, 0, 0, FALSE, HEAP_ID_PARTY_MENU);
    GfGfxLoader_GXLoadPalFromOpenNarc(narc, 4, GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)0x20, 0x20, HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 12, partyMenu->bgConfig, GF_BG_LYR_SUB_1, 0, 0, FALSE, HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 14, partyMenu->bgConfig, GF_BG_LYR_SUB_1, 0, 0, FALSE, HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 24, partyMenu->bgConfig, GF_BG_LYR_SUB_0, 0, 0, FALSE, HEAP_ID_PARTY_MENU);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 25, partyMenu->bgConfig, GF_BG_LYR_SUB_0, 0, 0, FALSE, HEAP_ID_PARTY_MENU);
    GfGfxLoader_GXLoadPalFromOpenNarc(narc, 13, GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)0, 0x40, HEAP_ID_PARTY_MENU);
    sub_0207CAAC(HEAP_ID_PARTY_MENU, partyMenu->unk_314, partyMenu->unk_3D4, partyMenu->unk_494);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, RGB_BLACK);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB_BLACK);
}

PartyMenuStruct *sub_02079BD8(OVY_MANAGER *manager) {
    u32 i;
    PartyMenuStruct *ret = (PartyMenuStruct *)OverlayManager_CreateAndGetData(manager, sizeof(PartyMenuStruct), HEAP_ID_PARTY_MENU);
    memset(ret, 0, sizeof(PartyMenuStruct));
    ret->args = OverlayManager_GetArgs(manager);
    ret->bgConfig = BgConfig_Alloc(HEAP_ID_PARTY_MENU);
    if (ret->args->context == PARTY_MENU_CONTEXT_2 && ret->args->unk_14 != NULL) {
        ret->pokedex = sub_02074944(HEAP_ID_PARTY_MENU);
    } else {
        ret->pokedex = NULL;
    }
    ret->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_msgdata_msg, NARC_msg_msg_0300_bin, HEAP_ID_PARTY_MENU);
    ret->msgPrinter = MessagePrinter_New(15, 14, 0, HEAP_ID_PARTY_MENU);
    ret->msgFormat = MessageFormat_New(HEAP_ID_PARTY_MENU);
    for (i = 0; i < PARTY_SIZE; ++i) {
        ret->monsDrawState[i].nickname = String_New(POKEMON_NAME_LENGTH + 1, HEAP_ID_PARTY_MENU);
    }
    ret->formattedStrBuf = String_New(0x100, HEAP_ID_PARTY_MENU);
    ret->unformattedStrBuf = String_New(0x100, HEAP_ID_PARTY_MENU);
    for (i = 0; i < 20; ++i) {
        ret->contextMenuStrings[i] = String_New(32, HEAP_ID_PARTY_MENU);
    }
    ret->unk_C7C = FALSE;
    ret->partyMonIndex = ret->args->partySlot;
    ret->unk_C66 = ret->partyMonIndex;
    return ret;
}

static void sub_02079CE4(PartyMenuStruct *partyMenu) {
    if (partyMenu->args->context & 0x80) {
        partyMenu->cancelDisabled = TRUE;
        partyMenu->args->context ^= 0x80;
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_21) {
        partyMenu->cancelDisabled = TRUE;
    } else {
        partyMenu->cancelDisabled = FALSE;
    }
}

static void sub_02079D38(PartyMenuStruct *partyMenu) {
    u8 r4 = 3;
    if (partyMenu->args->unk_25 == 2) {
        partyMenu->unk_948 = _0210144C;
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_2 || partyMenu->args->context == PARTY_MENU_CONTEXT_17 || partyMenu->args->context == PARTY_MENU_CONTEXT_22 || partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
        partyMenu->unk_948 = _0210148C;
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_21) {
        partyMenu->unk_948 = _021014CC;
    } else {
        partyMenu->unk_948 = _0210140C;
    }
    if (partyMenu->args->context != PARTY_MENU_CONTEXT_2 && partyMenu->args->context != PARTY_MENU_CONTEXT_17 && partyMenu->args->context != PARTY_MENU_CONTEXT_23 && partyMenu->args->context != PARTY_MENU_CONTEXT_22) {
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_8], FALSE);
        Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], 0);
        s16 x, y;
        Sprite_GetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], &x, &y);
        Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], x, y - 8);
        r4 ^= 1;
    }
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_4 || partyMenu->args->context == PARTY_MENU_CONTEXT_21) {
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], FALSE);
        r4 ^= 2;
    }
    sub_0207D998(partyMenu, r4);
}

static u8 PartyMenu_IsMonDrawStateActive(PartyMenuStruct *partyMenu, u8 partySlot) {
    return partyMenu->monsDrawState[partySlot].active;
}

BOOL sub_02079E38(PartyMenuStruct *partyMenu, u8 partySlot) {
    Pokemon *mon;
    u32 unused;
    u16 species;  // sp4

    (void)unused;

    partyMenu->monsDrawState[partySlot].active = FALSE;
    if (Party_GetCount(partyMenu->args->party) <= partySlot) {
        return FALSE;
    }
    mon = Party_GetMonByIndex(partyMenu->args->party, partySlot);
    species = (u16)GetMonData(mon, MON_DATA_SPECIES, NULL);
    if (species == SPECIES_NONE) {
        return FALSE;
    }
    PartyMenu_BufferMonNickname(partyMenu, mon, partySlot);
    partyMenu->monsDrawState[partySlot].species = species;
    partyMenu->monsDrawState[partySlot].hp = (u16)GetMonData(mon, MON_DATA_HP, NULL);
    partyMenu->monsDrawState[partySlot].maxHp = (u16)GetMonData(mon, MON_DATA_MAXHP, NULL);
    partyMenu->monsDrawState[partySlot].level = (u16)GetMonData(mon, MON_DATA_LEVEL, NULL);
    partyMenu->monsDrawState[partySlot].heldItem = (u16)GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
    partyMenu->monsDrawState[partySlot].capsule = (u16)GetMonData(mon, MON_DATA_CAPSULE, NULL);
    partyMenu->monsDrawState[partySlot].isEgg = (u8)GetMonData(mon, MON_DATA_IS_EGG, NULL);
    partyMenu->monsDrawState[partySlot].form = (u8)GetMonData(mon, MON_DATA_FORM, NULL);
    if (GetMonData(mon, MON_DATA_NO_PRINT_GENDER, NULL) == TRUE) {
        partyMenu->monsDrawState[partySlot].dontPrintGenderSymbol = FALSE;
    } else {
        partyMenu->monsDrawState[partySlot].dontPrintGenderSymbol = TRUE;
    }
    partyMenu->monsDrawState[partySlot].gender = GetMonGender(mon);
    partyMenu->monsDrawState[partySlot].active = TRUE;
    partyMenu->monsDrawState[partySlot].status = (u8)Pokemon_GetStatusIconId(mon);
    PartyMenu_MonSuperContestEligibilityCheck(partyMenu, mon, partySlot);
    return TRUE;
}

static void PartyMenu_MonSuperContestEligibilityCheck(PartyMenuStruct *partyMenu, Pokemon *mon, u8 partySlot) {
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_SUPER_CONTEST) {
        // Eggs and dead mons cannot compete
        if (partyMenu->monsDrawState[partySlot].isEgg == TRUE || partyMenu->monsDrawState[partySlot].hp == 0) {
            partyMenu->monsDrawState[partySlot].isContestCompatible = FALSE;
        } else {
            // A Pokemon must be at the minimum required ribbon level and have at least 2 moves
            u32 numRibbons = Pokemon_CountRibbonsByCategory(mon, partyMenu->args->contestStat);
            u32 i;
            for (i = 0; i < 4; ++i) {
                if (GetMonData(mon, MON_DATA_MOVE1 + i, NULL) == MOVE_NONE) {
                    break;
                }
            }
            if (partyMenu->args->contestLevel <= numRibbons && i >= 2) {
                partyMenu->monsDrawState[partySlot].isContestCompatible = TRUE;
            } else {
                partyMenu->monsDrawState[partySlot].isContestCompatible = FALSE;
            }
        }
    }
}

static u32 Pokemon_CountRibbonsByCategory(Pokemon *mon, u8 contestStat) {
    u32 result;
    switch (contestStat) {
    case COOL:
        result  = GetMonData(mon, MON_DATA_COOL_RIBBON, NULL);
        result += GetMonData(mon, MON_DATA_COOL_RIBBON_GREAT, NULL);
        result += GetMonData(mon, MON_DATA_COOL_RIBBON_ULTRA, NULL);
        result += GetMonData(mon, MON_DATA_COOL_RIBBON_MASTER, NULL);
        break;
    case BEAUTY:
        result  = GetMonData(mon, MON_DATA_BEAUTY_RIBBON, NULL);
        result += GetMonData(mon, MON_DATA_BEAUTY_RIBBON_GREAT, NULL);
        result += GetMonData(mon, MON_DATA_BEAUTY_RIBBON_ULTRA, NULL);
        result += GetMonData(mon, MON_DATA_BEAUTY_RIBBON_MASTER, NULL);
        break;
    case CUTE:
        result  = GetMonData(mon, MON_DATA_CUTE_RIBBON, NULL);
        result += GetMonData(mon, MON_DATA_CUTE_RIBBON_GREAT, NULL);
        result += GetMonData(mon, MON_DATA_CUTE_RIBBON_ULTRA, NULL);
        result += GetMonData(mon, MON_DATA_CUTE_RIBBON_MASTER, NULL);
        break;
    case SMART:
        result  = GetMonData(mon, MON_DATA_SMART_RIBBON, NULL);
        result += GetMonData(mon, MON_DATA_SMART_RIBBON_GREAT, NULL);
        result += GetMonData(mon, MON_DATA_SMART_RIBBON_ULTRA, NULL);
        result += GetMonData(mon, MON_DATA_SMART_RIBBON_MASTER, NULL);
        break;
    case TOUGH:
        result  = GetMonData(mon, MON_DATA_TOUGH_RIBBON, NULL);
        result += GetMonData(mon, MON_DATA_TOUGH_RIBBON_GREAT, NULL);
        result += GetMonData(mon, MON_DATA_TOUGH_RIBBON_ULTRA, NULL);
        result += GetMonData(mon, MON_DATA_TOUGH_RIBBON_MASTER, NULL);
        break;
    }
    return result;
}

u16 *sub_0207A16C(PartyMenuStruct *partyMenu) {
    return &partyMenu->unk_3D4[0x36];
}

static void sub_0207A174(PartyMenuStruct *partyMenu, u8 partySlot, u8 x, u8 y, u8 a4) {
    void *src;
    if (partySlot == 0 || (partyMenu->args->unk_25 != 0 && partySlot == 1)) {
        src = partyMenu->unk_314;
    } else {
        src = partyMenu->unk_3D4;
    }
    partyMenu->monsDrawState[partySlot].unk_14 = x;
    partyMenu->monsDrawState[partySlot].unk_15 = y;
    CopyToBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, x, y, 16, 6, src, 0, 0, 16, 6);
    if (!a4) {
        FillBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, 0x4B, x + 6, y + 3, 9, 1, TILEMAP_FILL_KEEP_PAL);
    }
    BgTilemapRectChangePalette(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, x, y, 16, 6, partySlot + 3);
    sub_0207A7F4(partyMenu, partySlot);
}

static void PartyMenu_DrawPanelsAndPush(PartyMenuStruct *partyMenu) {
    const UnkStruct_0207A22C *r1 = partyMenu->args->unk_25 == 2 ? _0210150C[1] : _0210150C[0];
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_EVO_STONE) {
        PartyMenu_DrawPanels_UseEvoStone(partyMenu, r1);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_TM_HM) {
        PartyMenu_DrawPanels_UseTMHM(partyMenu, r1);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_SUPER_CONTEST) {
        PartyMenu_Setup_SuperContestEntry(partyMenu, r1);
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_2 || partyMenu->args->context == PARTY_MENU_CONTEXT_17 || partyMenu->args->context == PARTY_MENU_CONTEXT_22 || partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
        PartyMenu_DrawPanels_FrontierFacilityEntry(partyMenu, r1);
    } else {
        PartyMenu_DrawPanels_Default(partyMenu, r1);
    }
    ScheduleBgTilemapBufferTransfer(partyMenu->bgConfig, GF_BG_LYR_MAIN_2);
    ScheduleBgTilemapBufferTransfer(partyMenu->bgConfig, GF_BG_LYR_SUB_0);
}

static void PartyMenu_DrawPanels_Default(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1) {
    NARC *narc = NARC_New(NARC_poketool_icongra_poke_icon, HEAP_ID_PARTY_MENU);
    for (u8 i = 0; i < PARTY_SIZE; ++i) {
        if (sub_02079E38(partyMenu, i) == TRUE) {
            if (partyMenu->monsDrawState[i].isEgg == TRUE) {
                sub_0207A174(partyMenu, i, a1[i].unk_0, a1[i].unk_2, FALSE);
            } else {
                sub_0207A174(partyMenu, i, a1[i].unk_0, a1[i].unk_2, TRUE);
            }
            sub_0207D5DC(partyMenu, i);
            sub_0207EBE4(partyMenu, i, a1[i].unk_4, a1[i].unk_6, narc);
            sub_0207EF5C(partyMenu, i, a1[i].unk_8, a1[i].unk_A);
            sub_0207F004(partyMenu, i, partyMenu->monsDrawState[i].heldItem);
            sub_0207F064(partyMenu, i, a1[i].unk_4, a1[i].unk_6);
            sub_0207F0C8(partyMenu, i);
            sub_0207F098(partyMenu, i);
            sub_0207EFC4(partyMenu, i, partyMenu->monsDrawState[i].status);
        } else {
            sub_0207A780(partyMenu, i, a1[i].unk_0, a1[i].unk_2);
        }
    }
    NARC_Delete(narc);
}

static void PartyMenu_DrawPanels_UseEvoStone(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1) {
    NARC *narc = NARC_New(NARC_poketool_icongra_poke_icon, HEAP_ID_PARTY_MENU);
    for (u8 i = 0; i < PARTY_SIZE; ++i) {
        if (sub_02079E38(partyMenu, i) == TRUE) {
            sub_0207A174(partyMenu, i, a1[i].unk_0, a1[i].unk_2, FALSE);
            sub_0207D710(partyMenu, i);
            sub_0207EBE4(partyMenu, i, a1[i].unk_4, a1[i].unk_6, narc);
            sub_0207EF5C(partyMenu, i, a1[i].unk_8, a1[i].unk_A);
            sub_0207F004(partyMenu, i, partyMenu->monsDrawState[i].heldItem);
            sub_0207F064(partyMenu, i, a1[i].unk_4, a1[i].unk_6);
            sub_0207F0C8(partyMenu, i);
            sub_0207F098(partyMenu, i);
            sub_0207EFC4(partyMenu, i, partyMenu->monsDrawState[i].status);
        } else {
            sub_0207A780(partyMenu, i, a1[i].unk_0, a1[i].unk_2);
        }
    }
    NARC_Delete(narc);
}

static void PartyMenu_DrawPanels_UseTMHM(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1) {
    NARC *narc = NARC_New(NARC_poketool_icongra_poke_icon, HEAP_ID_PARTY_MENU);
    for (u8 i = 0; i < PARTY_SIZE; ++i) {
        if (sub_02079E38(partyMenu, i) == TRUE) {
            sub_0207A174(partyMenu, i, a1[i].unk_0, a1[i].unk_2, FALSE);
            PartyMenu_DrawPartyMonsList_UseTMHM(partyMenu, i);
            sub_0207EBE4(partyMenu, i, a1[i].unk_4, a1[i].unk_6, narc);
            sub_0207EF5C(partyMenu, i, a1[i].unk_8, a1[i].unk_A);
            sub_0207F004(partyMenu, i, partyMenu->monsDrawState[i].heldItem);
            sub_0207F064(partyMenu, i, a1[i].unk_4, a1[i].unk_6);
            sub_0207F0C8(partyMenu, i);
            sub_0207F098(partyMenu, i);
            sub_0207EFC4(partyMenu, i, partyMenu->monsDrawState[i].status);
        } else {
            sub_0207A780(partyMenu, i, a1[i].unk_0, a1[i].unk_2);
        }
    }
    NARC_Delete(narc);
}

static void PartyMenu_Setup_SuperContestEntry(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1) {
    NARC *narc = NARC_New(NARC_poketool_icongra_poke_icon, HEAP_ID_PARTY_MENU);
    for (u8 i = 0; i < PARTY_SIZE; ++i) {
        if (sub_02079E38(partyMenu, i) == TRUE) {
            sub_0207A174(partyMenu, i, a1[i].unk_0, a1[i].unk_2, FALSE);
            sub_0207D840(partyMenu, i);
            sub_0207EBE4(partyMenu, i, a1[i].unk_4, a1[i].unk_6, narc);
            sub_0207EF5C(partyMenu, i, a1[i].unk_8, a1[i].unk_A);
            sub_0207F004(partyMenu, i, partyMenu->monsDrawState[i].heldItem);
            sub_0207F064(partyMenu, i, a1[i].unk_4, a1[i].unk_6);
            sub_0207F0C8(partyMenu, i);
            sub_0207F098(partyMenu, i);
            sub_0207EFC4(partyMenu, i, partyMenu->monsDrawState[i].status);
        } else {
            sub_0207A780(partyMenu, i, a1[i].unk_0, a1[i].unk_2);
        }
    }
    NARC_Delete(narc);
}

static void PartyMenu_DrawPanels_FrontierFacilityEntry(PartyMenuStruct *partyMenu, const UnkStruct_0207A22C *a1) {
    NARC *narc = NARC_New(NARC_poketool_icongra_poke_icon, HEAP_ID_PARTY_MENU);
    for (u8 i = 0; i < PARTY_SIZE; ++i) {
        if (sub_02079E38(partyMenu, i) == TRUE) {
            sub_0207A174(partyMenu, i, a1[i].unk_0, a1[i].unk_2, FALSE);
            sub_0207D8A4(partyMenu, i);
            sub_0207D8EC(partyMenu, i);
            sub_0207EBE4(partyMenu, i, a1[i].unk_4, a1[i].unk_6, narc);
            sub_0207EF5C(partyMenu, i, a1[i].unk_8, a1[i].unk_A);
            sub_0207F004(partyMenu, i, partyMenu->monsDrawState[i].heldItem);
            sub_0207F064(partyMenu, i, a1[i].unk_4, a1[i].unk_6);
            sub_0207F0C8(partyMenu, i);
            sub_0207F098(partyMenu, i);
            sub_0207EFC4(partyMenu, i, partyMenu->monsDrawState[i].status);
        } else {
            sub_0207A780(partyMenu, i, a1[i].unk_0, a1[i].unk_2);
        }
    }
    NARC_Delete(narc);
}

static void sub_0207A780(PartyMenuStruct *partyMenu, u8 partySlot, s16 x, s16 y) {
    CopyToBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, x, y, 16, 6, partyMenu->unk_494, 0, 0, 16, 6);
    BgTilemapRectChangePalette(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, x, y, 16, 6, 1);
    sub_0207EFC4(partyMenu, partySlot, PARTY_MON_STATUS_ICON_OK);
    sub_0207F004(partyMenu, partySlot, ITEM_NONE);
    sub_0207F0C8(partyMenu, partySlot);
}

void sub_0207A7F4(PartyMenuStruct *partyMenu, u8 partySlot) {
    Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partySlot);
    u8 paletteSlot;
    if (partyMenu->unk_C63_6 == TRUE && (partySlot == partyMenu->partyMonIndex || partySlot == partyMenu->softboiledDonorSlot)) {
        paletteSlot = 7;
    } else {
        if (partySlot == partyMenu->partyMonIndex) {
            paletteSlot = 4;
        } else {
            paletteSlot = 0;
        }
        if (GetMonData(mon, MON_DATA_HP, NULL) == 0) {
            paletteSlot += 2;
        } else if (sub_0207A880(partyMenu, partySlot) == TRUE) {
            paletteSlot += 1;
        }
    }
    BG_LoadPlttData(GF_BG_LYR_MAIN_2, &partyMenu->unk_554[16 * paletteSlot], 0x10, (partySlot + 3) * 32);
}

static BOOL sub_0207A880(PartyMenuStruct *partyMenu, u8 partySlot) {
    return partyMenu->args->unk_25 == 2 && (partySlot & 1);
}

static void sub_0207A89C(PartyMenuStruct *partyMenu) {
    u8 x;
    u8 y;
    sub_02020A24(partyMenu->unk_948, &x, &y, 0, 0, partyMenu->partyMonIndex, 4);
    Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], sub_0207B5EC(partyMenu->args->unk_25, partyMenu->partyMonIndex));
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], x, y);
}

static const u8 _021012CC[][6] = {
    { 0, 2, 4, 1, 3, 5 },
    { 1, 3, 5, 0, 2, 4 },
    { 4, 2, 0, 5, 3, 1 },
    { 5, 3, 1, 4, 2, 0 },
};

static u8 sub_0207A8FC(PartyMenuStruct *partyMenu) {
    if (PartyMenu_HandleDpadInput(partyMenu) == TRUE) {
        return 1;
    } else {
        return 5;
    }
}

static void PartyMenu_MoveCursorSpriteTo(PartyMenuStruct *partyMenu, int selection, int x, int y) {
    if (selection == PARTY_MON_SELECTION_CANCEL || selection == PARTY_MON_SELECTION_CONFIRM) {
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], FALSE);
    } else {
        Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], sub_0207B5EC(partyMenu->args->unk_25, selection));
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], TRUE);
        Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], x, y);
    }
    u8 oldPartyMonIndex = partyMenu->partyMonIndex;
    partyMenu->partyMonIndex = selection;
    sub_0207B51C(partyMenu, oldPartyMonIndex, FALSE);
    sub_0207B51C(partyMenu, partyMenu->partyMonIndex, TRUE);
}

static void PartyMenu_MoveCursorSpriteTo_WithSfx(PartyMenuStruct *partyMenu, int selection, int x, int y) {
    PartyMenu_MoveCursorSpriteTo(partyMenu, selection, x, y);
    PlaySE(SEQ_SE_DP_SELECT);
}

// Moves cursor sprite in response to dpad input.
// Returns TRUE if the cursor was moved, FALSE otherwise
static BOOL PartyMenu_HandleDpadInput(PartyMenuStruct *partyMenu) {
    u8 newSelection;
    u8 direction;
    u8 x, y;

    // Routine to get the dpad input. If none detected, return FALSE.
    direction = DIR_MAX;

    if (gSystem.newAndRepeatedKeys & PAD_KEY_UP) {
        direction = DIR_NORTH;
    } else if (gSystem.newAndRepeatedKeys & PAD_KEY_DOWN) {
        direction = DIR_SOUTH;
    } else if (gSystem.newAndRepeatedKeys & PAD_KEY_LEFT) {
        direction = DIR_WEST;
    } else if (gSystem.newAndRepeatedKeys & PAD_KEY_RIGHT) {
        direction = DIR_EAST;
    }

    if (direction == DIR_MAX) {
        return FALSE;
    }

    newSelection = partyMenu->partyMonIndex;
    if (newSelection == PARTY_MON_SELECTION_CANCEL) {
        if (direction == DIR_NORTH) {
            newSelection = PartyMenu_GetNewSelectionFromTable(partyMenu, &x, &y, _021012CC[(partyMenu->unk_C66 & 1) + 2]);
        } else {
            newSelection = PartyMenu_GetSelectionInDirection(partyMenu, &x, &y, direction);
        }
    } else if (newSelection == PARTY_MON_SELECTION_CONFIRM) {
        if (partyMenu->args->context != PARTY_MENU_CONTEXT_2 && partyMenu->args->context != PARTY_MENU_CONTEXT_17 && partyMenu->args->context != PARTY_MENU_CONTEXT_23 && partyMenu->args->context != PARTY_MENU_CONTEXT_22 && direction == DIR_NORTH) {
            newSelection = PartyMenu_GetNewSelectionFromTable(partyMenu, &x, &y, _021012CC[(partyMenu->unk_C66 & 1) + 2]);
        } else if (direction == DIR_SOUTH) {
            newSelection = PartyMenu_GetNewSelectionFromTable(partyMenu, &x, &y, _021012CC[partyMenu->unk_C66 & 1]);
        } else {
            newSelection = PartyMenu_GetSelectionInDirection(partyMenu, &x, &y, direction);
        }
    } else {
        newSelection = PartyMenu_GetSelectionInDirection(partyMenu, &x, &y, direction);
    }
    if (newSelection != partyMenu->partyMonIndex && newSelection != 0xFF) {
        PartyMenu_MoveCursorSpriteTo_WithSfx(partyMenu, newSelection, x, y);
        return TRUE;
    }

    return FALSE;
}

static u8 PartyMenu_GetSelectionInDirection(PartyMenuStruct *partyMenu, u8 *px, u8 *py, u8 direction) {
    u8 result = partyMenu->partyMonIndex;
    while (TRUE) {
        result = sub_02020A24(partyMenu->unk_948, px, py, 0, 0, result, direction);
        if (result == 6 || result == 7 || result == 0xFF) {
            break;
        }
        if (PartyMenu_IsMonDrawStateActive(partyMenu, result)) {
            break;
        }
    }
    return result;
}

static u8 PartyMenu_GetNewSelectionFromTable(PartyMenuStruct *partyMenu, u8 *px, u8 *py, const u8 *table) {
    u8 i = 0;
    while (TRUE) {
        if (i == 6) {
            break;
        }
        if (PartyMenu_IsMonDrawStateActive(partyMenu, table[i])) {
            sub_02020A24(partyMenu->unk_948, px, py, 0, 0, table[i], DIR_MAX);
            return table[i];
        }
        ++i;
    }
    sub_02020A24(partyMenu->unk_948, px, py, 0, 0, 0, DIR_MAX);
    return 0;
}

void sub_0207AB84(PartyMenuStruct *partyMenu, u8 partySlot) {
    if (partySlot == 6 || partySlot == 7) {
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], FALSE);
    } else {
        u8 x, y;
        sub_02020A24(partyMenu->unk_948, &x, &y, 0, 0, partyMenu->partyMonIndex, DIR_MAX);
        Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], sub_0207B5EC(partyMenu->args->unk_25, partySlot));
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], TRUE);
        Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], x, y);
    }
    u8 oldSlot = partyMenu->partyMonIndex;
    partyMenu->partyMonIndex = partySlot;
    sub_0207B51C(partyMenu, oldSlot, FALSE);
    sub_0207B51C(partyMenu, partyMenu->partyMonIndex, TRUE);
}

static void sub_0207AC20(PartyMenuStruct *partyMenu) {
    s16 x, y;
    switch (partyMenu->unk_C60) {
    case 0:
        break;
    case 1:
        sub_0207BBFC(partyMenu->unk_C61, &x, &y);
        sub_0207F2A8(partyMenu, x, y);
        ++partyMenu->unk_C60;
        break;
    case 2:
        partyMenu->unk_C60 = 0;
        break;
    }
}

static int sub_0207AC70(PartyMenuStruct *partyMenu, BOOL a1) {
    G2_BlendNone();
    if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CANCEL) {
        return 4;
    } else if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CONFIRM) {
        PlaySE(SEQ_SE_GS_GEARCANCEL);
        if (!partyMenu->cancelDisabled) {
            sub_0207CB3C(partyMenu, a1);
            return 3;
        }
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_3 || partyMenu->args->context == PARTY_MENU_CONTEXT_19) {
        PlaySE(SEQ_SE_DP_SELECT);
        return 0;
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_20 || partyMenu->args->context == PARTY_MENU_CONTEXT_14) {
        if (!partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg) {
            PlaySE(SEQ_SE_DP_SELECT);
            return 0;
        } else {
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return 5;
        }
    } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_15) {
        if (!partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg) {
            PlaySE(SEQ_SE_DP_SELECT);
            sub_0207E068(partyMenu);
            sub_0207F3A4(partyMenu, partyMenu->partyMonIndex);
            sub_0207AFC4(partyMenu);
            return 0;
        } else {
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return 5;
        }
    } else {
        PlaySE(SEQ_SE_DP_SELECT);
        sub_0207E068(partyMenu);
        sub_0207F3A4(partyMenu, partyMenu->partyMonIndex);
        sub_0207AFC4(partyMenu);
        return 0;
    }
    return 5;
}

static int PartyMenu_GetTouchButtonInput(PartyMenuStruct *partyMenu) {
    int idx = 0;
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_2 || partyMenu->args->context == PARTY_MENU_CONTEXT_17 || partyMenu->args->context == PARTY_MENU_CONTEXT_22 || partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
        return TouchscreenHitbox_FindRectAtTouchNew(_02110104);
    } else {
        if (partyMenu->args->unk_25 == 2) {
            idx = 1;
        }
        return TouchscreenHitbox_FindRectAtTouchNew(_02110128[idx]);
    }
}

static u8 sub_0207ADB8(PartyMenuStruct *partyMenu) {
    PartyMenuContextButtonAnimData *r5 = &partyMenu->contextMenuButtonAnim;
    u8 result;

    if (r5->active == TRUE) {
        if (PartyMenu_AnimateContextMenuButtonPress(partyMenu) == FALSE) {
            return r5->followUpState;
        } else {
            return 5;
        }
    }

    u32 selection = PartyMenu_GetTouchButtonInput(partyMenu);
    if (selection != -1) {
        switch (selection) {
        case PARTY_MON_SELECTION_1:
        case PARTY_MON_SELECTION_2:
        case PARTY_MON_SELECTION_3:
        case PARTY_MON_SELECTION_4:
        case PARTY_MON_SELECTION_5:
        case PARTY_MON_SELECTION_6:
            if (selection >= Party_GetCount(partyMenu->args->party)) {
                // UB: hits "return result;" but result was never initialized
                break;
            }
            PartyMenu_MoveCursorSpriteTo(partyMenu, selection, partyMenu->unk_948[selection].unk_0, partyMenu->unk_948[selection].unk_1);
            return sub_0207AC70(partyMenu, TRUE);
        case PARTY_MON_SELECTION_CANCEL:
            if (partyMenu->cancelDisabled) {
                // UB: hits "return result;" but result was never initialized
                break;
            }
            PlaySE(SEQ_SE_GS_GEARCANCEL);
            sub_02079224(partyMenu, FALSE);
            partyMenu->partyMonIndex = PARTY_MON_SELECTION_CONFIRM;
            sub_0207CB3C(partyMenu, TRUE);
            G2_BlendNone();
            PartyMenu_MoveCursorSpriteTo(partyMenu, 7, partyMenu->unk_948[7].unk_0, partyMenu->unk_948[7].unk_1);
            PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, TRUE);
            return 5;
        case PARTY_MON_SELECTION_CONFIRM:
            PartyMenu_MoveCursorSpriteTo_WithSfx(partyMenu, 6, partyMenu->unk_948[6].unk_0, partyMenu->unk_948[6].unk_1);
            PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_8, sub_0207AC70(partyMenu, TRUE), TRUE);
            return 5;
        }
    } else {
        if (gSystem.newKeys & PAD_BUTTON_A) {
            if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CONFIRM) {
                PartyMenu_MoveCursorSpriteTo(partyMenu, partyMenu->partyMonIndex, partyMenu->unk_948[partyMenu->partyMonIndex].unk_0, partyMenu->unk_948[partyMenu->partyMonIndex].unk_1);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9,  sub_0207AC70(partyMenu, FALSE), FALSE);
                return 5;
            } else if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CANCEL) {
                PartyMenu_MoveCursorSpriteTo_WithSfx(partyMenu, partyMenu->partyMonIndex, partyMenu->unk_948[partyMenu->partyMonIndex].unk_0, partyMenu->unk_948[partyMenu->partyMonIndex].unk_1);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_8, sub_0207AC70(partyMenu, FALSE), FALSE);
                return 5;
            } else {
                return sub_0207AC70(partyMenu, FALSE);
            }
        } else if ((gSystem.newKeys & PAD_BUTTON_B) && !partyMenu->cancelDisabled) {
            PlaySE(SEQ_SE_GS_GEARCANCEL);
            sub_02079224(partyMenu, FALSE);
            sub_0207CB3C(partyMenu, FALSE);
            G2_BlendNone();
            if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CONFIRM) {
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, FALSE);
            } else {
                PartyMenu_MoveCursorSpriteTo(partyMenu, 7, partyMenu->unk_948[7].unk_0, partyMenu->unk_948[7].unk_1);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, TRUE);
            }
            return 5;
        } else {
            result = sub_0207A8FC(partyMenu);
        }
    }
    return result;  // possible UB
}

static void sub_0207AFC4(PartyMenuStruct *partyMenu) {
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_32], TRUE);
    u8 *buf = AllocFromHeap(HEAP_ID_PARTY_MENU, 8);
    u8 r2;
    switch (partyMenu->args->context) {
    case PARTY_MENU_CONTEXT_0:
        r2 = sub_0207B0B0(partyMenu, buf);
        break;
    case PARTY_MENU_CONTEXT_2:
    case PARTY_MENU_CONTEXT_17:
        r2 = sub_0207B23C(partyMenu, buf);
        break;
    case PARTY_MENU_CONTEXT_15:
        r2 = sub_0207B1BC(partyMenu, buf);
        break;
    case PARTY_MENU_CONTEXT_18:
        r2 = sub_0207B1C8(partyMenu, buf);
        break;
    case PARTY_MENU_CONTEXT_21:
        r2 = sub_0207B32C(partyMenu, buf);
        break;
    case PARTY_MENU_CONTEXT_22:
        r2 = sub_0207B28C(partyMenu, buf);
        break;
    case PARTY_MENU_CONTEXT_23:
        r2 = sub_0207B2DC(partyMenu, buf);
        break;
    default:
        r2 = sub_0207B200(partyMenu, buf);
        break;
    }
    PartyMenu_OpenContextMenu(partyMenu, buf, r2);
    FreeToHeapExplicit(HEAP_ID_PARTY_MENU, buf);
    sub_0207D1C8(partyMenu);
    sub_0207DAD8(partyMenu, -1, TRUE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
}

static u8 sub_0207B0B0(PartyMenuStruct *partyMenu, u8 *buf) {
    Pokemon *pokemon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
    u16 move;
    u8 r4 = 0;
    u8 i;
    u8 count = 0;
    u8 fieldEffect;

    buf[count] = 1;
    ++count;
    if (!FieldSystem_MapIsBattleTowerMultiPartnerSelectRoom(partyMenu->args->fieldSystem)) {
        if (!partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg) {
            buf[count] = 0;
            ++count;
            if (ItemIdIsMail(partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem) == TRUE) {
                buf[count] = 5;
            } else {
                buf[count] = 2;
            }
            ++count;
            buf[count] = 9;
            ++count;
            for (i = 0; i < MAX_MON_MOVES; ++i) {
                move = GetMonData(pokemon, MON_DATA_MOVE1 + i, NULL);
                if (move == MOVE_NONE) {
                    break;
                }
                fieldEffect = sub_0207BCC0(move);
                if (fieldEffect != 0xFF) {
                    buf[count] = fieldEffect;
                    ++count;
                    PartyMenu_ContextMenuAddFieldMove(partyMenu, move, r4);
                    ++r4;
                }
            }
        } else {
            buf[count] = 0;
            ++count;
            buf[count] = 9;
            ++count;
        }
    } else {
        buf[count] = 9;
        ++count;
    }
    return count;
}

static u8 sub_0207B1BC(PartyMenuStruct *partyMenu, u8 *buf) {
    buf[0] = 14;
    buf[1] = 9;
    return 2;
}

static u8 sub_0207B1C8(PartyMenuStruct *partyMenu, u8 *buf) {
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg == FALSE) {
        buf[0] = 8;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    } else {
        buf[0] = 1;
        buf[1] = 9;
        return 2;
    }
}

static u8 sub_0207B200(PartyMenuStruct *partyMenu, u8 *buf) {
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].isContestCompatible == TRUE) {
        buf[0] = 13;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    } else {
        buf[0] = 1;
        buf[1] = 9;
        return 2;
    }
}

static u8 sub_0207B23C(PartyMenuStruct *partyMenu, u8 *buf) {
    switch (sub_0207B364(partyMenu, partyMenu->partyMonIndex)) {
    case 0:
        buf[0] = 1;
        buf[1] = 9;
        return 2;
    case 1:
        buf[0] = 11;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    case 2:
        buf[0] = 12;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    }

    return 0;
}

static u8 sub_0207B28C(PartyMenuStruct *partyMenu, u8 *buf) {
    switch (sub_0207B418(partyMenu, partyMenu->partyMonIndex)) {
    case 0:
        buf[0] = 1;
        buf[1] = 9;
        return 2;
    case 1:
        buf[0] = 11;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    case 2:
        buf[0] = 12;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    }

    return 0;
}

static u8 sub_0207B2DC(PartyMenuStruct *partyMenu, u8 *buf) {
    switch (sub_0207B4A0(partyMenu, partyMenu->partyMonIndex)) {
    case 0:
        buf[0] = 1;
        buf[1] = 9;
        return 2;
    case 1:
        buf[0] = 11;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    case 2:
        buf[0] = 12;
        buf[1] = 1;
        buf[2] = 9;
        return 3;
    }

    return 0;
}

static u8 sub_0207B32C(PartyMenuStruct *partyMenu, u8 *buf) {
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg == TRUE) {
        buf[0] = 1;
        buf[1] = 15;
        buf[2] = 9;
        return 3;
    } else {
        buf[0] = 1;
        buf[1] = 9;
        return 2;
    }
}

u8 sub_0207B364(PartyMenuStruct *partyMenu, u8 selection) {
    u8 i;

    if (partyMenu->args->unk_14 != NULL) {
        Pokemon *pokemon = Party_GetMonByIndex(partyMenu->args->party, selection);
        if (sub_0207496C(partyMenu->args->unk_14, pokemon, partyMenu->pokedex) == FALSE) {
            return 0;
        }
    }
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_17) {
        if (IsPokemonBannedFromBattleFrontier(partyMenu->monsDrawState[selection].species, partyMenu->monsDrawState[selection].form) == TRUE) {
            return 0;
        }
    }
    for (i = 0; i < partyMenu->args->unk_36_4; ++i) {
        if (partyMenu->args->selectedOrder[i] == selection + 1) {
            return 2;
        }
    }
    if (partyMenu->monsDrawState[selection].isEgg == TRUE || partyMenu->monsDrawState[selection].level > partyMenu->args->unk_37) {
        return 0;
    }
    return 1;
}

u8 sub_0207B418(PartyMenuStruct *partyMenu, u8 selection) {
    u8 i;

    if (partyMenu->args->context == PARTY_MENU_CONTEXT_22) {
        if (IsPokemonBannedFromBattleFrontier(partyMenu->monsDrawState[selection].species, partyMenu->monsDrawState[selection].form) == TRUE) {
            return 0;
        }
    }
    for (i = 0; i < partyMenu->args->unk_36_4; ++i) {
        if (partyMenu->args->selectedOrder[i] == selection + 1) {
            return 2;
        }
    }
    if (partyMenu->monsDrawState[selection].isEgg == TRUE || partyMenu->monsDrawState[selection].level < partyMenu->args->unk_37) {
        return 0;
    }
    return 1;
}

u8 sub_0207B4A0(PartyMenuStruct *partyMenu, u8 selection) {
    u8 i;

    if (partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
        if (IsPokemonBannedFromBattleFrontier(partyMenu->monsDrawState[selection].species, partyMenu->monsDrawState[selection].form) == TRUE) {
            return 0;
        }
    }
    for (i = 0; i < partyMenu->args->unk_36_4; ++i) {
        if (partyMenu->args->selectedOrder[i] == selection + 1) {
            return 2;
        }
    }
    if (partyMenu->monsDrawState[selection].isEgg == TRUE) {
        return 0;
    }
    return 1;
}

static void sub_0207B51C(PartyMenuStruct *partyMenu, u8 selection, BOOL active) {
    u8 animSeqNo;
    if (selection == PARTY_MON_SELECTION_CANCEL) {
        animSeqNo = Get2dSpriteCurrentAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_8]);
        if (active == FALSE) {
            animSeqNo &= 2;
        } else {
            animSeqNo = (animSeqNo & 2) + 1;
        }
        Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_8], animSeqNo);
    } else if (selection == PARTY_MON_SELECTION_CONFIRM) {
        animSeqNo = Get2dSpriteCurrentAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9]);
        if (active == FALSE) {
            animSeqNo &= 2;
        } else {
            animSeqNo = (animSeqNo & 2) + 1;
        }
        Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], animSeqNo);
    } else {
        if (!active) {
            partyMenu->monsDrawState[selection].unk_16 -= 2;
            partyMenu->monsDrawState[selection].unk_18 -= 2;
            Set2dSpriteAnimSeqNo(partyMenu->sprites[selection + PARTY_MENU_SPRITE_ID_0], 0);
        } else {
            partyMenu->monsDrawState[selection].unk_16 += 2;
            partyMenu->monsDrawState[selection].unk_18 += 2;
            Set2dSpriteAnimSeqNo(partyMenu->sprites[selection + PARTY_MENU_SPRITE_ID_0], 1);
        }
        sub_0207A7F4(partyMenu, selection);
    }
}

int sub_0207B5EC(u8 a0, u8 partySlot) {
    return partySlot == 0 || (a0 != 0 && partySlot == 1);
}

static u8 sub_0207B600(PartyMenuStruct *partyMenu) {
    u8 result;
    PartyMenuContextButtonAnimData *r5 = &partyMenu->contextMenuButtonAnim;

    if (r5->active == TRUE) {
        if (PartyMenu_AnimateContextMenuButtonPress(partyMenu) == FALSE) {
            if (partyMenu->partyMonIndex != PARTY_MON_SELECTION_CONFIRM) {
                Sprite_SetAnimCtrlCurrentFrame(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], 0);
                Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], 0);
            }
            return r5->followUpState;
        } else {
            return 5;
        }
    }

    u32 selection = PartyMenu_GetTouchButtonInput(partyMenu);
    if (selection != -1) {
        switch (selection) {
        case PARTY_MON_SELECTION_1:
        case PARTY_MON_SELECTION_2:
        case PARTY_MON_SELECTION_3:
        case PARTY_MON_SELECTION_4:
        case PARTY_MON_SELECTION_5:
        case PARTY_MON_SELECTION_6: {
            if (selection >= Party_GetCount(partyMenu->args->party)) {
                // UB: hits "return result;" but result was never initialized
                break;
            }
            u32 oldSelection = partyMenu->partyMonIndex;
            partyMenu->partyMonIndex = selection;
            PlaySE(SEQ_SE_DP_SELECT);
            if (partyMenu->partyMonIndex == partyMenu->softboiledDonorSlot) {
                if (oldSelection != partyMenu->partyMonIndex) {
                    sub_0207B51C(partyMenu, oldSelection, FALSE);
                    sub_0207B51C(partyMenu, partyMenu->partyMonIndex, TRUE);
                    PartyMenu_MoveCursorSpriteTo(partyMenu, selection, partyMenu->unk_948[selection].unk_0, partyMenu->unk_948[selection].unk_1);
                }
                sub_0207FBC8(partyMenu);
                return 3;
            } else {
                if (oldSelection != partyMenu->partyMonIndex && oldSelection != partyMenu->softboiledDonorSlot) {
                    sub_0207B51C(partyMenu, oldSelection, FALSE);
                }
                if (oldSelection == partyMenu->softboiledDonorSlot) {
                    sub_0207B51C(partyMenu, partyMenu->softboiledDonorSlot, FALSE);
                }
                if (oldSelection != partyMenu->partyMonIndex) {
                    sub_0207B51C(partyMenu, partyMenu->partyMonIndex, TRUE);
                }
                PartyMenu_MoveCursorSpriteTo(partyMenu, selection, partyMenu->unk_948[selection].unk_0, partyMenu->unk_948[selection].unk_1);
                sub_0207FC1C(partyMenu);
                return 0;
            }
            break;
        }
        case PARTY_MON_SELECTION_CANCEL:
            PlaySE(SEQ_SE_GS_GEARCANCEL);
            sub_0207FBC8(partyMenu);
            PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, FALSE);
            return 5;
        }
    } else {
        if (gSystem.newKeys & PAD_BUTTON_A) {
            if (partyMenu->partyMonIndex >= 7) {
                PlaySE(SEQ_SE_GS_GEARCANCEL);
                sub_0207FBC8(partyMenu);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, FALSE);
                return 5;
            } else if (partyMenu->partyMonIndex == partyMenu->softboiledDonorSlot) {
                PlaySE(SEQ_SE_DP_SELECT);
                sub_0207FBC8(partyMenu);
                return 3;
            } else {
                PlaySE(SEQ_SE_DP_SELECT);
                sub_0207FC1C(partyMenu);
                return 0;
            }
        } else if (gSystem.newKeys & PAD_BUTTON_B) {
            PlaySE(SEQ_SE_GS_GEARCANCEL);
            sub_0207FBC8(partyMenu);
            return 3;
        } else {
            result = sub_0207A8FC(partyMenu);
        }
    }

    return result;  // UB rist
}

static int sub_0207B7E0(PartyMenuStruct *partyMenu) {
    for (u8 i = 0; i < partyMenu->args->unk_36_0; ++i) {
        if (partyMenu->args->selectedOrder[i] == 0) {
            switch (partyMenu->args->unk_36_4) {
            case 2:
                sub_0207DAEC(partyMenu, msg_0300_00103, TRUE);
                break;
            case 3:
                sub_0207DAEC(partyMenu, msg_0300_00108, TRUE);
                break;
            case 4:
                sub_0207DAEC(partyMenu, msg_0300_00109, TRUE);
                break;
            case 5:
                sub_0207DAEC(partyMenu, msg_0300_00110, TRUE);
                break;
            case 6:
                sub_0207DAEC(partyMenu, msg_0300_00111, TRUE);
                break;
            case 0:
            case 1:
            default:
                sub_0207DAEC(partyMenu, msg_0300_00030, TRUE);
                break;
            }
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
    }

    if (partyMenu->args->unk_14 != NULL) {
        switch (sub_02074A6C(partyMenu->args->unk_14, partyMenu->args->party, partyMenu->pokedex, partyMenu->args->selectedOrder)) {
        case 0:
            break;
        case 1: {
            String *string = NewString_ReadMsgData(partyMenu->msgData, msg_0300_00167);
            BufferIntegerAsString(partyMenu->msgFormat, 0, sub_020290FC(partyMenu->args->unk_14, 3), 3, PRINTING_MODE_LEFT_ALIGN, TRUE);
            StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, string);
            String_Delete(string);
            sub_0207DAEC(partyMenu, -1, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
        case 2:
            sub_0207DAEC(partyMenu, msg_0300_00165, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        case 3:
            sub_0207DAEC(partyMenu, msg_0300_00166, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        case 4:
            break;
        case 5:
            break;
        case 6:
            sub_0207DAEC(partyMenu, msg_0300_00168, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        case 7:
            break;
        case 8:
            sub_0207DAEC(partyMenu, msg_0300_00191, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
    }

    if (partyMenu->args->context == PARTY_MENU_CONTEXT_17) {
        switch (sub_0207BA78(partyMenu)) {
        case 0:
            break;
        case 1:
            sub_0207DAEC(partyMenu, msg_0300_00165, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        case 2:
            sub_0207DAEC(partyMenu, msg_0300_00166, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
    }

    if (partyMenu->args->context == PARTY_MENU_CONTEXT_22) {
        switch (sub_0207BB14(partyMenu)) {
        case 0:
            break;
        case 1:
            sub_0207DAEC(partyMenu, msg_0300_00187, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
    }

    if (partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
        switch (sub_0207BB88(partyMenu)) {
        case 0:
            break;
        case 1:
            sub_0207DAEC(partyMenu, msg_0300_00165, TRUE);
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
            PlaySE(SEQ_SE_DP_CUSTOM06);
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
    }

    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
    return PARTY_MENU_STATE_BEGIN_EXIT;
}

static u8 sub_0207BA78(PartyMenuStruct *partyMenu) {
    for (u8 i = 0; i < PARTY_SIZE - 1; ++i) {
        if (partyMenu->args->selectedOrder[i] == 0) {
            break;
        }
        for (u8 j = i + 1; j < PARTY_SIZE; ++j) {
            if (partyMenu->args->selectedOrder[j] == 0) {
                break;
            }
            if (partyMenu->monsDrawState[partyMenu->args->selectedOrder[i] - 1].species == partyMenu->monsDrawState[partyMenu->args->selectedOrder[j] - 1].species) {
                return 1;
            }
            if (partyMenu->monsDrawState[partyMenu->args->selectedOrder[i] - 1].heldItem != ITEM_NONE && partyMenu->monsDrawState[partyMenu->args->selectedOrder[i] - 1].heldItem == partyMenu->monsDrawState[partyMenu->args->selectedOrder[j] - 1].heldItem) {
                return 2;
            }
        }
    }

    return 0;
}

static u8 sub_0207BB14(PartyMenuStruct *partyMenu) {
    for (u8 i = 0; i < PARTY_SIZE - 1; ++i) {
        if (partyMenu->args->selectedOrder[i] == 0) {
            break;
        }
        for (u8 j = i + 1; j < PARTY_SIZE; ++j) {
            if (partyMenu->args->selectedOrder[j] == 0) {
                break;
            }
            if (partyMenu->monsDrawState[partyMenu->args->selectedOrder[i] - 1].species != partyMenu->monsDrawState[partyMenu->args->selectedOrder[j] - 1].species) {
                return 1;
            }
        }
    }

    return 0;
}

static u8 sub_0207BB88(PartyMenuStruct *partyMenu) {
    for (u8 i = 0; i < PARTY_SIZE - 1; ++i) {
        if (partyMenu->args->selectedOrder[i] == 0) {
            break;
        }
        for (u8 j = i + 1; j < PARTY_SIZE; ++j) {
            if (partyMenu->args->selectedOrder[j] == 0) {
                break;
            }
            if (partyMenu->monsDrawState[partyMenu->args->selectedOrder[i] - 1].species == partyMenu->monsDrawState[partyMenu->args->selectedOrder[j] - 1].species) {
                return 1;
            }
        }
    }

    return 0;
}

static const u8 _021012B0[][2] = {
    {  1,  3 },
    { 26,  3 },
    {  1, 10 },
    { 26, 10 },
    {  1, 17 },
    { 26, 17 },
};

static void sub_0207BBFC(u8 a0, s16 *px, s16 *py) {
    *px = _021012B0[a0][0] * 8 + 20;
    *py = _021012B0[a0][1] * 8 + 20;
}

static BOOL PartyMenu_Subtask_HandleContextMenuInput(PartyMenuStruct *partyMenu, int *pState) {
    u32 func = PartyMenu_HandleInput_ContextMenu(partyMenu, partyMenu->contextMenuCursor);
    switch (func) {
    case LIST_CANCEL:
        sub_02079224(partyMenu, FALSE);
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
        sub_0207CB20(partyMenu);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        if (partyMenu->args->context == PARTY_MENU_CONTEXT_2 || partyMenu->args->context == PARTY_MENU_CONTEXT_17 || partyMenu->args->context == PARTY_MENU_CONTEXT_22 || partyMenu->args->context == PARTY_MENU_CONTEXT_23) {
            sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
        } else if (partyMenu->args->context == PARTY_MENU_CONTEXT_21) {
            sub_0207DAC4(partyMenu, msg_0300_00184, TRUE);
        } else {
            sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
        }
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
        return TRUE;
    case LIST_NOTHING_CHOSEN:
        break;
    default:
        ((PartyMenuStruct_SubC90_UnkFunc)func)(partyMenu, (int *)pState);
        break;
    }

    return FALSE;
}

static u8 sub_0207BCC0(u16 move) {
    for (u8 i = 0; i < 16; ++i) {
        if (move == sFieldMoves[i]) {
            return i + 16;
        }
    }
    return 0xFF;
}

static int PartyMenu_SoftboiledTryTargetCheck(PartyMenuStruct *partyMenu) {
    switch (PartyMenu_SoftboiledTargetCheck(partyMenu)) {
    case 0:
        PlaySE(SEQ_SE_DP_KAIFUKU);
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
        if (partyMenu->monsDrawState[partyMenu->partyMonIndex].maxHp - partyMenu->monsDrawState[partyMenu->partyMonIndex].hp < partyMenu->unk_C68[0]) {
            partyMenu->unk_C68[0] = partyMenu->monsDrawState[partyMenu->partyMonIndex].maxHp - partyMenu->monsDrawState[partyMenu->partyMonIndex].hp;
        }
        partyMenu->unk_C68[1] = 2;
        partyMenu->unk_C68[2] = 0;
        return PARTY_MENU_STATE_SOFTBOILED;
    case 1:
        PlaySE(SEQ_SE_DP_SELECT);
        partyMenu->unk_C68[1] = 1;
        return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
    case 2:
        PlaySE(SEQ_SE_DP_CUSTOM06);
        return PARTY_MENU_STATE_SOFTBOILED;
    }

    return PARTY_MENU_STATE_SOFTBOILED;
}

static int PartyMenu_Subtask_Softboiled(PartyMenuStruct *partyMenu) {
    PartyMenuContextButtonAnimData *r5 = &partyMenu->contextMenuButtonAnim;
    if (r5->active == TRUE) {
        if (PartyMenu_AnimateContextMenuButtonPress(partyMenu) == FALSE) {
            if (partyMenu->partyMonIndex != PARTY_MON_SELECTION_CONFIRM) {
                Sprite_SetAnimCtrlCurrentFrame(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], 0);
                Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_9], 0);
            }
            return r5->followUpState;
        } else {
            return PARTY_MENU_STATE_SOFTBOILED;
        }
    }

    switch (partyMenu->unk_C68[1]) {
    case 0: {
        u32 selection = PartyMenu_GetTouchButtonInput(partyMenu);
        if (selection != -1) {
            switch (selection) {
            case PARTY_MON_SELECTION_1:
            case PARTY_MON_SELECTION_2:
            case PARTY_MON_SELECTION_3:
            case PARTY_MON_SELECTION_4:
            case PARTY_MON_SELECTION_5:
            case PARTY_MON_SELECTION_6:
                if (selection >= Party_GetCount(partyMenu->args->party)) {
                    break;
                }
                PartyMenu_MoveCursorSpriteTo(partyMenu, selection, partyMenu->unk_948[selection].unk_0, partyMenu->unk_948[selection].unk_1);
                return PartyMenu_SoftboiledTryTargetCheck(partyMenu);
            case PARTY_MON_SELECTION_CANCEL:
                PlaySE(SEQ_SE_GS_GEARCANCEL);
                sub_0207FBC8(partyMenu);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_1, FALSE);
                return PARTY_MENU_STATE_SOFTBOILED;
            }
        } else {
            if (gSystem.newKeys & PAD_BUTTON_A) {
                if (partyMenu->partyMonIndex >= 6) {
                    PlaySE(SEQ_SE_GS_GEARCANCEL);
                    sub_0207FBC8(partyMenu);
                    PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_1, FALSE);
                    return PARTY_MENU_STATE_SOFTBOILED;
                } else {
                    return PartyMenu_SoftboiledTryTargetCheck(partyMenu);
                }
            } else if (gSystem.newKeys & PAD_BUTTON_B) {
                PlaySE(SEQ_SE_GS_GEARCANCEL);
                sub_0207FBC8(partyMenu);
                return PARTY_MENU_STATE_1;
            } else {
                sub_0207A8FC(partyMenu);
            }
        }
        break;
    }
    case 1:
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
        sub_0207DAC4(partyMenu, msg_0300_00037, TRUE);
        partyMenu->unk_C68[1] = 0;
        break;
    case 2:
        if (PartyMenu_SoftboiledHPTransferStep(partyMenu, partyMenu->softboiledDonorSlot, -1) == TRUE) {
            PlaySE(SEQ_SE_DP_KAIFUKU);
            partyMenu->unk_C68[1] = 3;
            partyMenu->unk_C68[2] = 0;
        }
        break;
    case 3:
        if (PartyMenu_SoftboiledHPTransferStep(partyMenu, partyMenu->partyMonIndex, 1) == TRUE) {
            Pokemon *pokemon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
            String *string = NewString_ReadMsgData(partyMenu->msgData, msg_0300_00065);
            BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(pokemon));
            BufferIntegerAsString(partyMenu->msgFormat, 1, partyMenu->unk_C68[2], 3, PRINTING_MODE_LEFT_ALIGN, TRUE);
            StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, string);
            String_Delete(string);
            sub_0207DAEC(partyMenu, -1, TRUE);
            partyMenu->unk_C68[1] = 4;
            partyMenu->afterTextPrinterState = PARTY_MENU_STATE_SOFTBOILED;
            return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
        }
        break;
    case 4:
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
        sub_0207FBC8(partyMenu);
        return PARTY_MENU_STATE_1;
    }

    return PARTY_MENU_STATE_SOFTBOILED;
}

static u8 PartyMenu_SoftboiledTargetCheck(PartyMenuStruct *partyMenu) {
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg) {
        return 2;
    }
    if (partyMenu->partyMonIndex == partyMenu->softboiledDonorSlot || partyMenu->monsDrawState[partyMenu->partyMonIndex].hp == 0 || partyMenu->monsDrawState[partyMenu->partyMonIndex].hp == partyMenu->monsDrawState[partyMenu->partyMonIndex].maxHp) {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
        sub_0207DAEC(partyMenu, msg_0300_00120, TRUE);
        partyMenu->unk_C68[1] = 1;
        partyMenu->afterTextPrinterState = PARTY_MENU_STATE_SOFTBOILED;
        return 1;
    }
    return 0;
}

static BOOL PartyMenu_SoftboiledHPTransferStep(PartyMenuStruct *partyMenu, u8 partySlot, s8 delta) {
    partyMenu->monsDrawState[partySlot].hp += delta;
    ++partyMenu->unk_C68[2];
    PartyMenu_ClearMonHpTextWindow(partyMenu, partySlot);
    FillWindowPixelBuffer(&partyMenu->windows[partySlot * 5 + 3], 0);
    PartyMenu_PrintMonCurHpOnWindow(partyMenu, partySlot);
    PartyMenu_DrawMonHpBarOnWindow(partyMenu, partySlot);
    if (partyMenu->unk_C68[0] == partyMenu->unk_C68[2] || partyMenu->monsDrawState[partySlot].hp == partyMenu->monsDrawState[partySlot].maxHp) {
        Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partySlot);
        u32 hp = partyMenu->monsDrawState[partySlot].hp;
        SetMonData(mon, MON_DATA_HP, &hp);
        return TRUE;
    }

    return FALSE;
}

static u8 sub_0207C0DC(PartyMenuStruct *partyMenu) {
    PartyMenuContextButtonAnimData *r5 = &partyMenu->contextMenuButtonAnim;
    if (r5->active == TRUE) {
        if (PartyMenu_AnimateContextMenuButtonPress(partyMenu) == FALSE) {
            return r5->followUpState;
        } else {
            return 5;
        }
    }

    u32 selection = PartyMenu_GetTouchButtonInput(partyMenu);
    if (selection != -1) {
        switch (selection) {
        case PARTY_MON_SELECTION_1:
        case PARTY_MON_SELECTION_2:
        case PARTY_MON_SELECTION_3:
        case PARTY_MON_SELECTION_4:
        case PARTY_MON_SELECTION_5:
        case PARTY_MON_SELECTION_6:
            if (selection < Party_GetCount(partyMenu->args->party)) {
                PartyMenu_MoveCursorSpriteTo(partyMenu, selection, partyMenu->unk_948[selection].unk_0, partyMenu->unk_948[selection].unk_1);
                partyMenu->partyMonIndex = selection;
                if (!partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg) {
                    PlaySE(SEQ_SE_DP_SELECT);
                    return 0;
                } else {
                    PlaySE(SEQ_SE_DP_CUSTOM06);
                    return 5;
                }
            }
            break;
        case PARTY_MON_SELECTION_CANCEL:
            if (!partyMenu->cancelDisabled) {
                PlaySE(SEQ_SE_GS_GEARCANCEL);
                PartyMenu_MoveCursorSpriteTo(partyMenu, 7, partyMenu->unk_948[7].unk_0, partyMenu->unk_948[7].unk_1);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, TRUE);
                return 5;
            }
        }
    } else if (gSystem.newKeys & PAD_BUTTON_A) {
        if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CONFIRM) {
            if (!partyMenu->cancelDisabled) {
                PlaySE(SEQ_SE_GS_GEARCANCEL);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, FALSE);
                return 5;
            }
        } else {
            if (!partyMenu->monsDrawState[partyMenu->partyMonIndex].isEgg) {
                PlaySE(SEQ_SE_DP_SELECT);
                return 0;
            } else {
                PlaySE(SEQ_SE_DP_CUSTOM06);
            }
        }
        return 5;
    }
    if (gSystem.newKeys & PAD_BUTTON_B) {
        if (!partyMenu->cancelDisabled) {
            PlaySE(SEQ_SE_GS_GEARCANCEL);
            if (partyMenu->partyMonIndex == PARTY_MON_SELECTION_CONFIRM) {
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, FALSE);
            } else {
                PartyMenu_MoveCursorSpriteTo(partyMenu, 7, partyMenu->unk_948[7].unk_0, partyMenu->unk_948[7].unk_1);
                PartyMenu_StartContextMenuButtonAnim(partyMenu, PARTY_MENU_SPRITE_ID_9, PARTY_MENU_STATE_3, TRUE);
            }
            return 5;
        } else {
            return 5;
        }
    }

    return sub_0207A8FC(partyMenu);
}

static int sub_0207C288(PartyMenuStruct *partyMenu) {
    ItemData *itemData = LoadItemDataOrGfx(partyMenu->args->itemId, ITEMNARC_PARAM, HEAP_ID_PARTY_MENU);

    if (partyMenu->args->itemId == ITEM_GRACIDEA && Mon_CanUseGracidea(Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex)) == TRUE) {
        partyMenu->args->species = SHAYMIN_SKY;  // SPECIES_BULBASAUR
        FreeToHeap(itemData);
        PartyMenu_FormChangeScene_Begin(partyMenu);
        return PARTY_MENU_STATE_FORM_CHANGE_ANIM;
    }

    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_UP) || GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_MAX)) {
        FreeToHeap(itemData);
        sub_02082654(partyMenu, 0);
        return PARTY_MENU_STATE_SELECT_MOVE;
    }
    if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE) && !GetItemAttr_PreloadedItemData(itemData, ITEMATTR_PP_RESTORE_ALL)) {
        FreeToHeap(itemData);
        sub_02082654(partyMenu, 1);
        return PARTY_MENU_STATE_SELECT_MOVE;
    }

    if (CanUseItemOnMonInParty(partyMenu->args->party, partyMenu->args->itemId, partyMenu->partyMonIndex, 0, HEAP_ID_PARTY_MENU) == TRUE) {
        Bag_TakeItem(partyMenu->args->bag, partyMenu->args->itemId, 1, HEAP_ID_PARTY_MENU);
        if (GetItemAttr_PreloadedItemData(itemData, ITEMATTR_EVOLVE)) {
            Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
            partyMenu->args->species = GetMonEvolution(NULL, mon, EVOCTX_ITEM_USE, partyMenu->args->itemId, &partyMenu->args->unk_40);
            partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_EVO_ITEM_USE;
            FreeToHeap(itemData);
            return PARTY_MENU_STATE_BEGIN_EXIT;
        } else {
            sub_020812E8(partyMenu);
        }
    } else {
        sub_0207DAEC(partyMenu, msg_0300_00102, TRUE);
        partyMenu->partyMonIndex = PARTY_MON_SELECTION_CONFIRM;
        partyMenu->unk_C54 = sub_02081378;
    }
    FreeToHeap(itemData);
    return PARTY_MENU_STATE_5;
}

static u8 sub_0207C3D0(PartyMenuStruct *partyMenu) {
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem == ITEM_NONE) {
        return 0;
    } else if (ItemIdIsMail(partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem) == TRUE) {
        return 2;
    } else {
        return 1;
    }
}

static int sub_0207C400(PartyMenuStruct *partyMenu) {
    int result = -1;
    Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
    FieldSystem *fieldSystem = partyMenu->args->fieldSystem;

    if (partyMenu->args->itemId == ITEM_GRISEOUS_ORB) {
        if (GetMonData(mon, MON_DATA_SPECIES, NULL) != SPECIES_GIRATINA) {
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00189, partyMenu->unformattedStrBuf);
            BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(mon));
            BufferItemNameWithIndefArticle(partyMenu->msgFormat, 1, partyMenu->args->itemId);
            StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
            result = PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
        } else if (fieldSystem != NULL) {
            if (fieldSystem->location->mapId == MAP_UNION) {
                ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00190, partyMenu->unformattedStrBuf);
                BufferItemName(partyMenu->msgFormat, 0, partyMenu->args->itemId);
                StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
                result = PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
            }
        }
    }

    if (result == -1) {
        switch (sub_0207C3D0(partyMenu)) {
        case 0:
            if (ItemIdIsMail(partyMenu->args->itemId) == TRUE) {
                partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_6;
                return PARTY_MENU_STATE_BEGIN_EXIT;
            } else {
                s32 sp0;
                result = sub_0207C5D4(partyMenu, mon, &sp0);
                ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00107, partyMenu->unformattedStrBuf);
                BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(mon));
                BufferItemName(partyMenu->msgFormat, 1, partyMenu->args->itemId);
                StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
            }
            break;
        case 1:
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00079, partyMenu->unformattedStrBuf);
            BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(mon));
            BufferItemNameWithIndefArticle(partyMenu->msgFormat, 1, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
            StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
            result = PARTY_MENU_STATE_PRINT_ASK_SWITCH_ITEMS;
            break;
        case 2:
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00078, partyMenu->formattedStrBuf);
            result = PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
            break;
        }
    }

    DrawFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE, 0x02A, 15);
    FillWindowPixelBuffer(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], 15);
    sub_0207DB30(partyMenu);
    return result;
}

static int sub_0207C5D4(PartyMenuStruct *partyMenu, Pokemon *mon, s32 *transformResult) {
    u32 itemToBeHeld = partyMenu->args->itemId;
    Bag_TakeItem(partyMenu->args->bag, partyMenu->args->itemId, 1, HEAP_ID_PARTY_MENU);
    SetMonData(mon, MON_DATA_HELD_ITEM, &itemToBeHeld);
    Pokemon_UpdateArceusForm(mon);
    *transformResult = Mon_UpdateGiratinaForm(mon);
    partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem = partyMenu->args->itemId;
    sub_0207F004(partyMenu, partyMenu->partyMonIndex, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
    if (itemToBeHeld == ITEM_GRISEOUS_ORB && *transformResult != -1) {
        return PARTY_MENU_STATE_PRINT_TAKE_GRISEOUS_ORB_MESSAGE;
    } else {
        return PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
    }
}

static void PartyMenu_SwapMonHeldItem(PartyMenuStruct *partyMenu, Pokemon *mon, u32 oldItemId, u32 newItemId) {
    Bag_AddItem(partyMenu->args->bag, oldItemId, 1, HEAP_ID_PARTY_MENU);
    SetMonData(mon, MON_DATA_HELD_ITEM, &newItemId);
    Pokemon_UpdateArceusForm(mon);
    Mon_UpdateGiratinaForm(mon);
    partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem = newItemId;
    sub_0207F004(partyMenu, partyMenu->partyMonIndex, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
}

static int PartyMenu_Subtask_PrintItemSwapMessage(PartyMenuStruct *partyMenu) {
    if (TextPrinterCheckActive(partyMenu->textPrinterId) == FALSE) {
        return sub_0207C8B4(partyMenu);
    } else {
        return PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
    }
}

static int PartyMenu_Subtask_PrintGriseousOrbMessage(PartyMenuStruct *partyMenu) {
    if (TextPrinterCheckActive(partyMenu->textPrinterId) == FALSE) {
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
        PartyMenu_FormChangeScene_Begin(partyMenu);
        return PARTY_MENU_STATE_WAIT_FORM_CHANGE;
    } else {
        return PARTY_MENU_STATE_PRINT_TAKE_GRISEOUS_ORB_MESSAGE;
    }
}

static int PartyMenu_Subtask_WaitFormChange(PartyMenuStruct *partyMenu) {
    if (PartyMenu_AnimateIconFormChange(partyMenu) == TRUE) {
        PartyMenu_FormChangeScene_End(partyMenu);
        return PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
    } else {
        return PARTY_MENU_STATE_WAIT_FORM_CHANGE;
    }
}

static int PartyMenu_Subtask_PrintAskSwitchItems(PartyMenuStruct *partyMenu) {
    if (TextPrinterCheckActive(partyMenu->textPrinterId) == FALSE) {
        sub_0207DBCC(partyMenu);
        return PARTY_MENU_STATE_YESNO_ASK_SWITCH_ITEMS;
    } else {
        return PARTY_MENU_STATE_PRINT_ASK_SWITCH_ITEMS;
    }
}

static int PartyMenu_Subtask_SwitchItemsHandleYesNoInput(PartyMenuStruct *partyMenu) {
    int result;
    switch (YesNoPrompt_HandleInput(partyMenu->yesNoPrompt)) {
    case YESNORESPONSE_YES: {
        YesNoPrompt_Destroy(partyMenu->yesNoPrompt);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
        int newItemId = partyMenu->args->itemId;
        int oldItemId = partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem;
        s32 giratinaResult;
        result = sub_0207C5D4(partyMenu, mon, &giratinaResult);
        if (!Bag_AddItem(partyMenu->args->bag, oldItemId, 1, HEAP_ID_PARTY_MENU)) {
            PartyMenu_SwapMonHeldItem(partyMenu, mon, newItemId, oldItemId);
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00084, partyMenu->formattedStrBuf);
            result = PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
        } else if (ItemIdIsMail(partyMenu->args->itemId) == TRUE) {
            Bag_TakeItem(partyMenu->args->bag, oldItemId, 1, HEAP_ID_PARTY_MENU);
            PartyMenu_SwapMonHeldItem(partyMenu, mon, newItemId, oldItemId);
            partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_6;
            return PARTY_MENU_STATE_BEGIN_EXIT;
        } else {
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00085, partyMenu->unformattedStrBuf);
            BufferItemName(partyMenu->msgFormat, 1, oldItemId);
            BufferItemName(partyMenu->msgFormat, 2, newItemId);
            StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
            if (newItemId != ITEM_GRISEOUS_ORB && oldItemId == ITEM_GRISEOUS_ORB && giratinaResult != -1) {
                result = PARTY_MENU_STATE_PRINT_TAKE_GRISEOUS_ORB_MESSAGE;
            } else if (newItemId == ITEM_GRISEOUS_ORB && oldItemId == ITEM_GRISEOUS_ORB) {
                result = PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE;
            }
        }
        FillWindowPixelBuffer(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], 15);
        sub_0207DB30(partyMenu);
        return result;
    }
    case YESNORESPONSE_NO:
        YesNoPrompt_Destroy(partyMenu->yesNoPrompt);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        return sub_0207C8B4(partyMenu);
    }

    return PARTY_MENU_STATE_YESNO_ASK_SWITCH_ITEMS;
}

static int sub_0207C8B4(PartyMenuStruct *partyMenu) {
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_10) {
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
        sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
        partyMenu->args->context = PARTY_MENU_CONTEXT_0;
        return PARTY_MENU_STATE_1;
    } else {
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_10;
        return PARTY_MENU_STATE_BEGIN_EXIT;
    }
}

static int sub_0207C908(PartyMenuStruct *partyMenu) {
    Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
    s32 giratinaResult;
    int newItem = partyMenu->args->itemId;
    int oldItem = partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem;
    int manipulateItemResult = sub_0207C5D4(partyMenu, mon, &giratinaResult);
    if (oldItem == ITEM_GRISEOUS_ORB && manipulateItemResult == PARTY_MENU_STATE_PRINT_ITEM_SWAP_MESSAGE && giratinaResult == 0) {
        manipulateItemResult = PARTY_MENU_STATE_PRINT_TAKE_GRISEOUS_ORB_MESSAGE;
    }
    if (oldItem == ITEM_NONE) {
        ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00107, partyMenu->unformattedStrBuf);
        BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(mon));
        BufferItemName(partyMenu->msgFormat, 1, partyMenu->args->itemId);
        StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
    } else {
        Bag_AddItem(partyMenu->args->bag, oldItem, 1, HEAP_ID_PARTY_MENU);
        ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00085, partyMenu->unformattedStrBuf);
        BufferItemName(partyMenu->msgFormat, 1, oldItem);
        BufferItemName(partyMenu->msgFormat, 2, newItem);
        StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
    }
    DrawFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE, 42, 15);
    FillWindowPixelBuffer(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], 15);
    sub_0207DB30(partyMenu);
    if (partyMenu->args->context == PARTY_MENU_CONTEXT_12) {
        partyMenu->args->context = PARTY_MENU_CONTEXT_10;
    }
    return manipulateItemResult;
}

static int sub_0207CA30(PartyMenuStruct *partyMenu) {
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].capsule == 0) {
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
        return PARTY_MENU_STATE_BEGIN_EXIT;
    } else {
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 1);
        sub_0207DAEC(partyMenu, msg_0300_00179, TRUE);
        partyMenu->yesCallback = sub_0207FAA8;
        partyMenu->noCallback = sub_0207FAD4;
        partyMenu->afterTextPrinterState = PARTY_MENU_STATE_YES_NO_INIT;
        return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
    }
}

// file IDs from NARC_a_0_2_1
u32 sub_0207CA9C(void) {
    return 20;
}

u32 sub_0207CAA0(void) {
    return 21;
}

u32 sub_0207CAA4(void) {
    return 19;
}

u32 sub_0207CAA8(void) {
    return 18;
}

void sub_0207CAAC(HeapID heapId, u16 *a1, u16 *a2, u16 *a3) {
    void *pNscrFile;
    NNSG2dScreenData *screenData;
    const u16 *src;
    u32 i;

    pNscrFile = AllocAndReadWholeNarcMemberByIdPair(NARC_a_0_2_1, 22, heapId);
    NNS_G2dGetUnpackedScreenData(pNscrFile, &screenData);
    src = (const u16 *)screenData->rawData;

    for (i = 0; i < 6; ++i) {
        memcpy(&a1[i * 16], &src[i * 32], 32);
        memcpy(&a2[i * 16], &src[(i + 6) * 32], 32);
        memcpy(&a3[i * 16], &src[(i + 12) * 32], 32);
    }
    FreeToHeap(pNscrFile);
}

void sub_0207CB20(PartyMenuStruct *partyMenu) {
    PartyMenu_CloseContextMenu(partyMenu, partyMenu->contextMenuCursor);
    ListMenuItems_Delete(partyMenu->listMenuItems);
}

void sub_0207CB3C(PartyMenuStruct *partyMenu, BOOL a1) {
    if (partyMenu->args->unk_20 != NULL) {
        sub_02018410(partyMenu->args->unk_20, a1);
    }
}

void PartyMenu_FormChangeScene_Begin(PartyMenuStruct *partyMenu) {
    HandleLoadOverlay(FS_OVERLAY_ID(OVY_94), OVY_LOAD_ASYNC);
    PartyMenu_InitIconFormChangeData(partyMenu);
}

void PartyMenu_FormChangeScene_End(PartyMenuStruct *partyMenu) {
    UnloadOverlayByID(FS_OVERLAY_ID(OVY_94));
}
