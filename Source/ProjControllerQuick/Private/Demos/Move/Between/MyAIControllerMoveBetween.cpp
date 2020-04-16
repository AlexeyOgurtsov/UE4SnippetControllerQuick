#include "MyAIControllerMoveBetween.h"
#include "Util/Core/LogUtilLib.h"

AMyAIControllerMoveBetween::AMyAIControllerMoveBetween()
: TargetSpot {FirstSpot}
{
}

void AMyAIControllerMoveBetween::PostInitProperties()
{
	Super::PostInitProperties();
	TargetSpot = FirstSpot;
}

void AMyAIControllerMoveBetween::Tick(float DeltaSeconds)
{
}

void AMyAIControllerMoveBetween::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	// @TODO
}

AActor* AMyAIControllerMoveBetween::GetOtherTargetSpot() const
{
	return (TargetSpot == FirstSpot) ? SecondSpot : FirstSpot;
}
