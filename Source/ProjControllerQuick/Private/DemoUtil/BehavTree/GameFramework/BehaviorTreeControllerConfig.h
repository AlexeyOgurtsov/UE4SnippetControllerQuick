#pragma once

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTreeControllerConfig.generated.h"

UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class EBTLaunchFlags : uint8
{
	None                   = 0             UMETA(DisplayName="None"),
	LaunchOnBeginPlay      = 1 << 0        UMETA(DisplayName="Launch on BeginPlay"),
	LaunchOnPossess        = 1 << 1        UMETA(DisplayName="Launch on Possess")
};
ENUM_CLASS_FLAGS(EBTLaunchFlags);

class UBehaviorTree;

USTRUCT(BlueprintType)
struct FBehaviorTreeControllerConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = BehaviorTree, Meta=(BitmaskEnum="EBTLaunchFlags"))
	uint8 BTLaunchFlags = static_cast<uint8>(EBTLaunchFlags::LaunchOnPossess);

	UPROPERTY(EditAnywhere, Category = BehaviorTree)
	class UBehaviorTree* BehaviorTree = nullptr;

	// ~Automatic Stopping Begin
	/**
	* If duration is equal to or less than zero,
	* then behavior tree will NOT be stopped.
	*/
	UPROPERTY(EditAnywhere, Category = BehaviorTree)
	float BTRunDuration = 5.0;

	bool ShouldStopAutomatically() const { return BTRunDuration > 0; }

	UPROPERTY(EditAnywhere, Category = BehaviorTree)
	bool bUseForcedAutomaticStop = true;

	EBTStopMode::Type GetAutomaticStopMode() const
	{
		return bUseForcedAutomaticStop ? EBTStopMode::Type::Forced : EBTStopMode::Type::Safe;
	}
	// ~Automatic Stopping End

	// ~LogTick Begin
	UPROPERTY(EditAnywhere, Category = Log)
	bool bLogTick = true;

	UPROPERTY(EditAnywhere, Category = Log)
	bool bLogTickOnlyWhenBTRunning = true;

	UPROPERTY(EditAnywhere, Category = Log)
	int LogTickPeriodInSeconds = 1.0F;
	// ~LogTick End
};
