#pragma once

#include "Enemy/MyGunEnemy.h"
#include "MyPawnWithAIControllerMoveBetween.generated.h"

UCLASS()
class AMyPawnWithAIControllerMoveBetween : public AMyGunEnemy
{
	GENERATED_BODY()

public:
	AMyPawnWithAIControllerMoveBetween();
	virtual void BeginPlay() override;

};
