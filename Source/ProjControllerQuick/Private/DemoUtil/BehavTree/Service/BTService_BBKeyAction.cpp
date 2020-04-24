#include "BTService_BBKeyAction.h"
#include "Util\Core\LogUtilLib.h"

struct FBTBBKeyActionServiceMemory
{
	float ElapsedTime = 0.0F;

	void Reset()
	{
		ElapsedTime = 0.0F;
	}
};

UBTService_BBKeyAction::UBTService_BBKeyAction()
{
	NodeName = "BBKeyActionService";

	bNotifyTick = true; // Q. Is it abount TickNode?
	bNotifyCeaseRelevant = true;
	bNotifyBecomeRelevant = true;

	LogPrefixString = FString::Printf(TEXT("Service node \"%s\""), *NodeName);
}
void UBTService_BBKeyAction::DoAction(UBehaviorTreeComponent& OwnerNode, uint8* NodeMemory)
{
	// Empty body
}

// ~UBTAuxiliaryNode Begin
void UBTService_BBKeyAction::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* const NodeMemory, const float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const auto MyMem = CastInstanceNodeMemory<FBTBBKeyActionServiceMemory>(NodeMemory);
	MyMem->ElapsedTime += DeltaSeconds;

	if(MyMem->ElapsedTime >= ActionDelay)
	{
		M_LOG(TEXT("%s: Performing action - time is come (ElapsedTime = %f)"), *LogPrefixString, MyMem->ElapsedTime);
		DoAction(OwnerComp, NodeMemory);
	}
}

void UBTService_BBKeyAction::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	const auto MyMem = CastInstanceNodeMemory<FBTBBKeyActionServiceMemory>(NodeMemory);
	M_LOG(TEXT("%s: %s"), *LogPrefixString, TEXT(__FUNCTION__));
	MyMem->Reset();
}

void UBTService_BBKeyAction::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	M_LOG(TEXT("%s: %s"), *LogPrefixString, TEXT(__FUNCTION__));
}
// ~UBTAuxiliaryNode End

// ~UBTNode Begin
uint16 UBTService_BBKeyAction::GetInstanceMemorySize() const
{
	return sizeof(FBTBBKeyActionServiceMemory);
}
// ~UBTNode End
