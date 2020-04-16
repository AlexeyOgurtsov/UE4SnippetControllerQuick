#include "BlackboardDemoActor.h"
#include "Util/Core/LogUtilLib.h"

// Blackboard includes
#include "BehaviorTree/BlackboardComponent.h"

//
//BehaviorTree/BehaviorTreeTypes.h: FBlackboardKey::FKey : uint8


ABlackboardDemoActor::ABlackboardDemoActor()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	TestSetGetKey();
}

void ABlackboardDemoActor::TestSetGetKey()
{
	M_LOGFUNC();

	static const FName TEST_KEY_NAME { TEXT("TEST_KEY") };
	static const int32 TEST_INT_KEY_VALUE { 3 };

	BlackboardComponent->SetValueAsInt( TEST_KEY_NAME, TEST_INT_KEY_VALUE );
	//check(BlackboardComponent->GetNumKeys() == 13);
//	const int GettedTestKeyValue = BlackboardComponent->GetValueAsInt( TEST_KEY_NAME );
	//check(GettedTestKeyValue == TEST_INT_KEY_VALUE);
}
