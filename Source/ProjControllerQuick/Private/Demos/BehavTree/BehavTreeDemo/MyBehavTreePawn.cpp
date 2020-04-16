#include "MyBehavTreePawn.h"
#include "BehavTreeController.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/EngineTypes.h" // EAutoPossessAI

AMyBehavTreePawn::AMyBehavTreePawn()
{
	AIControllerClass = ABehavTreeController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyBehavTreePawn::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}
