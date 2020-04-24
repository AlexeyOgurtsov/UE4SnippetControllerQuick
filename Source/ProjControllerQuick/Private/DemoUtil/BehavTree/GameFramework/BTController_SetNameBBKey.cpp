#include "BTController_SetNameBBKey.h"
#include "Util\Core\LogUtilLib.h"

#include "BehaviorTree/BlackboardComponent.h"


ABTController_SetNameBBKey::ABTController_SetNameBBKey()
{
}

void ABTController_SetNameBBKey::PostInitProperties()
{
	Super::PostInitProperties();
}

// ~AActor Begin
void ABTController_SetNameBBKey::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(TimeSinceLastActionCall >= ActionDelay)
	{		
		if (ActionCallIndex < NumActionCalls)
		{
			M_LOG(TEXT("%s: Performing action - time is come (TimeSinceLastActionCall = %f)"), *LogPrefix, TimeSinceLastActionCall);
			DoSetKey();
			ActionCallIndex++;
			TimeSinceLastActionCall = 0;
		}
	}

	TimeSinceLastActionCall +=  DeltaSeconds;
}

void ABTController_SetNameBBKey::DoSetKey()
{
	UBlackboardComponent* const BBComp = GetBlackboardComponent();
	const FBlackboard::FKey KeyID = GetSelectedBlackboardKeyID();
	if( ! BBComp->IsValidKey(KeyID) )
	{
		M_LOG_ERROR(TEXT("%s: unable to set name key: IsValidKey returns false"), *LogPrefix);
		return;
	}
	M_LOG_WARN_IF(!BlackboardKey.IsSet(), TEXT("%s: key is NOT set"), *LogPrefix);

	{
		M_LOG(TEXT("%s: Setting name key \"%s\" to value \"%s\""), *LogPrefix, *GetSelectedBlackboardKey().ToString(), *NewValue.ToString());
		BBComp->SetValueAsName(GetSelectedBlackboardKey(), NewValue);
	}
}
FName ABTController_SetNameBBKey::GetSelectedBlackboardKey() const
{
	return (KeyIdentMode == EBBKeyIdentMode::Selector) ? BlackboardKey.SelectedKeyName : BlackboardKeyName;
}
FBlackboard::FKey ABTController_SetNameBBKey::GetSelectedBlackboardKeyID() const
{
	switch(KeyIdentMode)
	{
	case EBBKeyIdentMode::Selector:
	       	return BlackboardKey.GetSelectedKeyID();

	case EBBKeyIdentMode::Name:
		if(const UBlackboardComponent* BBComp = GetBlackboardComponent())
		{
			return BBComp->GetKeyID(BlackboardKeyName);
		}
		else
		{
			ensureMsgf(false, TEXT("Blackboard component is expected to be added"));
			return FBlackboard::InvalidKey;
		}

	default:
		break;
	}
	return FBlackboard::InvalidKey;
}
// ~AActor End
