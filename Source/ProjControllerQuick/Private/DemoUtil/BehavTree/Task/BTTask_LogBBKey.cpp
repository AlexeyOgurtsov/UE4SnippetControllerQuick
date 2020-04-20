#include "BTTask_LogBBKey.h"
#include "Util/Core/LogUtilLib.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_NativeEnum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

struct FBTLogBBKeyTaskMemory
{
	FString LogPrefixString = "";
	float ElapsedTimeInSeconds = 0.0F;

	void Reset(const UBTTask_LogBBKey* InNode)
	{
		LogPrefixString = FString::Printf(TEXT("From node \"%s\": "), *InNode->GetNodeName());
		ElapsedTimeInSeconds = 0.0F;
	}
};

UBTTask_LogBBKey::UBTTask_LogBBKey()
{
	NodeName = "LogBBKey";

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_LogBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory)
{
	UBlackboardComponent* const BBComp = OwnerComp.GetBlackboardComponent();
	const auto MyMem = CastInstanceNodeMemory<FBTLogBBKeyTaskMemory>(NodeMemory);
	// WARNING!!! We must reset the memory content ever BEFORE logging
	MyMem->Reset(this);

	M_LOG(TEXT("%s: Task executed"), *MyMem->LogPrefixString);	

	if (BBComp)
	{
		BBKeyChangedDelegateHandle = BBComp->RegisterObserver(BlackboardKey.GetSelectedKeyID(), this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTTask_LogBBKey::OnBlackboardValueChange));
	}
	const bool bSucceeded = TryLogKeyValue(TEXT(__FUNCTION__), BBComp, MyMem);
	return EBTNodeResult::Type::InProgress;
}

void UBTTask_LogBBKey::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory, const float DeltaSeconds)
{
	UBlackboardComponent* const BBComp = OwnerComp.GetBlackboardComponent();
	const auto MyMem = CastInstanceNodeMemory<FBTLogBBKeyTaskMemory>(NodeMemory);

	MyMem->ElapsedTimeInSeconds += DeltaSeconds;
	if (MyMem->ElapsedTimeInSeconds >= ExecDuration)
	{
		M_LOG(TEXT("%s: Stopping execution because of time expire"), *MyMem->LogPrefixString);
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}

void UBTTask_LogBBKey::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory, EBTNodeResult::Type const TaskResult)
{
	const auto MyMem = CastInstanceNodeMemory<FBTLogBBKeyTaskMemory>(NodeMemory);

	M_LOG(TEXT("%s: task is finished"), *MyMem->LogPrefixString);
	if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
	{
		BBComp->UnregisterObserver(BlackboardKey.GetSelectedKeyID(), BBKeyChangedDelegateHandle);
	}
}

uint16 UBTTask_LogBBKey::GetInstanceMemorySize() const
{
	return sizeof(FBTLogBBKeyTaskMemory);
}

bool UBTTask_LogBBKey::TryLogKeyValue(const TCHAR* Reason, const UBlackboardComponent* BBComp, FBTLogBBKeyTaskMemory* NodeMemory) const
{
	M_LOG(TEXT("%s: Logging key, REASON: %s"), *NodeMemory->LogPrefixString, Reason);

	if(BBComp == nullptr)
	{
		M_LOG_ERROR(TEXT("%s: Unable to log the key - Blackboard component NOT found"), *NodeMemory->LogPrefixString);
		return false;
	}
	const FBlackboard::FKey KeyID = BlackboardKey.GetSelectedKeyID();
	if( ! BBComp->IsValidKey(KeyID) )
	{
		M_LOG_ERROR(TEXT("%s: Unable to log the key - blackboard key is invalid"), *NodeMemory->LogPrefixString);
		return false;
	}

	if ( ! BlackboardKey.IsSet() )
	{
		M_LOG_ERROR(TEXT("%s: Unable to log the key - blackboard key is NOT set"), *NodeMemory->LogPrefixString);		
		return false;
	}

	const FString KeyTypeName = (BlackboardKey.SelectedKeyType != nullptr) ? BlackboardKey.SelectedKeyType->GetName() : FString("nullptr");
	const FString KeyName = *GetSelectedBlackboardKey().ToString();
	M_LOG(TEXT("%s: Logging BBKey named \"%s\" (ID=%d) of type \"%s\""), *NodeMemory->LogPrefixString, *KeyName, KeyID, *KeyTypeName);

	{
		const FString KeyValueDesc = BBComp->DescribeKeyValue(KeyID, EBlackboardDescription::Type::Full);		
		M_LOG(TEXT("%s: BB Key %s result: %s"), *NodeMemory->LogPrefixString, TEXT("Name"), *KeyValueDesc);
	}

	const FString PrefixString = FString::Printf(TEXT("BB key \"%s\""), *KeyName);
	if(LogKeyValueAsBool(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsClass(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsEnum(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsFloat(PrefixString, BBComp, KeyID) 
		|| LogKeyValueAsInt(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsFloat(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsName(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsObject(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsRotator(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsString(PrefixString, BBComp, KeyID)
		|| LogKeyValueAsVector(PrefixString, BBComp, KeyID)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBTTask_LogBBKey::LogKeyValueAsBool(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const
{
	if(BBComp->IsKeyOfType<UBlackboardKeyType_Bool>(KeyID))
	{
		const bool bValue = BBComp->GetValue<UBlackboardKeyType_Bool>(KeyID);
		ULogUtilLib::LogYesNo(PrefixString, bValue);
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsClass(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Class>(KeyID))
	{
		const UClass* Class = BBComp->GetValue<UBlackboardKeyType_Class>(KeyID);
		ULogUtilLib::LogString(PrefixString, Class ? Class->GetClass()->GetName() : FString(TEXT("None")));
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsEnum(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Enum>(KeyID))
	{
		uint8 EnumIndex = BBComp->GetValueAsEnum(BBComp->GetKeyName(KeyID));
		M_LOG(TEXT("%s: EnumIndex=%d"), *PrefixString, EnumIndex);
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsFloat(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Float>(KeyID))
	{
		const float Value = BBComp->GetValue<UBlackboardKeyType_Float>(KeyID);
		ULogUtilLib::LogFloat(PrefixString, Value);
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsInt(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Int>(KeyID))
	{
		const int32 Value = BBComp->GetValue<UBlackboardKeyType_Int>(KeyID);
		ULogUtilLib::LogInt32(PrefixString, Value);
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsName(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Name>(KeyID))
	{
		const FName Value = BBComp->GetValue<UBlackboardKeyType_Name>(KeyID);
		ULogUtilLib::LogName(PrefixString, Value);
		return true;
	}
	return false;	
}

bool UBTTask_LogBBKey::LogKeyValueAsObject(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Object>(KeyID))
	{
		const UObject* Object = BBComp->GetValue<UBlackboardKeyType_Object>(KeyID);
		M_LOG(TEXT("%s: object %s"), *PrefixString, *ULogUtilLib::GetNameAndClassSafe(Object));
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsRotator(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Rotator>(KeyID))
	{
		const FRotator Value = BBComp->GetValue<UBlackboardKeyType_Rotator>(KeyID);
		ULogUtilLib::LogRotator(PrefixString, Value);
		return true;
	}	
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsString(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_String>(KeyID))
	{
		const FString Value = BBComp->GetValue<UBlackboardKeyType_String>(KeyID);
		ULogUtilLib::LogString(PrefixString, Value);
		return true;
	}
	return false;
}

bool UBTTask_LogBBKey::LogKeyValueAsVector(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const
{
	if (BBComp->IsKeyOfType<UBlackboardKeyType_Vector>(KeyID))
	{
		const FVector Value = BBComp->GetValue<UBlackboardKeyType_Vector>(KeyID);
		ULogUtilLib::LogVector(PrefixString, Value);
		return true;
	}
	return false;
}

EBlackboardNotificationResult UBTTask_LogBBKey::OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	const auto BBComp = Cast<UBehaviorTreeComponent>(Blackboard.GetBrainComponent());
	if (BBComp == nullptr)
	{
		M_LOG(TEXT("BehaviorTreeComponent no longer exist, so we should remove the blackboard value change observer"));
		return EBlackboardNotificationResult::RemoveObserver;
	}
	const auto MyMem = CastInstanceNodeMemory<FBTLogBBKeyTaskMemory>(BBComp->GetNodeMemory(this, BBComp->FindInstanceContainingNode(this)));

	TryLogKeyValue(TEXT("Key changed"), &Blackboard, MyMem);
	return EBlackboardNotificationResult::ContinueObserving;
}
