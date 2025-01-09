// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ArtworkGameState.generated.h"

/**
 * 
 */
UCLASS()
class DEPORECO_API AArtworkGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	TSet<int32> TotalArtworksCounted;
	TSet<int32> CompleteArtworksCounted;
	TSet<int32> CorrectArtworksCounted;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTotalArtworkCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCompleteArtworkCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCorrectArtworkCount() const;

	/// <summary>
	/// Uses the given unique id to increment the total artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool IncrementTotalArtworkCount(const int32& countedId);

	/// <summary>
	/// Uses the given unique id to increment the completed artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool IncrementCompleteArtworkCount(const int32& countedId);

	/// <summary>
	/// Uses the given unique id to increment the corrected artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool IncrementCorrectArtworkCount(const int32& countedId);

	/// <summary>
	/// Uses the given unique id to decrement the total artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool DecrementTotalArtworkCount(const int32& countedId);

	/// <summary>
	/// Uses the given unique id to decrement the completed artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool DecrementCompleteArtworkCount(const int32& countedId);

	/// <summary>
	/// Uses the given unique id to decrement the corrected artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool DecrementCorrectArtworkCount(const int32& countedId);

	/// <summary>
	/// STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the given unique id is contributing to the total artwork count.
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCountedForTotalArtworks(const int32& countedId) const;

	/// <summary>
	/// STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the given unique id is contributing to the completed artwork count.
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCountedForCompleteArtworks(const int32& countedId) const;

	/// <summary>
	/// STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the given unique id is contributing to the corrected artwork count.
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCountedForCorrectArtworks(const int32& countedId) const;
};
