#pragma once

#include "Controller/MyAIControllerBase.h"
#include "BehavTreeController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

class UBehaviorTree;
class UBlackboardData;

UCLASS(BlueprintType)
class ABehavTreeController : public AMyAIControllerBase
{
	GENERATED_BODY()

public:
	ABehavTreeController();

	virtual void BeginPlay() override;	
	virtual void OnPossess(APawn* NewPawn) override;
	
	/** GetBlackboardComponent*/
	UFUNCTION(BlueprintPure, Category=BehavTreeDemo)
	UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
	/** GetBehavTreeComponent*/
	UFUNCTION(BlueprintPure, Category=BehavTreeDemo)
	UBehaviorTreeComponent* GetBehavTreeComponent() const { return BehavTreeComponent; }
	
private:
	void LoadBlackboardComponentAtCtor();
	void InitBlackboardComponent();

	/** BlackboardComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UBlackboardComponent* BlackboardComponent = nullptr;

	/** Test blackboard data*/
	UPROPERTY()
	UBlackboardData* TestBlackboardData = nullptr;

	void InitBehavTree();	
	void LoadBehavTreeAtCtor();

	/** BehavTreeComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UBehaviorTreeComponent* BehavTreeComponent = nullptr;

	/** Test bevahior tree*/
	UPROPERTY()
	UBehaviorTree* TestBehavTree = nullptr;	

private:
	void OnWePossessedAndStartedToPlay();
	bool bBeginPlayStarted = false;
};
