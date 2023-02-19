// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CosmoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COSOMODISE_REBUILD_API ACosmoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	ACosmoGameModeBase();

};

