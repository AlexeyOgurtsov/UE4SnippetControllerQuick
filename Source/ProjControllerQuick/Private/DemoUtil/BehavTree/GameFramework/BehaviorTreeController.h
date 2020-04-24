#pragma once

#include "AIController.h"
#include "BehaviorTreeControllerConfig.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Engine/EngineTypes.h"
#include "BehaviorTreeController.generated.h"

UCLASS(BlueprintType)
class ABehaviorTreeController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=BehaviorTree, Meta=(ShowOnlyInnerProperties))
	FBehaviorTreeControllerConfig BTConfig;

public:
	ABehaviorTreeController();

	// ~Config Begin
	void SetBTConfig(const FBehaviorTreeControllerConfig& NewBTConfig);
	// ~Config End

	/**
	* Runs behavior tree according to settings.
	*/
	UFUNCTION(BlueprintCallable, Category = BehaviorTree)
	void MyRunBT();

	/**
	* Helper for stopping the behavior tree component.
	* You know (at least at 4.24 there's NO stop AI function in the AI controller!)
	*/
	UFUNCTION(BlueprintCallable, Category = BehaviorTree, Meta=(DisplayName=MyStopBT))
	void K2_MyStopBT();
	
	/**
	* Helper for stopping the behavior tree component.
	* You know (at least at 4.24 there's NO stop AI function in the AI controller!)
	*/
	void MyStopBT(EBTStopMode::Type StopMode = EBTStopMode::Type::Safe);

	// ~AActor Begin
	// Tick: Will it be called when behavior tree is running?
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
	// ~AActor End
	
	// ~AAIController Begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	// ~AAIController End

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Actor|Events")
	void OnPawnBeginOverlap(AActor* Actor, AActor* OverlappedActor);
	virtual void OnPawnBeginOverlap_Implementation(AActor* Actor, AActor* OverlappedActor);

	UFUNCTION(BlueprintNativeEvent, Category="Actor|Events")
	void OnPawnEndOverlap(AActor* Actor, AActor* OverlappedActor);
	virtual void OnPawnEndOverlap_Implementation(AActor* Actor, AActor* OverlappedActor);

protected:
	//  ~Logging Begin
	FString LogPrefix;
	//  ~Logging End

private:
	// ~BehaviorTree Begin
	UBehaviorTreeComponent* GetBTComponent() const;
	// ~BehaviorTree End
	
	// ~BehaviorTree Timer Begin
	FTimerHandle StopBTTimerHandle;
	UFUNCTION()
	void OnStopBTTimerSignaled();
	// ~BehaviorTree Timer End

	// ~Framework Begin
	bool bBeginPlayCalled = false;
	// ~Framework End

	// ~Tick logging begin
	int NumTickCalls = 0;
	mutable float LastLogTickTimeSinceCreation = 0.0;

	void LogTickIfShould() const;
	// ~Tick logging end
};
