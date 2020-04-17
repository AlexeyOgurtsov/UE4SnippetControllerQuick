#include "SimpleMoveToGoalAIPawn.h"
#include "SimpleMoveToGoalAIController.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/EngineTypes.h" // EAutoPossessAI

ASimpleMoveToGoalAIPawn::ASimpleMoveToGoalAIPawn()
{
	AIControllerClass = ASimpleMoveToGoalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASimpleMoveToGoalAIPawn::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}
