    .include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_FLAG_SET, BSCRIPT_VAR_MOVE_STATUS_FLAGS, MOVE_STATUS_SEMI_INVULNERABLE, _074
    CheckIgnorableAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_DEFENDER, ABILITY_SUCTION_CUPS, _079
    CompareMonDataToValue OPCODE_EQU, BATTLER_CATEGORY_DEFENDER, BMON_DATA_MOVE_EFFECT, MOVE_EFFECT_FLAG_INGRAIN, _086
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_BATTLE_TYPE, BATTLE_TYPE_DOUBLES|BATTLE_TYPE_MULTI|BATTLE_TYPE_AI, _074
    TryWhirlwind _074
    Call BATTLE_SUBSCRIPT_ATTACK_MESSAGE_AND_ANIMATION
    TryRestoreStatusOnSwitch BATTLER_CATEGORY_DEFENDER, _032
    UpdateMonData OPCODE_SET, BATTLER_CATEGORY_DEFENDER, BMON_DATA_STATUS, STATUS_NONE

_032:
    DeletePokemon BATTLER_CATEGORY_DEFENDER
    Wait 
    CompareVarToValue OPCODE_FLAG_NOT, BSCRIPT_VAR_BATTLE_TYPE, BATTLE_TYPE_TRAINER, _067
    HealthbarSlideOut BATTLER_CATEGORY_DEFENDER
    Wait 
    SwitchAndUpdateMon BATTLER_CATEGORY_FORCED_OUT
    Wait 
    PokemonSendOut BATTLER_CATEGORY_DEFENDER
    WaitTime 72
    HealthbarSlideIn BATTLER_CATEGORY_DEFENDER
    Wait 
    // {0} was dragged out!
    PrintMessage msg_0197_00603, TAG_NICKNAME, BATTLER_CATEGORY_DEFENDER
    Wait 
    WaitButtonABTime 30
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_BATTLER_SWITCH, BSCRIPT_VAR_BATTLER_TARGET
    Call BATTLE_SUBSCRIPT_HAZARDS_CHECK
    End 

_067:
    FadeOutBattle 
    Wait 
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_BATTLE_OUTCOME, BATTLE_RESULT_PLAYER_FLED
    End 

_074:
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End 

_079:
    // {0} anchors itself with {1}!
    BufferMessage msg_0197_00659, TAG_NICKNAME_ABILITY, BATTLER_CATEGORY_DEFENDER, BATTLER_CATEGORY_DEFENDER
    GoTo _090

_086:
    // {0} anchored itself with its roots!
    BufferMessage msg_0197_00542, TAG_NICKNAME, BATTLER_CATEGORY_DEFENDER

_090:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 30
    PrintBufferedMessage 
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End 
