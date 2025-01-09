// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ActorWithSound.generated.h"

UCLASS()
class DEPORECO_API AActorWithSound : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorWithSound();

protected:
	UPROPERTY(EditAnywhere, Category = Audio)
	USoundBase* Sound;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* Collision;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USoundBase* GetSound() const;
};
