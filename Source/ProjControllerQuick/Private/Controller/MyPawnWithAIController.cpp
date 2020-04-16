#include "MyPawnWithAIController.h"
#include "MyAIController.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/EngineTypes.h" // EAutoPossessAI

AMyPawnWithAIController::AMyPawnWithAIController()
{
	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyPawnWithAIController::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}
