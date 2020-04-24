#pragma once

#include "Controller/MyPawnWithAIController.h"
#include "BehaviorTreeControllerConfig.h"
#include "BehaviorTreePawn.generated.h"

class ABehaviorTreeController;

UCLASS()
class ABehaviorTreePawn : public AMyPawnWithAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=BehaviorTree, Meta=(ShowOnlyInnerProperties))
	FBehaviorTreeControllerConfig BTConfig;

public:
	ABehaviorTreePawn();

	virtual void PostInitProperties() override;

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	UFUNCTION(BlueprintPure, Category=Controller)
	ABehaviorTreeController* GetBTController() const;
};
