#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetBBKey.generated.h"

UCLASS(BlueprintType)
class UBTTask_SetBBKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditInstanceOnly, Category=Node)
	FName NewNameValue = "NEW_KEY_VALUE";
};

