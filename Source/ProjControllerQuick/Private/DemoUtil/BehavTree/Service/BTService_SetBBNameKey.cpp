#pragma once

#include "BTService_SetBBNameKey.h"
#include "Util\Core\LogUtilLib.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

static const FString TEST_STRING_REF_VALUE = "TEST_STRING";
struct FSetBBNameKeyNodeMemory
{
	// For test
	FString TestString = TEST_STRING_REF_VALUE;
};

UBTService_SetBBNameKey::UBTService_SetBBNameKey()
{
	NodeName = "SetBBNameKeyService";
}

// ~UBTService_BBKeyAction Begin
void UBTService_SetBBNameKey::DoAction(UBehaviorTreeComponent& OwnerNode, uint8* const NodeMemory)
{
	UBlackboardComponent* const BBComp = OwnerNode.GetBlackboardComponent();
	const auto MyMem = CastInstanceNodeMemory<FSetBBNameKeyNodeMemory>(NodeMemory);

	verifyf(MyMem->TestString == TEST_STRING_REF_VALUE, TEXT("CastInstanceNodeMemory of derived experiment failure!"));

	{
		const FBlackboard::FKey KeyID = BlackboardKey.GetSelectedKeyID();
		if( ! BBComp->IsValidKey(KeyID) )
		{
			M_LOG_ERROR(TEXT("%s: unable to set name key: IsValidKey returns false"), *LogPrefixString);
			return;
		}
		if( ! BlackboardKey.IsSet() )
		{
			M_LOG_ERROR(TEXT("%s: unable to set name key: key is NOT set"), *LogPrefixString);
			return;
		}

		{
			M_LOG(TEXT("%s: Setting name key \"%s\" to value \"%s\""), *LogPrefixString, *GetSelectedBlackboardKey().ToString(), *NewValue.ToString());
			BBComp->SetValueAsName(GetSelectedBlackboardKey(), NewValue);
		}
	}
}

uint16 UBTService_SetBBNameKey::GetInstanceMemorySize() const
{
	return sizeof(FSetBBNameKeyNodeMemory);
}
// ~UBTService_BBKeyAction End
