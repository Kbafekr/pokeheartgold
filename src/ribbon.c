#include "ribbon.h"

#include "global.h"

#include "constants/pokemon.h"

#include "msgdata/msg/msg_0424.h"

#define RIBBON_DESC_ID_MASK  0x00FF
#define RIBBON_DESC_ID_SHIFT 0
#define RIBBON_DESC_ID_SIZE  8

#define RIBBON_DESC_SPECIAL_MASK  0x8000
#define RIBBON_DESC_SPECIAL_SHIFT 15
#define RIBBON_DESC_SPECIAL_SIZE  1

// if sp == FALSE, id is a gmm id. if sp == TRUE, id points to a special ribbon
#define RIBBON_DESC(sp, id) ( \
    ((id) << RIBBON_DESC_ID_SHIFT) | ((sp) << RIBBON_DESC_SPECIAL_SHIFT))

struct RibbonData {
    u32 monDataNo;
    u16 ncgrId;
    u16 nclrId;
    u16 nameGmm;
    u16 descGmm;
};

static const struct RibbonData sRibbonInfo[] = {
    { MON_DATA_HOENN_CHAMPION_RIBBON,      72,  0, msg_0424_00000, RIBBON_DESC(FALSE, msg_0424_00080) },
    { MON_DATA_HOENN_COOL_RIBBON,          73,  0, msg_0424_00001, RIBBON_DESC(FALSE, msg_0424_00081) },
    { MON_DATA_HOENN_COOL_RIBBON_SUPER,    74,  0, msg_0424_00002, RIBBON_DESC(FALSE, msg_0424_00082) },
    { MON_DATA_HOENN_COOL_RIBBON_HYPER,    75,  0, msg_0424_00003, RIBBON_DESC(FALSE, msg_0424_00083) },
    { MON_DATA_HOENN_COOL_RIBBON_MASTER,   76,  0, msg_0424_00004, RIBBON_DESC(FALSE, msg_0424_00084) },
    { MON_DATA_HOENN_BEAUTY_RIBBON,        73,  1, msg_0424_00005, RIBBON_DESC(FALSE, msg_0424_00085) },
    { MON_DATA_HOENN_BEAUTY_RIBBON_SUPER,  74,  1, msg_0424_00006, RIBBON_DESC(FALSE, msg_0424_00086) },
    { MON_DATA_HOENN_BEAUTY_RIBBON_HYPER,  75,  1, msg_0424_00007, RIBBON_DESC(FALSE, msg_0424_00087) },
    { MON_DATA_HOENN_BEAUTY_RIBBON_MASTER, 76,  1, msg_0424_00008, RIBBON_DESC(FALSE, msg_0424_00088) },
    { MON_DATA_HOENN_CUTE_RIBBON,          73,  2, msg_0424_00009, RIBBON_DESC(FALSE, msg_0424_00089) },
    { MON_DATA_HOENN_CUTE_RIBBON_SUPER,    74,  2, msg_0424_00010, RIBBON_DESC(FALSE, msg_0424_00090) },
    { MON_DATA_HOENN_CUTE_RIBBON_HYPER,    75,  2, msg_0424_00011, RIBBON_DESC(FALSE, msg_0424_00091) },
    { MON_DATA_HOENN_CUTE_RIBBON_MASTER,   76,  2, msg_0424_00012, RIBBON_DESC(FALSE, msg_0424_00092) },
    { MON_DATA_HOENN_SMART_RIBBON,         73,  3, msg_0424_00013, RIBBON_DESC(FALSE, msg_0424_00093) },
    { MON_DATA_HOENN_SMART_RIBBON_SUPER,   74,  3, msg_0424_00014, RIBBON_DESC(FALSE, msg_0424_00094) },
    { MON_DATA_HOENN_SMART_RIBBON_HYPER,   75,  3, msg_0424_00015, RIBBON_DESC(FALSE, msg_0424_00095) },
    { MON_DATA_HOENN_SMART_RIBBON_MASTER,  76,  3, msg_0424_00016, RIBBON_DESC(FALSE, msg_0424_00096) },
    { MON_DATA_HOENN_TOUGH_RIBBON,         73,  4, msg_0424_00017, RIBBON_DESC(FALSE, msg_0424_00097) },
    { MON_DATA_HOENN_TOUGH_RIBBON_SUPER,   74,  4, msg_0424_00018, RIBBON_DESC(FALSE, msg_0424_00098) },
    { MON_DATA_HOENN_TOUGH_RIBBON_HYPER,   75,  4, msg_0424_00019, RIBBON_DESC(FALSE, msg_0424_00099) },
    { MON_DATA_HOENN_TOUGH_RIBBON_MASTER,  76,  4, msg_0424_00020, RIBBON_DESC(FALSE, msg_0424_00100) },
    { MON_DATA_HOENN_WINNING_RIBBON,       78,  0, msg_0424_00021, RIBBON_DESC(FALSE, msg_0424_00101) },
    { MON_DATA_HOENN_VICTORY_RIBBON,       77,  0, msg_0424_00022, RIBBON_DESC(FALSE, msg_0424_00102) },
    { MON_DATA_HOENN_ARTIST_RIBBON,        79,  1, msg_0424_00023, RIBBON_DESC(FALSE, msg_0424_00103) },
    { MON_DATA_HOENN_EFFORT_RIBBON,        80,  2, msg_0424_00024, RIBBON_DESC(FALSE, msg_0424_00104) },
    { MON_DATA_HOENN_MARINE_RIBBON,        81,  1, msg_0424_00025, RIBBON_DESC(TRUE,  0)              },
    { MON_DATA_HOENN_LAND_RIBBON,          81,  3, msg_0424_00026, RIBBON_DESC(TRUE,  1)              },
    { MON_DATA_HOENN_SKY_RIBBON,           81,  4, msg_0424_00027, RIBBON_DESC(TRUE,  2)              },
    { MON_DATA_HOENN_COUNTRY_RIBBON,       82,  3, msg_0424_00028, RIBBON_DESC(FALSE, msg_0424_00178) },
    { MON_DATA_HOENN_NATIONAL_RIBBON,      82,  4, msg_0424_00029, RIBBON_DESC(FALSE, msg_0424_00190) },
    { MON_DATA_HOENN_EARTH_RIBBON,         83,  0, msg_0424_00030, RIBBON_DESC(FALSE, msg_0424_00191) },
    { MON_DATA_HOENN_WORLD_RIBBON,         83,  1, msg_0424_00031, RIBBON_DESC(FALSE, msg_0424_00178) },
    { MON_DATA_SINNOH_CHAMP_RIBBON,        88,  0, msg_0424_00032, RIBBON_DESC(FALSE, msg_0424_00105) },
    { MON_DATA_COOL_RIBBON,                89,  0, msg_0424_00033, RIBBON_DESC(FALSE, msg_0424_00106) },
    { MON_DATA_COOL_RIBBON_GREAT,          90,  0, msg_0424_00034, RIBBON_DESC(FALSE, msg_0424_00107) },
    { MON_DATA_COOL_RIBBON_ULTRA,          91,  0, msg_0424_00035, RIBBON_DESC(FALSE, msg_0424_00108) },
    { MON_DATA_COOL_RIBBON_MASTER,         92,  0, msg_0424_00036, RIBBON_DESC(FALSE, msg_0424_00109) },
    { MON_DATA_BEAUTY_RIBBON,              89,  1, msg_0424_00037, RIBBON_DESC(FALSE, msg_0424_00110) },
    { MON_DATA_BEAUTY_RIBBON_GREAT,        90,  1, msg_0424_00038, RIBBON_DESC(FALSE, msg_0424_00111) },
    { MON_DATA_BEAUTY_RIBBON_ULTRA,        91,  1, msg_0424_00039, RIBBON_DESC(FALSE, msg_0424_00112) },
    { MON_DATA_BEAUTY_RIBBON_MASTER,       92,  1, msg_0424_00040, RIBBON_DESC(FALSE, msg_0424_00113) },
    { MON_DATA_CUTE_RIBBON,                89,  2, msg_0424_00041, RIBBON_DESC(FALSE, msg_0424_00114) },
    { MON_DATA_CUTE_RIBBON_GREAT,          90,  2, msg_0424_00042, RIBBON_DESC(FALSE, msg_0424_00115) },
    { MON_DATA_CUTE_RIBBON_ULTRA,          91,  2, msg_0424_00043, RIBBON_DESC(FALSE, msg_0424_00116) },
    { MON_DATA_CUTE_RIBBON_MASTER,         92,  2, msg_0424_00044, RIBBON_DESC(FALSE, msg_0424_00117) },
    { MON_DATA_SMART_RIBBON,               89,  3, msg_0424_00045, RIBBON_DESC(FALSE, msg_0424_00118) },
    { MON_DATA_SMART_RIBBON_GREAT,         90,  3, msg_0424_00046, RIBBON_DESC(FALSE, msg_0424_00119) },
    { MON_DATA_SMART_RIBBON_ULTRA,         91,  3, msg_0424_00047, RIBBON_DESC(FALSE, msg_0424_00120) },
    { MON_DATA_SMART_RIBBON_MASTER,        92,  3, msg_0424_00048, RIBBON_DESC(FALSE, msg_0424_00121) },
    { MON_DATA_TOUGH_RIBBON,               89,  4, msg_0424_00049, RIBBON_DESC(FALSE, msg_0424_00122) },
    { MON_DATA_TOUGH_RIBBON_GREAT,         90,  4, msg_0424_00050, RIBBON_DESC(FALSE, msg_0424_00123) },
    { MON_DATA_TOUGH_RIBBON_ULTRA,         91,  4, msg_0424_00051, RIBBON_DESC(FALSE, msg_0424_00124) },
    { MON_DATA_TOUGH_RIBBON_MASTER,        92,  4, msg_0424_00052, RIBBON_DESC(FALSE, msg_0424_00125) },
    { MON_DATA_ABILITY_RIBBON,             93,  0, msg_0424_00053, RIBBON_DESC(FALSE, msg_0424_00126) },
    { MON_DATA_GREAT_ABILITY_RIBBON,       94,  0, msg_0424_00054, RIBBON_DESC(FALSE, msg_0424_00127) },
    { MON_DATA_DOUBLE_ABILITY_RIBBON,      95,  0, msg_0424_00055, RIBBON_DESC(FALSE, msg_0424_00128) },
    { MON_DATA_MULTI_ABILITY_RIBBON,       96,  0, msg_0424_00056, RIBBON_DESC(FALSE, msg_0424_00129) },
    { MON_DATA_PAIR_ABILITY_RIBBON,        97,  0, msg_0424_00057, RIBBON_DESC(FALSE, msg_0424_00130) },
    { MON_DATA_WORLD_ABILITY_RIBBON,       98,  0, msg_0424_00058, RIBBON_DESC(FALSE, msg_0424_00131) },
    { MON_DATA_ALERT_RIBBON,               99,  2, msg_0424_00059, RIBBON_DESC(FALSE, msg_0424_00132) },
    { MON_DATA_SHOCK_RIBBON,               100, 0, msg_0424_00060, RIBBON_DESC(FALSE, msg_0424_00133) },
    { MON_DATA_DOWNCAST_RIBBON,            101, 1, msg_0424_00061, RIBBON_DESC(FALSE, msg_0424_00134) },
    { MON_DATA_CARELESS_RIBBON,            102, 2, msg_0424_00062, RIBBON_DESC(FALSE, msg_0424_00135) },
    { MON_DATA_RELAX_RIBBON,               103, 3, msg_0424_00063, RIBBON_DESC(FALSE, msg_0424_00136) },
    { MON_DATA_SNOOZE_RIBBON,              104, 0, msg_0424_00064, RIBBON_DESC(FALSE, msg_0424_00137) },
    { MON_DATA_SMILE_RIBBON,               105, 2, msg_0424_00065, RIBBON_DESC(FALSE, msg_0424_00138) },
    { MON_DATA_GORGEOUS_RIBBON,            106, 1, msg_0424_00066, RIBBON_DESC(FALSE, msg_0424_00139) },
    { MON_DATA_ROYAL_RIBBON,               107, 3, msg_0424_00067, RIBBON_DESC(FALSE, msg_0424_00140) },
    { MON_DATA_GORGEOUS_ROYAL_RIBBON,      108, 0, msg_0424_00068, RIBBON_DESC(FALSE, msg_0424_00141) },
    { MON_DATA_FOOTPRINT_RIBBON,           109, 0, msg_0424_00069, RIBBON_DESC(FALSE, msg_0424_00142) },
    { MON_DATA_RECORD_RIBBON,              110, 1, msg_0424_00070, RIBBON_DESC(FALSE, msg_0424_00143) },
    { MON_DATA_HISTORY_RIBBON,             111, 3, msg_0424_00071, RIBBON_DESC(FALSE, msg_0424_00144) },
    { MON_DATA_LEGEND_RIBBON,              112, 0, msg_0424_00072, RIBBON_DESC(FALSE, msg_0424_00145) },
    { MON_DATA_RED_RIBBON,                 113, 0, msg_0424_00073, RIBBON_DESC(TRUE,  7)              },
    { MON_DATA_GREEN_RIBBON,               114, 3, msg_0424_00074, RIBBON_DESC(TRUE,  8)              },
    { MON_DATA_BLUE_RIBBON,                115, 1, msg_0424_00075, RIBBON_DESC(TRUE,  9)              },
    { MON_DATA_FESTIVAL_RIBBON,            116, 1, msg_0424_00076, RIBBON_DESC(TRUE,  10)             },
    { MON_DATA_CARNIVAL_RIBBON,            117, 0, msg_0424_00077, RIBBON_DESC(TRUE,  11)             },
    { MON_DATA_CLASSIC_RIBBON,             118, 1, msg_0424_00078, RIBBON_DESC(TRUE,  12)             },
    { MON_DATA_PREMIER_RIBBON,             119, 0, msg_0424_00079, RIBBON_DESC(TRUE,  13)             },
};

u32 GetRibbonAttr(u8 ribbon, RibbonAttr attr) {
    switch (attr) {
    case RIBBONDAT_MONDATNO:
        return sRibbonInfo[ribbon].monDataNo;
    case RIBBONDAT_NCGR:
        return sRibbonInfo[ribbon].ncgrId;
    case RIBBONDAT_NCLR:
        return sRibbonInfo[ribbon].nclrId;
    case RIBBONDAT_NAMEGMM:
        return sRibbonInfo[ribbon].nameGmm;
    case RIBBONDAT_DESCGMM:
        return sRibbonInfo[ribbon].descGmm;
    }

    return 0;
}

int GetRibbonDescGmm(const u8 *a0, u8 ribbon) {
    int ret = sRibbonInfo[ribbon].descGmm;
    if (ret & RIBBON_DESC_SPECIAL_MASK) {
        ret = msg_0424_00146 + a0[((ret & RIBBON_DESC_ID_MASK) >> RIBBON_DESC_ID_SHIFT)];
    }
    return ret;
}

u8 GetSpecialRibbonNo(u8 ribbon) {
    int ret = sRibbonInfo[ribbon].descGmm;
    if (ret & RIBBON_DESC_SPECIAL_MASK) {
        return (ret & RIBBON_DESC_ID_MASK) >> RIBBON_DESC_ID_SHIFT;
    } else {
        return 0xFF;
    }
}
