#include <script.h>
#include <item.h>
#include "../../checkIds/base.h"

typedef void (*ScriptCommand)(Entity*, ScriptExecutionContext*);
extern void ScriptCommandNop(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_BeginBlock(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_EndBlock(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_Jump(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpIf(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpIfNot(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpTable(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpAbsolute(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpAbsoluteIf(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpAbsoluteIfNot(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_JumpAbsoluteTable(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_Call(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CallWithArg(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_LoadRoomEntityList(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckSyncFlagAndClear(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckInventory1(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckInventory2(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckLocalFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckLocalFlagByBank(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckGlobalFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckRoomFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckPlayerInRegion(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckPlayerInRegion2(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckEntityInteractType(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_FacePlayerAndCheckDist(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_HasRupees(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_HasShells(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckTextboxResult(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckKinstoneFused(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_BuyItem(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckBottleContaining(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_HasRoomItemForSale(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_VariableBitSet(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_VariableOnlyBitSet(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_VariableEqual(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckPlayerFlags(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CheckPlayerMinish(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_EntityHasHeight(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ComparePlayerAction(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ComparePlayerAnimationState(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetSyncFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ClearSyncFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetLocalFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetLocalFlagByBank(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ClearLocalFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetGlobalFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ClearGlobalFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetRoomFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ClearRoomFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_Wait(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitForSyncFlag(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitForSyncFlagAndClear(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitPlayerGetItem(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitForPlayerEnterRoom(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitFor_1(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitForFadeFinish(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFadeTime(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFadeMask(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_FadeInvert(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommandNop2(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFade4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFade5(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFade6(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFade7(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFadeIris(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetFadeIrisInOut(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E858(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetPlayerIdle(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_EnablePlayerControl(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_DisablePlayerControl(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetPlayerAction(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_StartPlayerScript(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetPlayerAnimation(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E8E4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetAction(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetIntVariable(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetVariableToFrame(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetAnimation(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_TriggerInteract(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E974(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E9D4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E9DC(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E9E4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807E9F0(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EA4C(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EA88(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WaitUntilTextboxCloses(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_MessageFromTarget(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_MessageNoOverlap(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_MessageFromTargetPos(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_MessageFromTargetTable(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_MessageNoOverlapVar(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_EzloMessage(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EB38(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetAnimationState(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EB4C(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_FacePlayer(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_FaceAwayFromPlayer(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetEntityDirection(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetEntityDirectionWithAnimationState(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetEntitySpeed(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetEntityVelocity(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetEntityPositionRelative(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_OffsetEntityPosition(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_MoveEntityToPlayer(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommandNop3(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WalkForward(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WalkNorth(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WalkEast(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WalkSouth(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_WalkWest(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807ED24(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EDD4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EE04(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EE30(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EEB4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EEF4(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807EF3C(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_DoPostScriptAction(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_DoPostScriptAction2(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_PlaySound(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_PlayBgm(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SoundReq(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_StopBgm(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ModRupees(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_ModHealth(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_IncreaseMaxHealth(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_GivePlayerItem(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_GiveKinstone(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_GetInventoryValue(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetInventoryValue(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_InitItemGetSequence(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CameraTargetEntity(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_CameraTargetPlayer(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_SetScrollSpeed(Entity* entity, ScriptExecutionContext* context);
extern void ScriptCommand_0807F0C8(Entity* entity, ScriptExecutionContext* context);
// custom
void ScriptCommand_JumpAbsoluteUninterruptible(Entity* entity, ScriptExecutionContext* context) {
    (void) entity;
    context->scriptInstructionPointer =
        (u16*)GetNextScriptCommandWordAfterCommandMetadata(context->scriptInstructionPointer);
    gActiveScriptInfo.commandSize = 0;
    gActiveScriptInfo.flags |= 1;
}

void ScriptCommand_GiveItemForFlag(Entity* entity, ScriptExecutionContext* context)
{
    (void) entity;
    int flag = context->scriptInstructionPointer[1];
    int item = context->scriptInstructionPointer[2];
    item = get_item_for_global_flag_with_default(flag, item);
    InitItemGetSequence(get_item_id(item), get_item_subvalue(item), 0);
}

void ExecuteScript(Entity* entity, ScriptExecutionContext* context) {
    static const ScriptCommand gScriptCommands[] = {
        ScriptCommandNop,
        ScriptCommand_BeginBlock,
        ScriptCommand_EndBlock,
        ScriptCommand_Jump,
        ScriptCommand_JumpIf,
        ScriptCommand_JumpIfNot,
        ScriptCommand_JumpTable,
        ScriptCommand_JumpAbsolute,
        ScriptCommand_JumpAbsoluteIf,
        ScriptCommand_JumpAbsoluteIfNot,
        ScriptCommand_JumpAbsoluteTable,
        ScriptCommand_Call,
        ScriptCommand_CallWithArg,
        ScriptCommand_LoadRoomEntityList,
        ScriptCommand_CheckSyncFlagAndClear,
        ScriptCommand_CheckInventory1,
        ScriptCommand_CheckInventory2,
        ScriptCommand_HasRoomItemForSale,
        ScriptCommand_CheckLocalFlag,
        ScriptCommand_CheckLocalFlagByBank,
        ScriptCommand_CheckGlobalFlag,
        ScriptCommand_CheckRoomFlag,
        ScriptCommand_CheckPlayerInRegion,
        ScriptCommand_CheckPlayerInRegion2,
        ScriptCommand_CheckEntityInteractType,
        ScriptCommand_FacePlayerAndCheckDist,
        ScriptCommand_HasRupees,
        ScriptCommand_HasShells,
        ScriptCommand_CheckTextboxResult,
        ScriptCommand_CheckKinstoneFused,
        ScriptCommand_BuyItem,
        ScriptCommand_CheckBottleContaining,
        ScriptCommand_VariableBitSet,
        ScriptCommand_VariableOnlyBitSet,
        ScriptCommand_VariableEqual,
        ScriptCommand_CheckPlayerFlags,
        ScriptCommand_CheckPlayerMinish,
        ScriptCommand_EntityHasHeight,
        ScriptCommand_ComparePlayerAction,
        ScriptCommand_ComparePlayerAnimationState,
        ScriptCommand_SetSyncFlag,
        ScriptCommand_ClearSyncFlag,
        ScriptCommand_SetLocalFlag,
        ScriptCommand_SetLocalFlagByBank,
        ScriptCommand_ClearLocalFlag,
        ScriptCommand_SetGlobalFlag,
        ScriptCommand_ClearGlobalFlag,
        ScriptCommand_SetRoomFlag,
        ScriptCommand_ClearRoomFlag,
        ScriptCommand_Wait,
        ScriptCommand_WaitForSyncFlag,
        ScriptCommand_WaitForSyncFlagAndClear,
        ScriptCommand_WaitPlayerGetItem,
        ScriptCommand_WaitForPlayerEnterRoom,
        ScriptCommand_WaitFor_1,
        ScriptCommand_WaitForFadeFinish,
        ScriptCommand_SetFadeTime,
        ScriptCommand_SetFadeMask,
        ScriptCommand_FadeInvert,
        ScriptCommandNop2,
        ScriptCommand_SetFade4,
        ScriptCommand_SetFade5,
        ScriptCommand_SetFade6,
        ScriptCommand_SetFade7,
        ScriptCommand_SetFadeIris,
        ScriptCommand_SetFadeIrisInOut,
        ScriptCommand_0807E858,
        ScriptCommand_SetPlayerIdle,
        ScriptCommand_EnablePlayerControl,
        ScriptCommand_DisablePlayerControl,
        ScriptCommand_SetPlayerAction,
        ScriptCommand_StartPlayerScript,
        ScriptCommand_SetPlayerAnimation,
        ScriptCommand_0807E8E4,
        ScriptCommand_0807E8E4,
        ScriptCommand_0807E8E4,
        ScriptCommand_0807E8E4,
        ScriptCommand_SetAction,
        ScriptCommand_SetIntVariable,
        ScriptCommand_SetVariableToFrame,
        ScriptCommand_SetAnimation,
        ScriptCommand_TriggerInteract,
        ScriptCommand_0807E974,
        ScriptCommand_0807E9D4,
        ScriptCommand_0807E9DC,
        ScriptCommand_0807E9E4,
        ScriptCommand_0807E9F0,
        ScriptCommand_0807EA4C,
        ScriptCommand_0807EA88,
        ScriptCommand_WaitUntilTextboxCloses,
        ScriptCommand_MessageFromTarget,
        ScriptCommand_MessageNoOverlap,
        ScriptCommand_MessageFromTargetPos,
        ScriptCommand_MessageFromTargetTable,
        ScriptCommand_MessageNoOverlapVar,
        ScriptCommand_EzloMessage,
        ScriptCommand_0807EB38,
        ScriptCommand_SetAnimationState,
        ScriptCommand_0807EB4C,
        ScriptCommand_FacePlayer,
        ScriptCommand_FaceAwayFromPlayer,
        ScriptCommand_SetEntityDirection,
        ScriptCommand_SetEntityDirectionWithAnimationState,
        ScriptCommand_SetEntitySpeed,
        ScriptCommand_SetEntityVelocity,
        ScriptCommand_SetEntityPositionRelative,
        ScriptCommand_OffsetEntityPosition,
        ScriptCommand_MoveEntityToPlayer,
        ScriptCommandNop3,
        ScriptCommand_WalkForward,
        ScriptCommand_WalkNorth,
        ScriptCommand_WalkEast,
        ScriptCommand_WalkSouth,
        ScriptCommand_WalkWest,
        ScriptCommand_0807ED24,
        ScriptCommand_0807EDD4,
        ScriptCommand_0807EE04,
        ScriptCommand_0807EE30,
        ScriptCommand_0807EEB4,
        ScriptCommand_0807EEF4,
        ScriptCommand_0807EF3C,
        ScriptCommand_DoPostScriptAction,
        ScriptCommand_DoPostScriptAction2,
        ScriptCommand_PlaySound,
        ScriptCommand_PlayBgm,
        ScriptCommand_SoundReq,
        ScriptCommand_StopBgm,
        ScriptCommand_ModRupees,
        ScriptCommand_ModHealth,
        ScriptCommand_IncreaseMaxHealth,
        ScriptCommand_GivePlayerItem,
        ScriptCommand_GiveKinstone,
        ScriptCommand_GetInventoryValue,
        ScriptCommand_SetInventoryValue,
        ScriptCommand_InitItemGetSequence,
        ScriptCommand_CameraTargetEntity,
        ScriptCommand_CameraTargetPlayer,
        ScriptCommand_SetScrollSpeed,
        ScriptCommand_0807F0C8,
        // custom
        /* 0x8b */ ScriptCommand_JumpAbsoluteUninterruptible,
        /* 0x8c */ ScriptCommand_GiveItemForFlag,
    };

    if (!context->scriptInstructionPointer)
        return;
    if (context->wait) {
        context->wait--;
    } else {
        ActiveScriptInfo* activeScriptInfo = &gActiveScriptInfo;
        activeScriptInfo->flags = 0;
        do {
            u32 cmd = GetNextScriptCommandHalfword(context->scriptInstructionPointer);
            u16* lastInstruction;
            if (cmd == 0xFFFF)
                return;
            activeScriptInfo->commandSize = cmd >> 0xA;
            activeScriptInfo->commandIndex = cmd & 0x3FF;
            lastInstruction = context->scriptInstructionPointer;
            activeScriptInfo->flags &= ~1;
            gScriptCommands[activeScriptInfo->commandIndex](entity, context);
            context->scriptInstructionPointer += activeScriptInfo->commandSize;
            if (lastInstruction != context->scriptInstructionPointer) {
                context->unk_18 = 0;
            }
        } while (activeScriptInfo->flags & 3);
    }
}
