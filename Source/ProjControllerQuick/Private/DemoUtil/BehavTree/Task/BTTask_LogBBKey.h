#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_LogBBKey.generated.h"

struct FBTLogBBKeyTaskMemory;

UCLASS(BlueprintType)
class UBTTask_LogBBKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = Node)
	float ExecDuration = 5.0F;

public:
	UBTTask_LogBBKey();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	virtual uint16 GetInstanceMemorySize() const override;

private:
	bool TryLogKeyValue(const TCHAR* Reason, const UBlackboardComponent * BBComp, FBTLogBBKeyTaskMemory* NodeMemory) const;
	bool LogKeyValueAsBool(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsClass(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsEnum(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsFloat(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsInt(const FString& PrefixString, const UBlackboardComponent * BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsName(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsObject(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsRotator(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsString(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const;
	bool LogKeyValueAsVector(const FString& PrefixString, const UBlackboardComponent* BBComp, FBlackboard::FKey KeyID) const;

	EBlackboardNotificationResult OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);

	FDelegateHandle BBKeyChangedDelegateHandle;
};

