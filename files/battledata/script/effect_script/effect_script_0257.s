    .include "macros/btlcmd.inc"

    .data

_000:
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_BATTLE_STATUS, BATTLE_STATUS_HIT_DIVE
    UpdateVar OPCODE_SET, BSCRIPT_VAR_POWER_MULTI, 10
    CompareMonDataToValue OPCODE_FLAG_NOT, BATTLER_CATEGORY_DEFENDER, BMON_DATA_MOVE_EFFECT, MOVE_EFFECT_FLAG_DIVE, _017
    UpdateVar OPCODE_SET, BSCRIPT_VAR_POWER_MULTI, 20

_017:
    CalcCrit 
    CalcDamage 
    End 
