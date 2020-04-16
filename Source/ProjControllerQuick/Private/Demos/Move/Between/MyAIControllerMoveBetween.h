#pragma once

#include "Controller/MyAIControllerBase.h"
#include "MyAIControllerMoveBetween.generated.h"

UCLASS()
class AMyAIControllerMoveBetween : public AMyAIControllerBase
{
	GENERATED_BODY()

	AMyAIControllerMoveBetween();

public:
	// ~AActor Begin
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitProperties() override;
	// ~AActor End

	/** GetFirstSpot*/
	UFUNCTION(BlueprintPure, Category=Path)
	AActor* GetFirstSpot() const { return FirstSpot; }
	
	/** GetSecondSpot*/
	UFUNCTION(BlueprintPure, Category=Path)
	AActor* GetSecondSpot() const { return SecondSpot; }
	
	/** GetTargetSpot*/
	UFUNCTION(BlueprintPure, Category=Path)
	AActor* GetTargetSpot() const { return TargetSpot; }

	AActor* GetOtherTargetSpot() const;
	
private:
	/** FirstSpot*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Path)
	AActor* FirstSpot = nullptr;

	/** SecondSpot*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Path)
	AActor* SecondSpot = nullptr;

	/** TargetSpot*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Path)
	AActor* TargetSpot = nullptr;
};
