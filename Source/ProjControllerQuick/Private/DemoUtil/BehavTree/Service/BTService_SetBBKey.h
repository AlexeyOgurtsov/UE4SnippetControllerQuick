#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_SetBBKey.generated.h"

UCLASS(BlueprintType)
class UBTService_SetBBKey : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetBBKey();

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
