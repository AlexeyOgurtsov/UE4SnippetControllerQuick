#include "BehaviorTreeController.h"
#include "Util/Core/LogUtilLib.h"

#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

/**
* Responsibilities:
*
* Tests:
* What will be if I run behavior tree that is ALREADT running?
* Running and stopping behavior tree.
* Logging ticking.
* Logging AI controller events (will they be fired when BT is running?):
* - Possession;
* - Actor collision handlers;
*/

ABehaviorTreeController::ABehaviorTreeController()
{
	LogPrefix = FString::Printf(TEXT("From %s"), *ULogUtilLib::GetNameAndClassSafe(this));
}

// ~Config Begin
void ABehaviorTreeController::SetBTConfig(const FBehaviorTreeControllerConfig& NewBTConfig)
{
	// @TODO: Check that we change BTConfig ONLY when BT is NOT running.
	BTConfig = NewBTConfig;
}
// ~Config End

void ABehaviorTreeController::MyRunBT()
{
	M_LOGFUNC();
	if (BTConfig.BehaviorTree == nullptr)
	{
		M_LOG_ERROR(TEXT("Skipping launching Behavior Tree: asset is nullptr"));
		return;
	}

	const bool bShouldRunBT = true;
	if(bShouldRunBT)
	{
		M_LOG(TEXT("Running behavior tree \"%s\""), *BTConfig.BehaviorTree->GetName());
		RunBehaviorTree(BTConfig.BehaviorTree);
		if(BTConfig.ShouldStopAutomatically())
		{
			bool const bLoopedTimer = false;
			GetWorldTimerManager().SetTimer(StopBTTimerHandle, this, &ABehaviorTreeController::OnStopBTTimerSignaled, BTConfig.BTRunDuration, bLoopedTimer);
		}
	}
}

void ABehaviorTreeController::OnStopBTTimerSignaled()
{
	M_LOG(TEXT("%s on object \"%s\" of class \"%s\" (IsValid = %s)"), TEXT(__FUNCTION__), *GetName(), *GetClass()->GetName(), IsValid(this) ? TEXT("YES") : TEXT("no"));
	MyStopBT();
}

void ABehaviorTreeController::K2_MyStopBT()
{
	MyStopBT();
}

void ABehaviorTreeController::MyStopBT(EBTStopMode::Type StopMode)
{
	UBehaviorTreeComponent* const BTComp = GetBTComponent();
	M_LOG_WARN_IF(BTComp == nullptr, TEXT("Unable to stop BT: BehaviorTree component is nullptr!"));
	if(BTComp)
	{
		M_LOG(TEXT("Calling StopTree to Stop the beahviour tree"));
		BTComp->StopTree(BTConfig.GetAutomaticStopMode());
	}
}

// ~AActor Begin
void ABehaviorTreeController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	LogTickIfShould();
	NumTickCalls++;
}

void ABehaviorTreeController::BeginPlay()
{
	Super::BeginPlay();
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));
	if( ( static_cast<EBTLaunchFlags>(BTConfig.BTLaunchFlags) & EBTLaunchFlags::LaunchOnBeginPlay) != EBTLaunchFlags::None )
	{
		MyRunBT();
	}
	bBeginPlayCalled = true;
}
// ~AActor End

// ~AAIController Begin
void ABehaviorTreeController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	M_LOG(TEXT("%s: %s; bBeginPlayCalled=%s"), *LogPrefix, TEXT(__FUNCTION__), bBeginPlayCalled ? TEXT("YES") : TEXT("no"));

	if(InPawn)
	{
		InPawn->OnActorBeginOverlap.AddDynamic(this, &ABehaviorTreeController::OnPawnBeginOverlap);
		InPawn->OnActorEndOverlap.AddDynamic(this, &ABehaviorTreeController::OnPawnEndOverlap);
	}

	if( ( static_cast<EBTLaunchFlags>(BTConfig.BTLaunchFlags) & EBTLaunchFlags::LaunchOnPossess) != EBTLaunchFlags::None )
	{
		MyRunBT();
	}
}

void ABehaviorTreeController::OnUnPossess()
{
	Super::OnUnPossess();
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));

	if(APawn* P = GetPawn())
	{
		P->OnActorBeginOverlap.RemoveAll(this);
		P->OnActorEndOverlap.RemoveAll(this);
	}
}
// ~AAIController End
void ABehaviorTreeController::OnPawnBeginOverlap_Implementation(AActor* Actor, AActor* OverlappedActor)
{
	M_LOG(TEXT("%s: %s: Actor={%s}, OtherActor={%s}"), *LogPrefix, TEXT(__FUNCTION__), *ULogUtilLib::GetNameAndClassSafe(Actor),  *ULogUtilLib::GetNameAndClassSafe(OverlappedActor));
}

void ABehaviorTreeController::OnPawnEndOverlap_Implementation(AActor* Actor, AActor* OverlappedActor)
{
	M_LOG(TEXT("%s: %s: Actor={%s}, OtherActor={%s}"), *LogPrefix, TEXT(__FUNCTION__), *ULogUtilLib::GetNameAndClassSafe(Actor),  *ULogUtilLib::GetNameAndClassSafe(OverlappedActor));
}

UBehaviorTreeComponent* ABehaviorTreeController::GetBTComponent() const
{
	return Cast<UBehaviorTreeComponent>(GetBrainComponent());
}

void ABehaviorTreeController::LogTickIfShould() const
{
	if (!BTConfig.bLogTick)
	{
		return;
	}
	if (BTConfig.bLogTickOnlyWhenBTRunning)
	{
		if (GetBTComponent() == nullptr || !GetBTComponent()->IsRunning())
		{
			return;
		}		
	}
	const float SecsSinceCreation = GetGameTimeSinceCreation();
	if( ( (SecsSinceCreation - LastLogTickTimeSinceCreation) >= BTConfig.LogTickPeriodInSeconds )
			||  (SecsSinceCreation == 0) )
	{
		M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));
		LastLogTickTimeSinceCreation = SecsSinceCreation;
	}
}
