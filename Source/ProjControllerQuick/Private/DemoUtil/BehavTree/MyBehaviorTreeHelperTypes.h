#pragma once

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBehaviorTreeHelperTypes.generated.h"

/** EBBKeyIdentMode*/
UENUM(BlueprintType, Category=Blackboard)
enum class EBBKeyIdentMode : uint8
{
	Selector       = 0         UMETA(DisplayName="Selector")
	, Name         = 1           UMETA(DisplayName="Name")
};
