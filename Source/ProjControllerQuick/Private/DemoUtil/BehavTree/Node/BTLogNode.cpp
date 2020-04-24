#include "BTLogNode.h"
#include "BTNodeUtil.h"
#include "Util\Core\LogUtilLib.h"

#include "BehaviorTree\BehaviorTreeComponent.h"

/**
 * TODO - Instancing demo
 * TODO - Memory demo
 * 1. Memory
 * 2. Special memory
 */

int32 UBTLogNode::NextMyInstanceId = 0;

UBTLogNode::UBTLogNode()
{
	NodeName = TEXT("LogNode");
}

// ~UBTTaskNode Begin
EBTNodeResult::Type UBTLogNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Type::Succeeded;
}
// ~UBTTaskNode End

void UBTLogNode::UBTLogNode::PostInitProperties()
{
	Super::PostInitProperties();	
	LogPrefix = GetLogPrefix();
	M_LOG(TEXT("From node \"%s\": %s"), *LogPrefix, TEXT(__FUNCTION__));
}

// ~UBTNode Begin
/** initialize any asset related data */
void UBTLogNode::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	LogPrefix = GetLogPrefix();
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));
}

FString UBTLogNode::GetLogPrefix() const
{
	return FString::Printf(TEXT("From %s node object \"%s\" with NodeName \"%s\" (InstIdProp=%d)"), *GetName(), *GetClass()->GetName(), *NodeName, MyInstanceIdxProp);
}

/** initialize memory block */
void UBTLogNode::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	Super::InitializeMemory(OwnerComp, NodeMemory, InitType);

	const auto MyMem = CastInstanceNodeMemory<FBTLogNodeMemory>(NodeMemory);	

	LogPrefix = GetLogPrefix();
	MyMem->InstancedLogPrefix = FString::Printf(TEXT("%s; (InstId=%d)"), *LogPrefix, MyMem->MyInstanceIdx);
	M_LOG(TEXT("%s: %s"), *MyMem->InstancedLogPrefix, TEXT(__FUNCTION__));
	LogMemoryInitType(TEXT("InitType"), InitType);
	// @TODO: Log memory init type

	{
		MyMem->MyInstanceIdx = NextMyInstanceId;
		MyInstanceIdxProp = NextMyInstanceId;
		NextMyInstanceId++;
	}
}

/** cleanup memory block */
void UBTLogNode::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type InitType) const
{
	const auto MyMem = CastInstanceNodeMemory<FBTLogNodeMemory>(NodeMemory);
	M_LOG(TEXT("%s: %s; RunDesc={%s}"), *MyMem->InstancedLogPrefix, TEXT(__FUNCTION__), *GetRuntimeDescription(OwnerComp, NodeMemory, EBTDescriptionVerbosity::Type::Basic));
	LogMemoryClearType(TEXT("ClearType"), InitType);
	// @TODO: Log memory clear type
}

/** gathers description of all runtime parameters */
void UBTLogNode::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	const auto MyMem = CastInstanceNodeMemory<FBTLogNodeMemory>(NodeMemory);

	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
	Values.Add(FString::Printf(TEXT("InstIdx=%d"), MyMem->MyInstanceIdx));
	Values.Add(FString::Printf(TEXT("InstIdxProp=%d"), MyInstanceIdxProp));
}

/** size of instance memory */
uint16 UBTLogNode::GetInstanceMemorySize() const
{
	return sizeof(FBTLogNodeMemory);
}

/** called when node instance is added to tree */
void UBTLogNode::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));
	Super::OnInstanceCreated(OwnerComp);
}

/** called when node instance is removed from tree */
void UBTLogNode::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));
	Super::OnInstanceDestroyed(OwnerComp);
}
