#include "global.h"

#include "msgdata/msg.naix"
#include "msgdata/msg/msg_0197.h"
#include "msgdata/msg/msg_0249.h"
#include "msgdata/msg/msg_0254.h"

#include "bg_window.h"
#include "filesystem.h"
#include "font.h"
#include "gf_gfx_planes.h"
#include "launch_application.h"
#include "math_util.h"
#include "message_format.h"
#include "msgdata.h"
#include "obj_char_transfer.h"
#include "obj_pltt_transfer.h"
#include "pokemon_icon_idx.h"
#include "sound_02004A44.h"
#include "systask_environment.h"
#include "system.h"
#include "text.h"
#include "unk_02005D10.h"
#include "unk_0200ACF0.h"
#include "unk_0200B150.h"
#include "unk_0200FA24.h"
#include "unk_020163E0.h"
#include "unk_02082908.h"

typedef struct NamingScreenAppData {
    NameScreenType type;
    int unk_004;
    int unk_008;
    u8 filler_00C[0x10];
    int unk_01C;
    int unk_020;
    u8 filler_024[0xC];
    int unk_030;
    int unk_034;
    u8 unk_038[0x2];
    u16 unk_03A[6][13];
    u8 filler_0D6[2];
    u16 unk_0D8[0x20];
    u16 unk_118[0x20];
    u16 unk_158;
    u16 unk_15A;
    u8 filler_15C[0x4];
    BgConfig *bgConfig; // 0x160
    u8 filler_164[4];
    MessageFormat *msgFormat; // 0x168
    MsgData *msgData_249;     // 0x16C
    MsgData *msgData_254;     // 0x170
    MsgData *msgData_197;     // 0x174
    String *unk_178;
    String *unk_17C;
    String *unk_180;
    String *unk_184;
    SpriteList *unk_188;
    u8 unk_18C[0x128];
    GF_2DGfxResMan *unk_2B4[4];
    GF_2DGfxResObj *unk_2C4;
    GF_2DGfxResObj *unk_2C8;
    GF_2DGfxResObj *unk_2CC;
    GF_2DGfxResObj *unk_2D0;
    GF_2DGfxResObj *unk_2D4;
    GF_2DGfxResObj *unk_2D8;
    GF_2DGfxResObj *unk_2DC;
    GF_2DGfxResObj *unk_2E0;
    u8 filler_2E4[0x48];
    u8 unk_32C[0x20];
    Sprite *unk_34C;
    u8 filler_350[0x4C];
    SysTask *unk_39C[7];
    u8 unk_3B8[0x40];
    u8 unk_3F8[0x50];
    Window unk_448;
    int unk_458;
    int unk_45C;
    int unk_460;
    u8 unk_464[4];
    u8 unk_468[4];
    u8 filler_46C[0x24];
    int unk_490[6];
    int unk_4A8;
    void *unk_4AC;
    NNSG2dCharacterData *unk_4B0;
    void *unk_4B4;
    NNSG2dCharacterData *unk_4B8;
    void *unk_4BC;
    NNSG2dPaletteData *unk_4C0;
    u8 unk_4C4[0x100];
    UnkStruct_020163E0 *unk_5C4;
    BOOL unk_5C8;
    int unk_5CC;
    u8 filler_5D0[0x4];
} NamingScreenAppData; // size: 0x5D4

BOOL NamingScreenApp_Init(OVY_MANAGER *ovyMan, int *pState);
void sub_02082AEC(NNSG2dCharacterData *pCharData, NNSG2dPaletteData *pPlttData, int species, int form);
BOOL NamingScreenApp_Main(OVY_MANAGER *ovyMan, int *pState);
int sub_02082CF8(NamingScreenAppData *data, int a1);
void sub_02082E28(NamingScreenAppData *data, NamingScreenArgs *args);
BOOL sub_02082EC0(const u16 *s);
BOOL NamingScreenApp_Exit(OVY_MANAGER *ovyMan, int *pState);
void sub_02083140(void *param);
BOOL sub_02082EC0(const u16 *s);
void sub_02083160(NamingScreenAppData *data, NamingScreenArgs *args);
void sub_02083184(void);
void sub_020831A4(BgConfig *bgConfig);
void sub_020832E4(int a0);
void sub_02083334(NamingScreenAppData *data, OVY_MANAGER *ovyMan);
void sub_020834FC(NamingScreenAppData *data, OVY_MANAGER *ovyMan);
void sub_02083614(BgConfig *bgConfig, void *a1);
void sub_02083654(NamingScreenAppData *data, NARC *narc);
void sub_0208377C(void);
void sub_020837AC(NamingScreenAppData *data, NARC *narc);
void sub_020839EC(NamingScreenAppData *data);
void sub_02083D34(BgConfig *bgConfig, void *a1, void *a2, int a3, void *a4, void *a5, void *a6, const u16 *a7);
void sub_02083F9C(NamingScreenAppData *data, OVY_MANAGER *ovyMan, NARC *narc);
void sub_0208432C(NamingScreenAppData *data);
void sub_02084740(void *a0, u16 *a1, u16 a2, void *a3, void *a4, String *a5);
void sub_02084830(u16 (*a0)[13], int a1);
int sub_02084884(NamingScreenAppData *data, int key, BOOL a2);
void sub_02084F3C(void *a0, void *a1, int a2);
void sub_02084FCC(NamingScreenAppData *data);
void sub_02084500(void *a0);

static NamingScreenAppData *_021D43B0;

BOOL NamingScreenApp_Init(OVY_MANAGER *ovyMan, int *pState) {
    NamingScreenAppData *data;
    NARC *narc;
    switch (*pState) {
    case 0:
        Main_SetVBlankIntrCB(NULL, NULL);
        HBlankInterruptDisable();
        GfGfx_DisableEngineAPlanes();
        GfGfx_DisableEngineBPlanes();
        GX_SetVisiblePlane(0);
        GXS_SetVisiblePlane(0);
        CreateHeap(HEAP_ID_3, HEAP_ID_NAMING_SCREEN, 0x28000);

        data = OverlayManager_CreateAndGetData(ovyMan, sizeof(NamingScreenAppData), HEAP_ID_NAMING_SCREEN);
        memset(data, 0, sizeof(NamingScreenAppData));
        data->bgConfig    = BgConfig_Alloc(HEAP_ID_NAMING_SCREEN);
        narc              = NARC_New(NARC_a_0_3_1, HEAP_ID_NAMING_SCREEN);
        data->msgFormat   = MessageFormat_New(HEAP_ID_NAMING_SCREEN);
        data->msgData_249 = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_msgdata_msg, NARC_msg_msg_0249_bin, HEAP_ID_NAMING_SCREEN);
        data->msgData_254 = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0254_bin, HEAP_ID_NAMING_SCREEN);
        data->msgData_197 = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0197_bin, HEAP_ID_NAMING_SCREEN);
        SetKeyRepeatTimers(4, 8);
        sub_02083184();
        sub_020831A4(data->bgConfig);
        sub_02083160(data, OverlayManager_GetArgs(ovyMan));
        sub_02083654(data, narc);
        FontID_Alloc(2, HEAP_ID_NAMING_SCREEN);
        Main_SetVBlankIntrCB(sub_02083140, NULL);
        sub_02083334(data, ovyMan);
        FontID_SetAccessDirect(0, HEAP_ID_NAMING_SCREEN);
        sub_0208377C();
        sub_020837AC(data, narc);
        sub_020839EC(data);
        sub_02083F9C(data, ovyMan, narc);
        sub_02084740(data->unk_3F8, data->unk_0D8, data->unk_158, &data->unk_15A, data->unk_4C4, data->unk_17C);
        sub_02004EC4(0x34, 0, 0);
        BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 16, 1, HEAP_ID_NAMING_SCREEN);
        sub_020832E4(1);
        GfGfx_SetMainDisplay(PM_LCD_BOTTOM);
        NARC_Delete(narc);
        ++(*pState);
        break;
    case 1:
        data = OverlayManager_GetData(ovyMan);
        if (data->type == NAME_SCREEN_POKEMON) {
            sub_02082AEC(data->unk_4B8, data->unk_4C0, data->unk_004, data->unk_008);
        }
        _021D43B0     = data;
        data->unk_5C4 = sub_020163E0(NULL, PM_LCD_BOTTOM, 12, HEAP_ID_NAMING_SCREEN);
        *pState       = 0;
        return TRUE;
    }

    return FALSE;
}

void sub_02082AEC(NNSG2dCharacterData *pCharData, NNSG2dPaletteData *pPlttData, int species, int form) {
    GX_LoadOBJ(pCharData->pRawData, 0x57E0, 0x200);
    const u16 *rawPltt = pPlttData->pRawData;
    u32 plttNo         = GetMonIconPaletteEx(species, form, FALSE);
    GX_LoadOBJPltt(rawPltt + 16 * plttNo, 0xC0, 0x20);
}

BOOL NamingScreenApp_Main(OVY_MANAGER *ovyMan, int *pState) {
    NamingScreenAppData *data = OverlayManager_GetData(ovyMan);

    switch (*pState) {
    case 0:
        if (IsPaletteFadeFinished()) {
            *pState       = 1;
            data->unk_5CC = 0;
        }
        break;
    case 1:
        ++data->unk_5CC;
        sub_02084FCC(data);
        sub_02084F3C(data->unk_490, data->unk_32C, data->unk_460);
        if (data->unk_5CC > 5) {
            *pState       = 2;
            data->unk_5CC = 0;
        }
        break;
    case 2:
        switch (data->unk_45C) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            if (data->unk_034 == 0) {
                *pState = sub_02082CF8(data, *pState);
            }
            sub_02084FCC(data);
            break;
        case 5:
            sub_020834FC(data, ovyMan);
            FillWindowPixelBuffer(&data->unk_448, 15);
            DrawFrameAndWindow2(&data->unk_448, FALSE, 256, 10);
            data->unk_458 = AddTextPrinterParameterized(&data->unk_448, 1, data->unk_180, 0, 0, 1, NULL);
            CopyWindowToVram(&data->unk_448);
            data->unk_45C = 6;
            break;
        case 6:
            if (!TextPrinterCheckActive(data->unk_458)) {
                PlaySE(SEQ_SE_DP_PIRORIRO);
                ++data->unk_4A8;
                data->unk_5CC = 0;
                data->unk_45C = 7;
            }
            break;
        case 7:
            ++data->unk_5CC;
            if (data->unk_5CC > 30) {
                BeginNormalPaletteFade(2, 0, 0, RGB_BLACK, 16, 1, HEAP_ID_NAMING_SCREEN);
                *pState = 3;
            }
            break;
        }
        sub_02083D34(data->bgConfig, data->unk_3B8, &data->unk_45C, data->unk_460, data->unk_464, data->unk_468, data->unk_32C, data->unk_4B0->pRawData);
        sub_02084F3C(data->unk_490, data->unk_32C, data->unk_460);
        sub_02084500(data->unk_038);
        break;
    case 3:
        if (IsPaletteFadeFinished()) {
            return TRUE;
        }
        break;
    }

    SpriteList_RenderAndAnimateSprites(data->unk_188);
    return FALSE;
}

int sub_02082CF8(NamingScreenAppData *data, int a1) {
    int ret = a1;

    sub_0208432C(data);
    if (gSystem.newKeys & PAD_BUTTON_SELECT) {
        if (!Sprite_GetVisibleFlag(data->unk_34C)) {
            Sprite_SetVisibleFlag(data->unk_34C, TRUE);
            return ret;
        }
        if (data->type != 4) {
            data->unk_45C = 0;
            ++data->unk_460;
            if (data->unk_460 >= 3) {
                data->unk_460 = 0;
            }
            ++data->unk_490[data->unk_460];
            sub_02084830(data->unk_03A, data->unk_460);
            PlaySE(SEQ_SE_DP_SYU03);
            data->unk_030 = 1;
        }
        ++data->unk_490[data->unk_460];
        sub_02084830(data->unk_03A, data->unk_460);
        PlaySE(SEQ_SE_DP_SYU03);
    } else if (gSystem.newKeys & PAD_BUTTON_A) {
        ret           = sub_02084884(data, data->unk_03A[data->unk_020][data->unk_01C], TRUE);
        data->unk_030 = 1;
    } else if (data->unk_5C8 == TRUE) {
        ret = sub_02084884(data, data->unk_03A[data->unk_020][data->unk_01C], FALSE);
    } else if (gSystem.newKeys & PAD_BUTTON_B) {
        ret = sub_02084884(data, 0xE007, TRUE);
    } else if (gSystem.newKeys & PAD_BUTTON_R) {
        ret = sub_02084884(data, 0xE006, TRUE);
    }
    return ret;
}

#ifdef HEARTGOLD
#define FIRST_DEFAULT_NAME_MALE   msg_0254_00000
#define FIRST_DEFAULT_NAME_FEMALE msg_0254_00018
#define FIRST_DEFAULT_NAME_RIVAL  msg_0254_00084
#else
#define FIRST_DEFAULT_NAME_MALE   msg_0254_00042
#define FIRST_DEFAULT_NAME_FEMALE msg_0254_00060
#define FIRST_DEFAULT_NAME_RIVAL  msg_0254_00085
#endif // HEARTGOLD

void sub_02082E28(NamingScreenAppData *data, NamingScreenArgs *args) {
    String *string;

    if (data->type == NAME_SCREEN_PLAYER) {
        if (data->unk_004 == PLAYER_GENDER_MALE) {
            string = NewString_ReadMsgData(data->msgData_254, FIRST_DEFAULT_NAME_MALE + (LCRandom() % 18));
        } else if (data->unk_004 == PLAYER_GENDER_FEMALE) {
            string = NewString_ReadMsgData(data->msgData_254, FIRST_DEFAULT_NAME_FEMALE + (LCRandom() % 18));
        }
        // UB: Nonbinary players will not initialize string.
        String_Copy(args->nameInputString, string);
        String_Delete(string);
        CopyStringToU16Array(args->nameInputString, args->unk1C, 10);
    } else if (data->type == NAME_SCREEN_RIVAL) {
        string = NewString_ReadMsgData(data->msgData_254, FIRST_DEFAULT_NAME_RIVAL);
        String_Copy(args->nameInputString, string);
        String_Delete(string);
        CopyStringToU16Array(args->nameInputString, args->unk1C, 10);
    } else {
        args->unk14 = 1;
    }
}

BOOL sub_02082EC0(const u16 *s) {
    BOOL ret = TRUE;
    int i;

    for (i = 0;; ++i) {
        if (s[i] == EOS) {
            break;
        }
        if (s[i] != CHAR_SPACE) {
            ret = FALSE;
        }
    }
    return ret;
}

BOOL NamingScreenApp_Exit(OVY_MANAGER *ovyMan, int *pState) {
    NamingScreenAppData *data = OverlayManager_GetData(ovyMan);
    NamingScreenArgs *args    = OverlayManager_GetArgs(ovyMan);

    data->unk_0D8[data->unk_158] = EOS;
    if (data->type == NAME_SCREEN_POKEMON) {
        Pokemon *mon = AllocMonZeroed(HEAP_ID_NAMING_SCREEN);
        CreateMon(mon, data->unk_004, 5, 10, 10, 10, 10, 10);
        // wtf
        FreeToHeap(mon);
    }
    if (data->unk_158 == 0 || !StringNotEqual(data->unk_0D8, data->unk_118) || sub_02082EC0(data->unk_0D8)) {
        sub_02082E28(data, args);
    } else {
        CopyU16StringArray(data->unk_118, data->unk_0D8);
        CopyU16StringArray(args->unk1C, data->unk_0D8);
        CopyU16ArrayToString(args->nameInputString, data->unk_0D8);
    }
    String_Delete(data->unk_184);
    for (int i = 0; i < 7; ++i) {
        DestroySysTaskAndEnvironment(data->unk_39C[i]);
    }
    sub_0200AEB0(data->unk_2C4);
    sub_0200AEB0(data->unk_2D4);
    sub_0200B0A8(data->unk_2C8);
    sub_0200B0A8(data->unk_2D8);
    for (int i = 0; i < 4; ++i) {
        Destroy2DGfxResObjMan(data->unk_2B4[i]);
    }
    SpriteList_Delete(data->unk_188);
    OamManager_Free();
    FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, data->unk_4AC);
    if (data->type == NAME_SCREEN_POKEMON) {
        FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, data->unk_4B4);
        FreeToHeapExplicit(HEAP_ID_NAMING_SCREEN, data->unk_4BC);
    }
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_3);
    ObjCharTransfer_Destroy();
    ObjPlttTransfer_Destroy();
    sub_02083614(data->bgConfig, data->unk_3B8);
    FontID_SetAccessLazy(0);
    GX_SetVisibleWnd(0);
    FontID_Release(2);
    if (data->unk_180 != NULL) {
        String_Delete(data->unk_180);
    }
    String_Delete(data->unk_178);
    String_Delete(data->unk_17C);
    DestroyMsgData(data->msgData_197);
    DestroyMsgData(data->msgData_254);
    DestroyMsgData(data->msgData_249);
    MessageFormat_Delete(data->msgFormat);
    OverlayManager_FreeData(ovyMan);
    Main_SetVBlankIntrCB(NULL, NULL);
    DestroyHeap(HEAP_ID_NAMING_SCREEN);
    GfGfx_SetMainDisplay(PM_LCD_TOP);
    return TRUE;
}
