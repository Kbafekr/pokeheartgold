    .include "macros/btlcmd.inc"

    .data

_000:
    CheckSubstitute BATTLER_CATEGORY_DEFENDER, _022
    CompareMonDataToValue OPCODE_FLAG_SET, BATTLER_CATEGORY_DEFENDER, BMON_DATA_STATUS, STATUS_PARALYSIS, _014
    UpdateVar OPCODE_SET, BSCRIPT_VAR_POWER_MULTI, 10
    GoTo _022

_014:
    UpdateVar OPCODE_SET, BSCRIPT_VAR_POWER_MULTI, 20
    UpdateVar OPCODE_SET, BSCRIPT_VAR_SIDE_EFFECT_FLAGS_INDIRECT, MOVE_SIDE_EFFECT_ON_HIT|MOVE_SUBSCRIPT_PTR_HEAL_TARGET_PARALYSIS

_022:
    CalcCrit 
    CalcDamage 
    End 
