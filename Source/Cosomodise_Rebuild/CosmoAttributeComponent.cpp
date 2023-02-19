// Fill out your copyright notice in the Description page of Project Settings.


#include "CosmoAttributeComponent.h"
#include "CosmoGameModeBase.h"
#include "Net/UnrealNetwork.h"

UCosmoAttributeComponent* UCosmoAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UCosmoAttributeComponent>();
		//return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UCosmoAttributeComponent::IsActorAlive(AActor* Actor)
{
	UCosmoAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

// Sets default values for this component's properties
UCosmoAttributeComponent::UCosmoAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;

	
	BoostMax = 100;
	Boost = BoostMax;

	SetIsReplicatedByDefault(true);//Use if in the constructor
}


void UCosmoAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{

}

void UCosmoAttributeComponent::MulticastBoostChanged_Implementation(AActor* InstigatorActor, float NewRage, float Delta)
{

}

// Called when the game starts
void UCosmoAttributeComponent::BeginPlay()
{
	
	
}


bool UCosmoAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

bool UCosmoAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float UCosmoAttributeComponent::GetHealth() const
{
	return Health;
}

float UCosmoAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool UCosmoAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UCosmoAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}


	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = NewHealth - OldHealth;

	// Is Server?
	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		// Died
		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			ACosmoGameModeBase* GM = GetWorld()->GetAuthGameMode<ACosmoGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	return ActualDelta != 0;
}

// Called every frame
void UCosmoAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCosmoAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCosmoAttributeComponent, Health);
	DOREPLIFETIME(UCosmoAttributeComponent, HealthMax);
	DOREPLIFETIME(UCosmoAttributeComponent, Boost);
	DOREPLIFETIME(UCosmoAttributeComponent, BoostMax);

	//OREPLIFETIME_CONDITION(USAttributeComponent, HealthMax, COND_OwnerOnly);
}
