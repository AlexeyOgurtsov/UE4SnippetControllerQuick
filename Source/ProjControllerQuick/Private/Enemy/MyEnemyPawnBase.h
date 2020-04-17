#pragma once

/**
* Actor that has collision and mesh.
*/

#include "GameFramework/Character.h"
#include "PawnBase/IMyPawnInterface.h"
#include "MyEnemyPawnBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class AMyAIControllerBase;

class UMyPawnImpl;

class UPawnSensingComponent;

UCLASS()
class AMyEnemyPawnBase : 
	public ACharacter
,	public IMyPawnInterface
{
	GENERATED_BODY()

public:
	AMyEnemyPawnBase();

	// Helper getters Begin
	AMyAIControllerBase* GetAIControllerBase() const;
	// Helper getters End

	// ~ AActor Begin
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// ~ AActor End
	
	// ~ IMyPawnBase Begin
	virtual FMyHitState GetHitState_Implementation() const override;
	virtual UMyPawnEvents* GetEvents_Implementation() const override;
	virtual UPawnSensingComponent* GetSensingComponent_Implementation() const override;
	// ~ IMyPawnBase End

	UFUNCTION(BlueprintPure, Category = Visual)
	UStaticMeshComponent* GetMesh() const { return MyMesh; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, Meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* MyMesh = nullptr;
	void InitMesh(USceneComponent* InAttachTo);
	
	/** GetSensing*/
	UFUNCTION(BlueprintPure, Category=Sensing)
	UPawnSensingComponent* GetSensing() const
	{
		return Sensing;
	}

private:
	// ~Sensing Begin
	/** Sensing*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UPawnSensingComponent* Sensing = nullptr;

	/** OnSeePawn*/
	UFUNCTION(BlueprintCallable, Category=Sensing)
	void OnSeePawn(APawn* InPawn);

	void InitializeSensingComponent();	
	// ~Sensing End
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UMyPawnImpl* Impl = nullptr;
};
