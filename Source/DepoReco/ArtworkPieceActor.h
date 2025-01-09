// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwissBlockPiece.h"
#include "ArtworkPieceActor.generated.h"

/**
 * 
 */
UCLASS()
class DEPORECO_API AArtworkPieceActor : public ASwissBlockPiece
{
	GENERATED_BODY()

public:
	AArtworkPieceActor();

protected:
	UPROPERTY(EditAnywhere, Category="ArtworkPieceActor")
	UTexture2D* InventoryTexture;

	UPROPERTY(EditAnywhere, Category="ArtworkPieceActor")
	FString InventoryName;

	UPROPERTY(EditAnywhere, Category = Audio)
	USoundBase* PickupSound;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTexture2D* GetInventoryTexture() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetInventoryName() const;

	UFUNCTION(BlueprintCallable)
	USoundBase* PickUpWithSound();
};
