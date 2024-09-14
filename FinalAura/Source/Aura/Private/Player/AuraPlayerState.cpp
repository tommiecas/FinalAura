// Copyright Gravity Well Games


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, PlayerCharacterLevel);
	DOREPLIFETIME(AAuraPlayerState, XP);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::AddToXP(const int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToLevel(const int32 InLevel)
{
	PlayerCharacterLevel += InLevel;
	OnLevelChangedDelegate.Broadcast(PlayerCharacterLevel);
}

void AAuraPlayerState::SetXP(const int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::SetLevel(const int32 InLevel)
{
	PlayerCharacterLevel = InLevel;
	OnLevelChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel) const
{
	OnLevelChangedDelegate.Broadcast(PlayerCharacterLevel);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP) const
{
	OnXPChangedDelegate.Broadcast(XP);
}
