#pragma once

#include "Enemy/MyGunEnemy.h"
#include "SimpleMoveToGoalAIPawn.generated.h"

UCLASS()
class ASimpleMoveToGoalAIPawn : public AMyGunEnemy
{
	GENERATED_BODY()

public:
	ASimpleMoveToGoalAIPawn();
	virtual void BeginPlay() override;

};
