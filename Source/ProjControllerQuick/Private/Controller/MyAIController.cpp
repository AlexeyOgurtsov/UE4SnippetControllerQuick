#include "MyAIController.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/Core/AI/AIUtil.h"

#include "Kismet/GameplayStatics.h"

AMyAIController::AMyAIController()
{
}

void AMyAIController::PostInitProperties()
{
	Super::PostInitProperties();
}

void AMyAIController::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	MoveToGoal_InMode();
}

void AMyAIController::OnPawnBeginPlay(APawn* InPawn)
{
	Super::OnPawnBeginPlay(InPawn);
}

void AMyAIController::OnPossess(APawn* const InPawn)
{
	M_LOGFUNC();
	Super::OnPossess(InPawn);
	MoveToGoal_InMode();
}

void AMyAIController::OnMoveCompleted(FAIRequestID InRequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(InRequestID, Result);
	// @TODO
}

void AMyAIController::MoveToGoal_InMode()
{
	switch(MoveToGoalMode)
	{
	case ETestMoveToGoalMode::RequestMove:
		RequestMoveToActor();
		return;

	case ETestMoveToGoalMode::MoveToActor:
		MoveToGoalActor();
		return;

	case ETestMoveToGoalMode::MoveToLocation:
		MoveToGoalLocation();
		return;

	default:
		M_LOG_ERROR(TEXT("Unknown MoveToGoal mode!"));
		return;
	}
}

AActor* AMyAIController::FindGoalActor()
{
	TArray<AActor*> TaggedActors;
	static const FName TAG_NAME(TEXT("Goal"));
	UGameplayStatics::GetAllActorsWithTag(this, TAG_NAME, TaggedActors);
	if(TaggedActors.Num() == 0)
	{
		M_LOG_WARN(TEXT("no actor with \"%s\" Tag found"), *TAG_NAME.ToString());
		return nullptr;
	}
	if(TaggedActors.Num() > 0 )
	{
		M_LOG_WARN(TEXT("More than once actor with \"%s\" Tag found"), *TAG_NAME.ToString());
	}
	return Actor = TaggedActors[0];

}

void AMyAIController::MoveToGoalLocation()
{
	M_LOGFUNC();

	if( ! PrepareMoveToGoal() )
	{
		M_LOG_ERROR(TEXT("Aborting move request - PrepareMoveToGoal returned false"));
		return;
	}

	EPathFollowingRequestResult::Type const Result = MoveToLocation
	(
		GoalLocation,
	       	Move_AcceptanceRadius, bMove_StopOnOverlap, bMove_UsePathfinding, 
		bMove_ProjectDestinationToNavigation, bMove_CanStrafe, Move_FilterClass, bMove_AllowPartialPath
	);

	UAIUtil::LogPathFollowingRequestResult(FString(TEXT("MoveToLocation: Result")), Result);
}

void AMyAIController::MoveToGoalActor()
{
	M_LOGFUNC();

	if( ! PrepareMoveToGoal() )
	{
		M_LOG_ERROR(TEXT("Aborting move request - PrepareMoveToGoal returned false"));
		return;
	}

	EPathFollowingRequestResult::Type const Result = MoveToActor
	(
	 	Actor, 
	       	Move_AcceptanceRadius, bMove_StopOnOverlap, bMove_UsePathfinding, 
		bMove_CanStrafe, Move_FilterClass, bMove_AllowPartialPath
	);
	UAIUtil::LogPathFollowingRequestResult(FString(TEXT("MoveToActor: Result")), Result);
}

void AMyAIController::RequestMoveToActor()
{
	M_LOGFUNC();

	if( ! PrepareMoveToGoal() )
	{
		M_LOG_ERROR(TEXT("Aborting move request - PrepareMoveToGoal returned false"));
		return;
	}

	FAIMoveRequest Req { Actor };
	Req.SetAcceptanceRadius(Move_AcceptanceRadius);
	Req.SetUsePathfinding(bMove_UsePathfinding);
	Req.SetCanStrafe(bMove_CanStrafe);
	Req.SetNavigationFilter(Move_FilterClass);
	Req.SetAllowPartialPath(bMove_AllowPartialPath);

	FNavPathSharedPtr Path;
	FPathFindingQuery Query;

	{
		bool bBuildQuery = BuildPathfindingQuery(Req, Query);
		if(false == bBuildQuery)
		{
			M_LOG_ERROR(TEXT("BuildPathfindingQuery returned false"));
			return;
		}
		M_LOG(TEXT("BuildPathFindingQuery succeeded"));
	}

	{
		M_LOG(TEXT("Before calling FindPathForMoveRequest"));
		FindPathForMoveRequest(Req, Query, Path);
		M_LOG(TEXT("After calling FindPathForMoveRequest"));
	}

	{
		M_LOG(TEXT("Before calling RequestMove"));
		GoalRequestID = RequestMove(Req, Path);
		if(GoalRequestID == FAIRequestID::InvalidRequest)
		{
			M_LOG_ERROR(TEXT("RequestMove returend FAIRequestID::InvalidRequest"));
			return;
		}
		M_LOG(TEXT("Move request returned valid ID (RequestMove called); RequestID=%d"), GoalRequestID);
	}
}
bool AMyAIController::PrepareMoveToGoal()
{
	M_LOGFUNC();
	if(GetPawn() == nullptr)
	{
		M_LOG_ERROR(TEXT("Skipping requesting move: Pawn is not possessed"));
		return false;
	}
	if(GetCurrentMoveRequestID() != FAIRequestID::InvalidRequest)
	{
		M_LOG_WARN(TEXT("Skipping requesting move: ALREADY moving"));
		return false;
	}
	if( nullptr == Actor )
	{
		if(nullptr == FindGoalActor())
		{
			M_LOG_WARN(TEXT("Unable to find goal ACTOR"));
			return false;
		}

		if(nullptr == Actor)
		{
			M_LOG_ERROR(TEXT("Unable to move - target Actor is nullptr"));
			return false;
		}
	}
	return true;
}
