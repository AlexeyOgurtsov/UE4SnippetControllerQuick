#include "MyEnemyPawnBase.h"
#include "EnemyBaseConfig.h"
#include "Controller/MyAIControllerBase.h"

#include "PawnBase/MyPawnImpl.h"
#include "Util/Weapon/QuickWeaponComponent/QuickWeaponComponent.h"
#include "Util/Weapon/QuickWeaponComponent/QuickWeaponTypesLib.h"

#include "Util/Core/LogUtilLib.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

#include "UObject/ConstructorHelpers.h"

// WARN
#include "Perception/PawnSensingComponent.h"

AMyEnemyPawnBase::AMyEnemyPawnBase()
{
	Impl = UMyPawnImpl::CreateInitialized(this, TEXT("Impl"));

	InitMesh(RootComponent);	
	InitWeaponComponent();

	InitializeSensingComponent();
}

AMyAIControllerBase* AMyEnemyPawnBase::GetAIControllerBase() const
{
	return Cast<AMyAIControllerBase>(GetController());
}

void AMyEnemyPawnBase::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	WeaponComponent->ReAttachToSockets();
	if( GetAIControllerBase() )
	{
		GetAIControllerBase()->OnPawnBeginPlay(this);
	}
}

void AMyEnemyPawnBase::InitWeaponComponent()
{
	checkf(MyMesh, TEXT("When calling %s mesh must be initialized"), TEXT(__FUNCTION__));
	WeaponComponent = CreateDefaultSubobject<UQuickWeaponComponent>(TEXT("QuickWeaponComponent"));
	bool bInitialized = UQuickWeaponTypesLib::InitializePrimaryWeapon(WeaponComponent, MyMesh->GetFName());
}

void AMyEnemyPawnBase::PawnStartFire(uint8 Mode)
{
	bool bSucceeded = WeaponComponent->FireByIndex(Mode);
}

void AMyEnemyPawnBase::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { EnemyBaseConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), EnemyBaseConfig::Default::MESH_ASSET_PATH);

	{
		MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), EnemyBaseConfig::Default::MESH_ASSET_PATH);
			MyMesh->SetStaticMesh(MeshFinder.Get());
		}

		if(InAttachTo)
		{
			MyMesh->SetupAttachment(InAttachTo);
		}
	}
}

void AMyEnemyPawnBase::InitializeSensingComponent()	
{
	M_LOGFUNC();
	Sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
	Sensing->OnSeePawn.AddDynamic(this, &AMyEnemyPawnBase::OnSeePawn);
}
// ~ AActor Begin
float AMyEnemyPawnBase::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return Impl->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
// ~ AActor End

// ~ IMyPawnBase Begin
FMyHitState AMyEnemyPawnBase::GetHitState_Implementation() const
{
	return Impl->HitState;
}

UMyPawnEvents* AMyEnemyPawnBase::GetEvents_Implementation() const
{
	return Impl->MyEvents;
}
UPawnSensingComponent* AMyEnemyPawnBase::GetSensingComponent_Implementation() const
{
	return Sensing;
}
void AMyEnemyPawnBase::OnSeePawn(APawn* InPawn)
{
	// Nothing is to be done here yet
}
// ~ IMyPawnBase End
