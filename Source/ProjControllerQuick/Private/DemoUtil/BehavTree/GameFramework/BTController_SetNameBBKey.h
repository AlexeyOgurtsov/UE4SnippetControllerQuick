#pragma once

#include "BehaviorTreeController.h"
#include "DemoUtil\BehavTree\MyBehaviorTreeHelperTypes.h"
#include "BTController_SetNameBBKey.generated.h"

UCLASS(BlueprintType)
class ABTController_SetNameBBKey : public ABehaviorTreeController
{
	GENERATED_BODY()

	// ~Action Begin
	UPROPERTY(EditAnywhere, Category=Blackboard)
	float ActionDelay = 3.0F;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	int32 NumActionCalls = 1;
	// ~Action End

	// ~Blackboard key Begin
	UPROPERTY(EditAnywhere, Category=Blackboard)
	EBBKeyIdentMode KeyIdentMode = EBBKeyIdentMode::Name;

	/** get name of selected blackboard key */
	FName GetSelectedBlackboardKey() const;
	FBlackboard::FKey GetSelectedBlackboardKeyID() const; 

	/** blackboard key selector 
	 * WARNING!!! Can NOT select blackboard key using the selector 
	 * in the AI Controller blueprint (by default, at least)!!!
	 **/
	UPROPERTY(EditAnywhere, Category=Blackboard, Meta=(EditCondition="KeyIdentMode == EBBKeyIdentMode::Selector"))
	FBlackboardKeySelector BlackboardKey;

	/** blackboard key name */
	UPROPERTY(EditAnywhere, Category=Blackboard, Meta=(EditCondition="KeyIdentMode == EBBKeyIdentMode::Name"))
	FName BlackboardKeyName;

	UPROPERTY(EditAnywhere, Category=Blackboard)
	FName NewValue = TEXT("NEW_VALUE");
	// ~Blackboard key End

public:
	ABTController_SetNameBBKey();

	// ~UObject Begin
	virtual void PostInitProperties() override;

	virtual void Tick(float DeltaSeconds) override;
	// ~UObject End
	
private:
	// ~Time Begin
	float TimeSinceLastActionCall = 0.0F;
	// ~Time End

	// ~Blackboard key Begin
	void DoSetKey();
	// ~Blackboard key End
	
	int32 ActionCallIndex = 0;
};
