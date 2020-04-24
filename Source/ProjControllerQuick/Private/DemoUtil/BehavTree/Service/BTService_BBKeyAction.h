#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_BBKeyAction.generated.h"

UCLASS(BlueprintType)
class UBTService_BBKeyAction : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = Node)
	float ActionDelay = 0.0F;

public:
	UBTService_BBKeyAction();

	virtual void DoAction(UBehaviorTreeComponent& OwnerNode, uint8* NodeMemory);

	// ~UBTNode Begin
	virtual uint16 GetInstanceMemorySize() const override;
	// ~UBTNode End
	
	// ~UAuxiliaryNode Begin
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~UAuxiliaryNode End
	
protected:
	FString LogPrefixString;
};
