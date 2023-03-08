// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Flyer_Base.generated.h"

class UCosmoAttributeComponent;

UCLASS()
class COSOMODISE_REBUILD_API AFlyer_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFlyer_Base();

	UPROPERTY(EditAnywhere, Category = "Flight")
		float Acceleration{ 25.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MouseSensitivityActual = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Flight")
		float TurnSpeed{ 100.f };
	UPROPERTY(EditAnywhere, Category = "Flight")
		float MaxSpeed{ 7000.f };
	UPROPERTY(EditAnywhere, Category = "Flight")
		float MinSpeed{ 500.f };
	UPROPERTY(EditAnywhere, Category = "Flight")
		float RollRateMultiplier{ 200.f };
	UPROPERTY(EditAnywhere, Category = "Flight")
		float PitchRateMultiplier{ 200.f };
	UPROPERTY(VisibleAnywhere, Category = "Flight")
		float CurrentForwardSpeed{ 500.f };


	float CurrentYawSpeed{ 0 };
	float CurrentPitchSpeed{ 0 };
	float CurrentRollSpeed{ 0 };

protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCosmoAttributeComponent* AttributeComp;

	void ProcessKeyPitch(float Rate);
	void ProcessKeyRoll(float Rate);

	void ProcessMouseYInput(float Value);
	void ProcessMouseXInput(float Value);

	void ProcessKeyThrust(float Rate);
	void ProcessKeyPause(float Rate);

	//For calculation rotation
	void ProcessRoll(float Value);
	void ProcessPitch(float Value);
	void ProcessThrust(float Rate);

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UCosmoAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
