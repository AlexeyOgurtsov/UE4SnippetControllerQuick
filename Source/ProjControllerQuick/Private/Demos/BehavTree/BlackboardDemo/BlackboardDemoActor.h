#pragma once

#include "GameFramework/Actor.h"
#include "BlackboardDemoActor.generated.h"

class UBlackboardComponent;

UCLASS(BlueprintType)
class ABlackboardDemoActor : public AActor
{
	GENERATED_BODY()

public:
	ABlackboardDemoActor();

	UFUNCTION(BlueprintPure, Category=BlackboardDemo)
	UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
private:

	/** BlackboardComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UBlackboardComponent* BlackboardComponent = nullptr;
	
	void TestSetGetKey();
};
