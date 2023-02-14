// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RingBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnComponent), Blueprintable )
class COSOMODISE_REBUILD_API ARingBase : public AActor
{
	GENERATED_BODY()

			
public:	
	// Sets default values for this actor's properties
	ARingBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTurning = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
			FVector GetRingRotation() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FuelReward = 50;

};
