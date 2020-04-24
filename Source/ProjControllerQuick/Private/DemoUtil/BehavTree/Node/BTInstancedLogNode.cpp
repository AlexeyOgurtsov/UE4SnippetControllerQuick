#include "BTInstancedLogNode.h"
#include "Util/Core/LogUtilLib.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

// TODO
// Memory test:
// 1. Try to access special memory in the derived class

UBTInstancedLogNode::UBTInstancedLogNode()
{
	NodeName = TEXT("BTInstancedLogNode");

	bCreateNodeInstance = true;
}

// ~UBTNode Begin
/** initialize any asset related data */
void UBTInstancedLogNode::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);	
}

/** initialize memory block */
void UBTInstancedLogNode::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory, const EBTMemoryInit::Type InitType) const
{
	const auto MyMem = CastInstanceNodeMemory<FBTInstancedLogNodeMemory>(NodeMemory);	

	Super::InitializeMemory(OwnerComp, NodeMemory, InitType);
	ensureMsgf(MyMem->MemSignature == INSTANCED_LOG_NODE_MEM_SIGNATURE, TEXT("Instance memory signature mismatch"));

	MyMem->InstancedLogPrefix = FString::Printf(TEXT("%s"), *LogPrefix);
	M_LOG(TEXT("%s: %s"), *MyMem->InstancedLogPrefix, TEXT(__FUNCTION__));
}

/** cleanup memory block */
void UBTInstancedLogNode::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory, const EBTMemoryClear::Type InitType) const
{
	const auto MyMem = CastInstanceNodeMemory<FBTInstancedLogNodeMemory>(NodeMemory);
	M_LOG(TEXT("%s: %s; RunDesc={%s}"), *MyMem->InstancedLogPrefix, TEXT(__FUNCTION__), *GetRuntimeDescription(OwnerComp, NodeMemory, EBTDescriptionVerbosity::Type::Basic));
	Super::CleanupMemory(OwnerComp, NodeMemory, InitType);
}

/** gathers description of all runtime parameters */
void UBTInstancedLogNode::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory, const EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	const auto MyMem = CastInstanceNodeMemory<FBTInstancedLogNodeMemory>(NodeMemory);

	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
	Values.Add(FString::Printf(TEXT("InstIdx=%d"), MyMem->MyInstanceIdx));
	Values.Add(FString::Printf(TEXT("InstIdxProp=%d"), MyInstanceIdxProp));
}
	
/** size of instance memory */
uint16 UBTInstancedLogNode::GetInstanceMemorySize() const
{
	return sizeof(FBTInstancedLogNodeMemory);
}


/** called when node instance is added to tree */
void UBTInstancedLogNode::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
}

/** called when node instance is removed from tree */
void UBTInstancedLogNode::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceDestroyed(OwnerComp);
}
// ~UBTNode End
