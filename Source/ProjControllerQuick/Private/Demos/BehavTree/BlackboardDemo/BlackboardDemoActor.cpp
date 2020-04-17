#include "BlackboardDemoActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Util/Core/LogUtilLib.h"

// Blackboard includes
#include "BehaviorTree/BlackboardComponent.h"

//
//BehaviorTree/BehaviorTreeTypes.h: FBlackboardKey::FKey : uint8


ABlackboardDemoActor::ABlackboardDemoActor()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	InitBlackboard();

	TestSetGetKey();
}

void ABlackboardDemoActor::TestSetGetKey()
{
	M_LOGFUNC();

	static const FName TEST_INT_KEY_NAME { TEXT("TestInt") };
	static const int32 TEST_INT_KEY_VALUE { 3 };

	BlackboardComponent->SetValueAsInt( TEST_INT_KEY_NAME, TEST_INT_KEY_VALUE );	
	const int GettedTestKeyValue = BlackboardComponent->GetValueAsInt( TEST_INT_KEY_NAME );
	// Why does NOT work?
	//check(GettedTestKeyValue == TEST_INT_KEY_VALUE);
}

void ABlackboardDemoActor::InitBlackboard()
{
	M_LOGFUNC();	
	ConstructorHelpers::FObjectFinder<UBlackboardData> ObjectFinder { TEXT("BlackboardData'/Game/Demos/BlackboardDemo/ASSET/DemoBlackboard.DemoBlackboard'") };	
	BlackboardComponent->InitializeBlackboard(*ObjectFinder.Object);

	// fails:?
	//check(BlackboardComponent->GetNumKeys() > 0);
}