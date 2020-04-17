#include "BehavTreeController.h"
#include "Util\Core\LogUtilLib.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "UObject/ConstructorHelpers.h"

ABehavTreeController::ABehavTreeController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehavTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));

	LoadBlackboardComponentAtCtor();
	LoadBehavTreeAtCtor();

	InitBlackboardComponent();
}

void ABehavTreeController::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();		

	bBeginPlayStarted = true;

	if (GetPawn() != nullptr)
	{
		OnWePossessedAndStartedToPlay();
	}
}

void ABehavTreeController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	M_LOGFUNC();

	if (bBeginPlayStarted)
	{
		OnWePossessedAndStartedToPlay();
	}
}

void ABehavTreeController::OnWePossessedAndStartedToPlay()
{
	M_LOGFUNC();
	RunBehaviorTree(TestBehavTree);
}

void ABehavTreeController::InitBlackboardComponent()
{
	M_LOGFUNC();	
	const bool bInitializedProperly = BlackboardComponent->InitializeBlackboard(*TestBlackboardData);
	ULogUtilLib::LogYesNoC(TEXT("InitializeBlackboard returned"), bInitializedProperly);
}

void ABehavTreeController::InitBehavTree()
{
	M_LOGFUNC();
	//BehavTreeComponent->StartTree(*TestBehavTree);
}


void ABehavTreeController::LoadBlackboardComponentAtCtor()
{
	M_LOGFUNC();
	ConstructorHelpers::FObjectFinder<UBlackboardData> ObjectFinder{ TEXT("BlackboardData'/Game/Demos/BehavTree/Asset/TestBlackboard.TestBlackboard'") };
	TestBlackboardData = ObjectFinder.Object;
}

void ABehavTreeController::LoadBehavTreeAtCtor()
{
	M_LOGFUNC();
	ConstructorHelpers::FObjectFinder<UBehaviorTree> ObjectFinder{ TEXT("BehaviorTree'/Game/Demos/BehavTree/Asset/TestBehavTree.TestBehavTree'") };
	TestBehavTree = ObjectFinder.Object;
}