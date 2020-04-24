#pragma once

#include "BTService_BBKeyAction.h"
#include "BTService_SetBBNameKey.generated.h"

UCLASS(BlueprintType)
class UBTService_SetBBNameKey : public UBTService_BBKeyAction
{
	GENERATED_BODY()

	UPROPERTY()
	FName NewValue;

public:
	UBTService_SetBBNameKey();

	// ~UBTService_BBKeyAction Begin
	virtual void DoAction(UBehaviorTreeComponent& OwnerNode, uint8* NodeMemory) override;
	// ~UBTService_BBKeyAction End
	
	// ~For xpr Begin
	virtual uint16 GetInstanceMemorySize() const override;
	// ~For xpr end
};
	
