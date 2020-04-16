#include "MyPawnWithAIControllerMoveBetween.h"
#include "MyAIControllerMoveBetween.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/EngineTypes.h" // EAutoPossessAI

AMyPawnWithAIControllerMoveBetween::AMyPawnWithAIControllerMoveBetween()
{
	AIControllerClass = AMyAIControllerMoveBetween::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyPawnWithAIControllerMoveBetween::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}
