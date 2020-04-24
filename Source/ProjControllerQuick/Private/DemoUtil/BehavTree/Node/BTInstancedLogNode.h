#pragma once

#include "BTLogNode.h"
#include "BTInstancedLogNode.generated.h"

const FString INSTANCED_LOG_NODE_MEM_SIGNATURE = TEXT("INSTANCED_LOG_MEM_SIG");

struct FBTInstancedLogNodeMemory : public FBTLogNodeMemory
{
	FString MemSignature = INSTANCED_LOG_NODE_MEM_SIGNATURE;
};

UCLASS(BlueprintType)
class UBTInstancedLogNode : public UBTLogNode
{
	GENERATED_BODY()

public:
	UBTInstancedLogNode();

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
};
