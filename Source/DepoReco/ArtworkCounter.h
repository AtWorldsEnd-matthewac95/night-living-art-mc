// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArtworkGameState.h"
#include "Components/ActorComponent.h"
#include "ArtworkCounter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEPORECO_API UArtworkCounter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArtworkCounter();

protected:
	AArtworkGameState* GameState;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsTotalCounted() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCompleteCounted() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCorrectCounted() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTotalArtworkCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCompleteArtworkCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCorrectArtworkCount() const;

	UFUNCTION(BlueprintCallable)
	bool IncrementTotalArtworkCount();

	UFUNCTION(BlueprintCallable)
	bool IncrementCompleteArtworkCount();

	UFUNCTION(BlueprintCallable)
	bool IncrementCorrectArtworkCount();

	UFUNCTION(BlueprintCallable)
	bool DecrementTotalArtworkCount();

	UFUNCTION(BlueprintCallable)
	bool DecrementCompleteArtworkCount();

	UFUNCTION(BlueprintCallable)
	bool DecrementCorrectArtworkCount();
};
