// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CosmoAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UCosmoAttributeComponent*, OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, UCosmoAttributeComponent*, OwningComp, float, NewValue, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COSOMODISE_REBUILD_API UCosmoAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UCosmoAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);

	// Sets default values for this component's properties
	UCosmoAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float Boost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
		float BoostMax;

	UFUNCTION(NetMulticast, Reliable)//@FIXME: mark as unreliable once we move the "state" out of SCharacter//Reliable ex. Chat Message
		void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Unreliable)//@FIXME: mark as unreliable once we move the "state" out of SCharacter//Reliable ex. Chat Message
		void MulticastBoostChanged(AActor* InstigatorActor, float NewRage, float Delta);

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthMax() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsAlive() const;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttributeChanged OnBoostChanged;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
