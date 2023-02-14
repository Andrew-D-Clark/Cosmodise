// Fill out your copyright notice in the Description page of Project Settings.


#include "RingBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetMathLibrary.inl"

// Sets default values
ARingBase::ARingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	UE_LOG(LogTemp, Warning, TEXT("RingBase Constructer"));

}

// Called when the game starts or when spawned
void ARingBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("RingBase BeginPlay"));

	
}

// Called every frame
void ARingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("RingBase TickTickTick"));

}

FVector ARingBase::GetRingRotation() const
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector coords = GetActorLocation();
	FVector PreNormal = PlayerLocation - coords * (1, 1, 1);
	FVector PostNormal = UKismetMathLibrary::Normal(PreNormal, .0001);
    	return PostNormal;
}