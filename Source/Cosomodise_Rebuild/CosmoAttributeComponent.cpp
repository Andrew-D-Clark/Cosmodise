// Fill out your copyright notice in the Description page of Project Settings.


#include "CosmoAttributeComponent.h"

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

}

bool UCosmoAttributeComponent::IsFullHealth() const
{

}

float UCosmoAttributeComponent::GetHealth() const
{

}

float UCosmoAttributeComponent::GetHealthMax() const
{

}

bool UCosmoAttributeComponent::IsAlive() const
{

}

bool UCosmoAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{

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
