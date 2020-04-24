#include "BehaviorTreePawn.h"
#include "BehaviorTreeController.h"

#include "Util\Core\LogUtilLib.h"

ABehaviorTreePawn::ABehaviorTreePawn()
{
	AIControllerClass = ABehaviorTreeController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABehaviorTreePawn::PostInitProperties()
{
	Super::PostInitProperties();
}

void ABehaviorTreePawn::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}

void ABehaviorTreePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	M_LOG(TEXT("%s: NewController=%s"), TEXT(__FUNCTION__), *ULogUtilLib::GetNameAndClassSafe(NewController));
	if (auto NewBTController = Cast<ABehaviorTreeController>(NewController))
	{
		NewBTController->SetBTConfig(BTConfig);
	}
	// NOTE: AController::OnPossessed will be called LATER than PossessedBy (UE 4.24)
}

void ABehaviorTreePawn::UnPossessed()
{
	M_LOG(TEXT("%s: GetController=%s"), TEXT(__FUNCTION__), *ULogUtilLib::GetNameAndClassSafe(GetController()));
	Super::UnPossessed();	
}

ABehaviorTreeController* ABehaviorTreePawn::GetBTController() const
{
	return Cast<ABehaviorTreeController>(GetController());
}
