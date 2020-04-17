#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBTTaskLib.generated.h"

UCLASS(BlueprintType)
class UMyBTTaskLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Task|BehaviorTree|Log|Debug")
	static void LogBTNodeResult(EBTNodeResult::Type NodeResult);

	UFUNCTION(BlueprintPure, Category = "Task|BehaviorTree|Log|Debug")
	static FString GetBTNodeResultString(EBTNodeResult::Type NodeResult);
};

