#include "TestGameplayAbility.h"
#include "Util\Core\LogUtilLib.h"

UTestGameplayAbility::UTestGameplayAbility()
{
	LogPrefix = FString::Printf(TEXT("ABILITY of class \"%s\""), *GetClass()->GetName());
}

// ~UGameplayAbility Begin
bool UTestGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, OptionalRelevantTags);
}

/** Actually activate ability, do not call this directly */
void UTestGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

bool UTestGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo);
}

bool UTestGameplayAbility::CommitAbilityCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const bool ForceCooldown)
{
	return Super::CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, ForceCooldown);
}

bool UTestGameplayAbility::CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	return Super::CommitAbilityCost(Handle, ActorInfo, ActivationInfo);
}

/** Destroys instanced-per-execution abilities. Instance-per-actor abilities should 'reset'. Any active ability state tasks receive the 'OnAbilityStateInterrupted' event. Non instance abilities - what can we do? */
void UTestGameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
void UTestGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
// ~UGameplayAbility End

