#pragma once

#include "Controller/MyPawnWithAIController.h"
#include "MyBehavTreePawn.generated.h"

UCLASS()
class AMyBehavTreePawn : public AMyPawnWithAIController
{
	GENERATED_BODY()

public:
	AMyBehavTreePawn();

	virtual void BeginPlay() override;
};
