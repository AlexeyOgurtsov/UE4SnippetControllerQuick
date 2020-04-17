#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Log.generated.h"

struct FBTLogTaskMemory;

UCLASS()
class UBTTask_Log : public UBTTaskNode
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
	UBTTask_Log();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// ~Memory Begin
	virtual uint16 GetInstanceMemorySize() const override;
	// ~Memory End

	// ~Task Begin
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	// ~Task End

	// ~Messaging Begin
	virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestId, bool bSuccess) override;
	// ~Messaging End

private:
	// ~Tick logging helpers Begin
	void LogTickIfShould(UBehaviorTreeComponent& OwnerComp, FBTLogTaskMemory* NodeMemory);
	
	// ~Tick logging helpers End
	void LogTaskFunc(UBehaviorTreeComponent& OwnerComp, TCHAR* SenderFunction);

	void LogTaskResult(EBTNodeResult::Type TaskResult, TCHAR* SenderFunction);
};
