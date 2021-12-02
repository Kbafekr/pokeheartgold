#include "pokemon.h"
#include "heap.h"
#include "save.h"
#include "party.h"

#define PARTY_ASSERT_SLOT(party, slot) ({             \
    GF_ASSERT(slot >= 0);                             \
    GF_ASSERT(slot < (party)->core.curCount);        \
    GF_ASSERT(slot < (party)->core.maxCount);        \
})

u32 SavArray_Party_sizeof(void) {
    return sizeof(PARTY);
}

u32 sub_020744B4(void) {
    return sizeof(PARTY_CORE);
}

PARTY * SavArray_Party_alloc(HeapID heapId) {
    PARTY *ret = AllocFromHeap(heapId, sizeof(PARTY));
    SavArray_Party_init(ret);
    return ret;
}

void SavArray_Party_init(PARTY *party) {
    InitPartyWithMaxSize(party, PARTY_SIZE);
}

void InitPartyWithMaxSize(PARTY *party, int maxSize) {
    int i;

    GF_ASSERT(maxSize <= PARTY_SIZE);
    memset(party, 0, sizeof(PARTY));
    party->core.curCount = 0;
    party->core.maxCount = maxSize;
    for (i = 0; i < PARTY_SIZE; i++) {
        ZeroMonData(&party->core.mons[i]);
    }
    MI_CpuFill8(&party->extra, 0, 5 * party->core.maxCount);
}

BOOL AddMonToParty(PARTY *party, const POKEMON *pokemon) {
    if (party->core.curCount >= party->core.maxCount) {
        return FALSE;
    }
    party->core.mons[party->core.curCount] = *pokemon;
    MI_CpuFill8(&party->extra.unk_00[party->core.curCount], 0, sizeof(PARTY_EXTRA_SUB));
    party->core.curCount++;
    return TRUE;
}

BOOL RemoveMonFromParty(PARTY *party, int slot) {
    PARTY_ASSERT_SLOT(party, slot);
    GF_ASSERT(party->core.curCount > 0);
    for (; slot < party->core.curCount - 1; slot++) {
        party->core.mons[slot] = party->core.mons[slot + 1];
        party->extra.unk_00[slot] = party->extra.unk_00[slot + 1];
    }
    ZeroMonData(&party->core.mons[slot]);
    MI_CpuFill8(&party->extra.unk_00[slot], 0, sizeof(PARTY_EXTRA_SUB));
    party->core.curCount--;
    return TRUE;
}

int GetPartyMaxCount(const PARTY *party) {
    return party->core.maxCount;
}

int GetPartyCount(const PARTY *party) {
    return party->core.curCount;
}

POKEMON *GetPartyMonByIndex(PARTY *party, int slot) {
    PARTY_ASSERT_SLOT(party, slot);
    return &party->core.mons[slot];
}

void sub_02074670(const PARTY *party, PARTY_EXTRA_SUB *dest, int slot) {
    PARTY_ASSERT_SLOT(party, slot);
    *dest = party->extra.unk_00[slot];
}

void sub_020746BC(PARTY *party, const PARTY_EXTRA_SUB *src, int slot) {
    PARTY_ASSERT_SLOT(party, slot);
    party->extra.unk_00[slot] = *src;
}

void sub_02074708(PARTY *party, int slot) {
    PARTY_ASSERT_SLOT(party, slot);
    MI_CpuFill8(&party->extra.unk_00[slot], 0, sizeof(PARTY_EXTRA_SUB));
}

void sub_02074740(PARTY *party, int slot, POKEMON *src) {
    PARTY_ASSERT_SLOT(party, slot);
    {
        BOOL valid = GetMonData(&party->core.mons[slot], MON_DATA_SPECIES_EXISTS, NULL) - GetMonData(src, MON_DATA_SPECIES_EXISTS, NULL);
        party->core.mons[slot] = *src;
        MI_CpuFill8(&party->extra.unk_00[slot], 0, sizeof(PARTY_EXTRA_SUB));
        party->core.curCount += valid;
    }
}

BOOL sub_020747BC(PARTY *party, int slotA, int slotB) {
    PARTY_EXTRA_SUB tmp_PARTY_EXTRA_SUB;
    POKEMON *tmp_POKEMON;

    PARTY_ASSERT_SLOT(party, slotA);
    PARTY_ASSERT_SLOT(party, slotB);
    tmp_POKEMON = AllocFromHeap(0, sizeof(POKEMON));
    *tmp_POKEMON = party->core.mons[slotA];
    party->core.mons[slotA] = party->core.mons[slotB];
    party->core.mons[slotB] = *tmp_POKEMON;
    FreeToHeap(tmp_POKEMON);

    tmp_PARTY_EXTRA_SUB = party->extra.unk_00[slotA];
    party->extra.unk_00[slotA] = party->extra.unk_00[slotB];
    party->extra.unk_00[slotB] = tmp_PARTY_EXTRA_SUB;
    return FALSE;
}

void sub_020748B8(const PARTY *src, PARTY *dest) {
    *dest = *src;
}

BOOL PartyHasMon(PARTY *party, u16 species) {
    int i;

    for (i = 0; i < party->core.curCount; i++) {
        if (species == GetMonData(&party->core.mons[i], MON_DATA_SPECIES2, NULL)) {
            break;
        }
    }

    return (i != party->core.curCount);
}

PARTY *SavArray_PlayerParty_get(SAVEDATA *saveData) {
    return (PARTY *) SavArray_get(saveData, SAVE_PARTY);
}