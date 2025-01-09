// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorWithSound.h"

// Sets default values
AActorWithSound::AActorWithSound()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sound = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
}

USoundBase* AActorWithSound::GetSound() const { return Sound; }
