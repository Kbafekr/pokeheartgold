#include "scrcmd.h"
#include "gf_gfx_loader.h"
#include "unk_0200FA24.h"
#include "blackout.h"
#include "system.h"
#include "render_window.h"
#include "font.h"
#include "text.h"
#include "save_local_field_data.h"
#include "unk_0203BA5C.h"
#include "field_warp_tasks.h"
#include "brightness.h"
#include "unk_0206793C.h"
#include "unk_0200B150.h"
#include "unk_02054E00.h"
#include "unk_020552A4.h"
#include "use_item_on_mon.h"
#include "sound.h"
#include "msgdata/msg/msg_0203.h"
#include "msgdata/msg.naix"

static void Blackout_InitDisplays(BgConfig *bgConfig);
void Blackout_DrawMessage(FieldSystem *fieldSystem, TaskManager *taskManager);
BOOL Task_ShowPrintedBlackoutMessage(TaskManager *taskManager);
void _PrintMessage(BlackoutScreenEnvironment *environment, int msgno, u8 x, u8 y);

static const struct GraphicsBanks Blackout_GraphicsBanks = {
    .bg = GX_VRAM_BG_128_B,
    .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
    .subbg = GX_VRAM_SUB_BG_128_C,
    .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
    .obj = GX_VRAM_OBJ_64_E,
    .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
    .subobj = GX_VRAM_SUB_OBJ_16_I,
    .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
    .tex = GX_VRAM_TEX_0_A,
    .texpltt = GX_VRAM_TEXPLTT_01_FG,
};

static const struct GraphicsModes Blackout_GraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const BgTemplate Blackout_BgTemplate = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0,
    .size = GF_BG_SCR_SIZE_256x256,
    .colorMode = GX_BG_COLORMODE_16,
    .screenBase = GX_BG_SCRBASE_0xf800,
    .charBase = GX_BG_CHARBASE_0x00000,
    .bgExtPltt = GX_BG_EXTPLTT_01,
    .priority = 1,
    .areaOver = GX_BG_AREAOVER_XLU,
    .dummy = 0,
    .mosaic = FALSE
};

static const WindowTemplate Blackout_WindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_3,
    .left = 4,
    .top = 5,
    .width = 25,
    .height = 15,
    .palette = 13,
    .baseTile = 0x01
};

static void Blackout_InitDisplays(BgConfig *bgConfig) {
    GfGfx_SetBanks(&Blackout_GraphicsBanks);
    SetBothScreensModesAndDisable(&Blackout_GraphicsModes);
    InitBgFromTemplate(bgConfig, 3, &Blackout_BgTemplate, GF_BG_TYPE_TEXT);
    GfGfxLoader_GXLoadPal(NARC_graphic_font, 7, GF_BG_LYR_MAIN_0, 0x1A0, 0x20, HEAP_ID_FIELD); //TODO: update these enums
    BG_SetMaskColor(3, RGB_WHITE);
}

static void Blackout_DrawMessage(FieldSystem *fieldSystem, TaskManager *taskManager) {
    BlackoutScreenEnvironment *env = AllocFromHeap(HEAP_ID_FIELD, sizeof(BlackoutScreenEnvironment));

    GF_ASSERT(env != NULL);
    memset(env, 0, sizeof(BlackoutScreenEnvironment));
    env->state = 0;
    env->fieldSystem = fieldSystem;
    env->bgConfig = BgConfig_Alloc(HEAP_ID_FIELD);
    sub_0200FBF4(PM_LCD_TOP, RGB_WHITE); //are RGBs correct here?
    sub_0200FBF4(PM_LCD_BOTTOM, RGB_WHITE);
    sub_0200FBDC(0); //PM_LCD_TOP?
    sub_0200FBDC(1); //PM_LCD_TOP?
    Blackout_InitDisplays(env->bgConfig);
    env->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0203_bin, HEAP_ID_FIELD);
    env->msgFmt = MessageFormat_New(HEAP_ID_FIELD);

    AddWindow(env->bgConfig, &env->window, &Blackout_WindowTemplate);

    BufferPlayersName(env->msgFmt, 0, Save_PlayerData_GetProfileAddr(FieldSystem_GetSaveData(fieldSystem)));
    if (fieldSystem->location->mapId == MAP_T20R0201) {
        // {STRVAR_1 3, 0, 0} scurried back\nhome, protecting the exhausted\nand fainted Pokémon from further\nharm...
        _PrintMessage(env, msg_0203_00004, 0, 0);
    } else {
        // {STRVAR_1 3, 0, 0} scurried to\na Pokémon Center, protecting\nthe exhausted and fainted\nPokémon from further harm...
        _PrintMessage(env, msg_0203_00003, 0, 0);
    }
    CopyWindowToVram(&env->window);
    TaskManager_Call(taskManager, Task_ShowPrintedBlackoutMessage, env);
}

static BOOL Task_ShowPrintedBlackoutMessage(TaskManager *taskManager) {
    BlackoutScreenEnvironment *work = TaskManager_GetEnvironment(taskManager);
    switch (work->state) {
    case 0:
        BeginNormalPaletteFade(3, 1, 43, RGB_WHITE, 8, 1, (HeapID)32);
        G2_BlendNone();
        work->state++;
        break;
    case 1:
        if (IsPaletteFadeFinished()) {
            work->state++;
        }
        break;
    case 2:
        if (gSystem.newKeys & PAD_BUTTON_A || gSystem.newKeys & PAD_BUTTON_B || gSystem.touchNew != 0) {
            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 8, 1, (HeapID)32);
            work->state++;
        }
        break;
    case 3:
        if (IsPaletteFadeFinished()) {
            FillWindowPixelBuffer(&work->window, 0);
            work->state++;
        }
        break;
    case 4:
        ClearFrameAndWindow2(&work->window, 0);
        RemoveWindow(&work->window);
        MessageFormat_Delete(work->msgFmt);
        DestroyMsgData(work->msgData);
        FreeBgTilemapBuffer(work->bgConfig, 3);
        FreeToHeap(work->bgConfig);
        FreeToHeap(work);
        return TRUE;
    }

    return FALSE;
}

static void _PrintMessage(BlackoutScreenEnvironment *work, int msgno, u8 x, u8 y) {
    String *str0 = String_New(1024, (HeapID)11);
    String *str1 = String_New(1024, (HeapID)11);

    FillWindowPixelBuffer(&work->window, 0);
    ReadMsgDataIntoString(work->msgData, msgno, str0);
    StringExpandPlaceholders(work->msgFmt, str1, str0);
    {
        u32 width = FontID_String_GetWidthMultiline(0, str1, 0);
        x = (work->window.width * 8 - width);
        x /= 2;
        x -= 4;
        AddTextPrinterParameterized2(&work->window, 0, str1, x, y, TEXT_SPEED_NOTRANSFER, MakeTextColor(1, 2, 0), NULL);
    }

    String_Delete(str0);
    String_Delete(str1);
}

BOOL Task_BlackOut(TaskManager *taskManager) {
    FieldSystem *fieldSystem = TaskManager_GetFieldSystem(taskManager);
    u32 *state = TaskManager_GetStatePtr(taskManager);
    LocalFieldData *localFieldData;
    Location deathWarp;
    u16 deathSpawn;

    switch (*state) {
    case 0:
        localFieldData = Save_LocalFieldData_Get(fieldSystem->saveData);
        deathSpawn = LocalFieldData_GetBlackoutSpawn(localFieldData);
        GetDeathWarpData(deathSpawn, &deathWarp);
        GetSpecialSpawnWarpData(deathSpawn, LocalFieldData_GetSpecialSpawnWarpPtr(localFieldData));
        sub_020537A8(taskManager, &deathWarp);
        FieldSystem_ClearFollowingTrainer(fieldSystem);
        HealParty(SaveArray_Party_Get(fieldSystem->saveData));
        (*state)++;
        break;
    case 1:
        GF_SndStartFadeOutBGM(0, 20);
        (*state)++;
        break;
    case 2:
        if (GF_SndGetFadeTimer() == 0) {
            sub_02054F14();
            (*state)++;
        }
        break;
    case 3:
        SetBlendBrightness(-16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_MAIN);
        SetBlendBrightness(-16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_SUB);
        Blackout_DrawMessage(fieldSystem, taskManager);
        (*state)++;
        break;
    case 4:
        CallTask_RestoreOverworld(taskManager);
        (*state)++;
        break;
    case 5:
        SetBlendBrightness(0, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_MAIN | SCREEN_MASK_SUB);
        if (GetMomSpawnId() == LocalFieldData_GetBlackoutSpawn(Save_LocalFieldData_Get(fieldSystem->saveData))) {
            QueueScript(taskManager, std_whited_out_to_mom, NULL, NULL);
        } else {
            QueueScript(taskManager, std_whited_out_to_pokecenter, NULL, NULL);
        }
        (*state)++;
        break;
    case 6:
        return TRUE;
    }

    return FALSE;
}

void CallTask_BlackOut(TaskManager *taskManager) {
    TaskManager_Call(taskManager, Task_BlackOut, NULL);
}
