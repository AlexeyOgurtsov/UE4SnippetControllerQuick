#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTLogNode.generated.h"

const FString LOG_NODE_MEM_SIGNATURE = TEXT("LOG_MEM_SIG");

struct FBTLogNodeMemory
{
	FString MemSignature = LOG_NODE_MEM_SIGNATURE;
	int32 MyInstanceIdx = 0;
	FString InstancedLogPrefix;
};

UCLASS(BlueprintType)
class UBTLogNode : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	mutable int32 MyInstanceIdxProp = 0;

	static int32 NextMyInstanceId;

public:
	UBTLogNode();

	virtual void PostInitProperties() override;

	// ~UBTTaskNode Begin
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~UBTTaskNode End

	// ~UBTNode Begin
	/** initialize any asset related data */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	/** initialize memory block */
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	/** cleanup memory block */
	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type InitType) const override;

	/** gathers description of all runtime parameters */
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

	/** size of instance memory */
	virtual uint16 GetInstanceMemorySize() const override;

	/** called when node instance is added to tree */
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

	/** called when node instance is removed from tree */
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
	// ~UBTNode End
	
protected:
	/**
	* Class level log prefix.
	* Generated on Node-level (NOT on instance level!)
	*/
	mutable FString LogPrefix;

private:
	FString GetLogPrefix() const;
};
