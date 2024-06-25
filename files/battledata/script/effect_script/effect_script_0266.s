    .include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_FLAG_SET, BSCRIPT_VAR_SIDE_CONDITION_TARGET, SIDE_CONDITION_STEALTH_ROCKS, _017
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_SIDE_CONDITION_TARGET, SIDE_CONDITION_STEALTH_ROCKS
    // Pointed stones float in the air around your team!
    BufferMessage msg_0197_01077, TAG_NONE_SIDE, BATTLER_CATEGORY_ATTACKER_ENEMY
    UpdateVar OPCODE_SET, BSCRIPT_VAR_SIDE_EFFECT_FLAGS_INDIRECT, MOVE_SIDE_EFFECT_ON_HIT|MOVE_SUBSCRIPT_PTR_PRINT_MESSAGE_AND_PLAY_ANIMATION
    End 

_017:
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End 
