#pragma once

#include "Enemy/MyGunEnemy.h"
#include "MyPawnWithAIController.generated.h"

UCLASS()
class AMyPawnWithAIController : public AMyGunEnemy
{
	GENERATED_BODY()

public:
	AMyPawnWithAIController();
	virtual void BeginPlay() override;
};
