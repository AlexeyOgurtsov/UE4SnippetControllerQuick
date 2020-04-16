#include "MyEnemyPawnBase.h"
#include "EnemyBaseConfig.h"
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

#include "PawnBase/MyPawnImpl.h"
#include "Controller/MyAIControllerBase.h"

AMyEnemyPawnBase::AMyEnemyPawnBase()
{
	Impl = UMyPawnImpl::CreateInitialized(this, TEXT("Impl"));

	InitProxSphere(RootSceneComponent);
	RootComponent = ProxSphere;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);

	InitCameraAndSpringArm(RootSceneComponent);
	InitMesh(RootSceneComponent);

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
	if( GetAIControllerBase() )
	{
		GetAIControllerBase()->OnPawnBeginPlay(this);
	}
}

void AMyEnemyPawnBase::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = EnemyBaseConfig::Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(EnemyBaseConfig::Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(EnemyBaseConfig::Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = EnemyBaseConfig::Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = EnemyBaseConfig::Default::SPRINGARM_CAMERA_LAG_SPEED;
	if(InAttachTo)
	{
		SpringArm->SetupAttachment(InAttachTo);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AMyEnemyPawnBase::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { EnemyBaseConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), EnemyBaseConfig::Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), EnemyBaseConfig::Default::MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}
}

void AMyEnemyPawnBase::InitProxSphere(USceneComponent* InAttachTo)
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(EnemyBaseConfig::Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(EnemyBaseConfig::Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
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
