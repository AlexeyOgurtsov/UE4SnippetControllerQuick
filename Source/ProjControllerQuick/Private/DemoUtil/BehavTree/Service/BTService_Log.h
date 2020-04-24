#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_Log.generated.h"

// Q1: How to finish service execution?

struct FBTLogServiceNodeMemory;

UCLASS(BlueprintType)
class UBTService_Log : public UBTService
{
	GENERATED_BODY()


	// ~Tick logging props Begin
	UPROPERTY(Category = Node, EditAnywhere)
	uint32 bEnableTickLogging : 1;

	UPROPERTY(Category = Node, EditAnywhere)
	int32 LogTickPeriod;

	/**
	* Count of logs of the tick (if zero, then log EVERY tick).
	*/
	UPROPERTY(Category = Node, EditAnywhere)
	int32 MaxLogTickLogs;
	// ~Tick logging props End
	
	// ~Operation props Begin
	/**
	* Maximum duration of task in seconds.
	* Zero means ONE TICK ONLY!
	*/
	UPROPERTY(Category = Node, EditAnywhere)
	float DurationInSeconds;
	// ~Operation props End

public:
	UBTService_Log();

	virtual void PostInitProperties();

	/** called when node instance is added to tree */
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	/** called when node instance is removed from tree */
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	virtual uint16 GetInstanceMemorySize() const override;

private:
	FString LogPrefixString;
};
