#pragma once

#include "Controller/MyAIControllerBase.h"
#include "AITypes.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "MyAIController.generated.h"

/**
* Controller for quick tests
*/

/** ETestMoveToGoalMode*/
UENUM(BlueprintType, Category=Misc)
enum class ETestMoveToGoalMode : uint8
{
	/** RequestMove*/
	RequestMove UMETA(DisplayName="RequestMove")
	
	/** MoveToActor*/
	, MoveToActor UMETA(DisplayName="MoveToActor")

	/** MoveToLocation*/
	, MoveToLocation UMETA(DisplayName="MoveToLocation")
};

UCLASS()
class AMyAIController : public AMyAIControllerBase
{
	GENERATED_BODY()

public:
	AMyAIController();

	virtual void OnPawnBeginPlay(APawn* InPawn) override;

	// ~AActor Begin
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	// ~AActor End

	/** GetActor*/
	UFUNCTION(BlueprintPure, Category=Test)
	AActor* GetActor() const
	{
		return Actor;
	}

	// ~Test Move Functions Begin
	UFUNCTION(BlueprintCallable, Category="Move|Test")
	void MoveToGoal_InMode();

	UFUNCTION(BlueprintCallable, Category="Move|Test")
	void MoveToGoalActor();

	UFUNCTION(BlueprintCallable, Category="Move|Test")
	void MoveToGoalLocation();

	UFUNCTION(BlueprintCallable, Category="Move|Test")
	void RequestMoveToActor();
	// ~Test Move Functions End

	// ~AAIController Begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID InRequestID, const FPathFollowingResult& Result) override;
	// ~AAIController Begin

private:
	AActor* FindGoalActor();

	bool PrepareMoveToGoal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	ETestMoveToGoalMode MoveToGoalMode = ETestMoveToGoalMode::RequestMove;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	float Move_AcceptanceRadius = -1; // Default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	bool bMove_StopOnOverlap = true; // Default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	bool bMove_UsePathfinding = true; // Default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	bool bMove_ProjectDestinationToNavigation = false; // Default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	bool bMove_CanStrafe = true; // Default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	TSubclassOf<UNavigationQueryFilter> Move_FilterClass = nullptr; // Default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	bool bMove_AllowPartialPath = true; // Default

	/** Goal Actor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	AActor* Actor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Test)
	FVector GoalLocation = FVector::ZeroVector;

	/**
	* Id of the last move-to-goal request.
	*/
	UPROPERTY()
	FAIRequestID GoalRequestID = FAIRequestID::InvalidRequest;
};
