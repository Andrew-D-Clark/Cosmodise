// Fill out your copyright notice in the Description page of Project Settings.


#include "Flyer_Base.h"
#include "CosmoAttributeComponent.h"

// Sets default values
AFlyer_Base::AFlyer_Base()
{
	AttributeComp = CreateDefaultSubobject<UCosmoAttributeComponent>("AttributeComp");

}


// Called when the game starts or when spawned
void AFlyer_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyer_Base::Tick(float DeltaTime)
{
	//Calc Thrust
	// Removed Gravity Acceleration
	//float CurrentAcceleration = -GetActorRotation().Pitch * DeltaTime * Acceleration
	const float CurrentAcc = 1;//= -GetActorRotation().Pitch * DeltaTime * Acceleration;
	const float NewForwardSpeed = CurrentForwardSpeed;// + CurrentAcc;
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(LocalMove, true);

	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Roll = MouseSensitivityActual * CurrentRollSpeed * DeltaTime;
	DeltaRotation.Yaw = MouseSensitivityActual * CurrentYawSpeed * DeltaTime;
	DeltaRotation.Pitch = MouseSensitivityActual * CurrentPitchSpeed * DeltaTime;

	AddActorLocalRotation(DeltaRotation);

	GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Green, FString::Printf(TEXT("ForwardSpeed: %f"), CurrentForwardSpeed));

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlyer_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AFlyer_Base::ProcessMouseYInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &AFlyer_Base::ProcessMouseXInput);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	PlayerInputComponent->BindAxis("Thrust", this, &AFlyer_Base::ProcessKeyThrust);
	PlayerInputComponent->BindAxis("Pause/Unpause", this, &AFlyer_Base::ProcessKeyPause);

}

void AFlyer_Base::ProcessKeyPitch(float Rate)
{
}

void AFlyer_Base::ProcessKeyRoll(float Rate)
{
}

void AFlyer_Base::ProcessMouseYInput(float Value)
{
	ProcessRoll(Value);
}

void AFlyer_Base::ProcessMouseXInput(float Value)
{
	ProcessPitch(Value);
}

void AFlyer_Base::ProcessKeyThrust(float Rate)
{
	if (FMath::Abs(Rate) > .2f)
		CurrentForwardSpeed = CurrentForwardSpeed + Acceleration;
	if (FMath::Abs(Rate) < .2f)
		CurrentForwardSpeed = CurrentForwardSpeed - Acceleration;
}

void AFlyer_Base::ProcessKeyPause(float Rate)
{
}

void AFlyer_Base::ProcessRoll(float Value)
{
	const float TargetRollSpeed = Value * RollRateMultiplier;

	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AFlyer_Base::ProcessPitch(float Value)
{
	const float TargetPitchSpeed = Value * PitchRateMultiplier;

	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AFlyer_Base::ProcessThrust(float Rate)
{
}

void AFlyer_Base::OnHealthChanged(AActor* InstigatorActor, UCosmoAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Damaged
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	// Died
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);

		SetLifeSpan(5.0f);
	}
}

void AFlyer_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
