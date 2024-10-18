#include "unk_020183F0.h"

#include "global.h"

#include "gf_gfx_loader.h"

int sub_020183F0(BOOL *a0) {
    GF_ASSERT(*a0 == FALSE || *a0 == TRUE);
    return *a0;
}

void sub_02018410(BOOL *a0, BOOL a1) {
    GF_ASSERT(a1 == FALSE || a1 == TRUE);
    *a0 = a1;
}

UnkStruct_02018424 *sub_02018424(HeapID heapId, int a1) {
    UnkStruct_02018424 *ret = AllocFromHeap(heapId, sizeof(UnkStruct_02018424));
    MI_CpuFill8(ret, 0, sizeof(UnkStruct_02018424));
    ret->heapId      = heapId;
    ret->charDataRaw = GfGfxLoader_LoadFromNarc(NARC_a_1_6_5, 1, FALSE, heapId, FALSE);
    NNS_G2dGetUnpackedBGCharacterData(ret->charDataRaw, &ret->pCharData);
    ret->plttDataRaw = GfGfxLoader_LoadFromNarc(NARC_a_1_6_5, 0, FALSE, heapId, FALSE);
    NNS_G2dGetUnpackedPaletteData(ret->plttDataRaw, &ret->pPlttData);
    ret->unk_14 = a1;
    return ret;
}

void sub_02018474(UnkStruct_02018424 *a0) {
    FreeToHeap(a0->plttDataRaw);
    FreeToHeap(a0->charDataRaw);
    MI_CpuFill8(a0, 0, sizeof(UnkStruct_02018424));
    FreeToHeap(a0);
}
