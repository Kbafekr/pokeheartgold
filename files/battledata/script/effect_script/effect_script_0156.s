    .include "macros/btlcmd.inc"

    .data

_000:
    UpdateMonData OPCODE_FLAG_ON, BATTLER_CATEGORY_ATTACKER, BMON_DATA_STATUS2, STATUS2_DEFENSE_CURL
    UpdateVar OPCODE_SET, BSCRIPT_VAR_SIDE_EFFECT_FLAGS_DIRECT, MOVE_SIDE_EFFECT_TO_ATTACKER|MOVE_SUBSCRIPT_PTR_DEFENSE_UP_1_STAGE
    End 
