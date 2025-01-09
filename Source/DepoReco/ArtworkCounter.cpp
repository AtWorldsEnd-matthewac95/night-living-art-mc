// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtworkCounter.h"

// Sets default values for this component's properties
UArtworkCounter::UArtworkCounter()
{
	GameState = nullptr;
}

// Called when the game starts
void UArtworkCounter::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GameState = GetWorld()->GetGameState<AArtworkGameState>();
	}
}

bool UArtworkCounter::IsTotalCounted() const { return GameState->IsCountedForTotalArtworks(GetUniqueID()); }
bool UArtworkCounter::IsCompleteCounted() const { return GameState->IsCountedForCompleteArtworks(GetUniqueID()); }
bool UArtworkCounter::IsCorrectCounted() const { return GameState->IsCountedForCorrectArtworks(GetUniqueID()); }
int UArtworkCounter::GetTotalArtworkCount() const { return GameState->GetTotalArtworkCount(); }
int UArtworkCounter::GetCompleteArtworkCount() const { return GameState->GetCompleteArtworkCount(); }
int UArtworkCounter::GetCorrectArtworkCount() const { return GameState->GetCorrectArtworkCount(); }
bool UArtworkCounter::IncrementTotalArtworkCount() { return GameState->IncrementTotalArtworkCount(GetUniqueID()); }
bool UArtworkCounter::IncrementCompleteArtworkCount() { return GameState->IncrementCompleteArtworkCount(GetUniqueID()); }
bool UArtworkCounter::IncrementCorrectArtworkCount() { return GameState->IncrementCorrectArtworkCount(GetUniqueID()); }
bool UArtworkCounter::DecrementTotalArtworkCount() { return GameState->DecrementTotalArtworkCount(GetUniqueID()); }
bool UArtworkCounter::DecrementCompleteArtworkCount() { return GameState->DecrementCompleteArtworkCount(GetUniqueID()); }
bool UArtworkCounter::DecrementCorrectArtworkCount() { return GameState->DecrementCorrectArtworkCount(GetUniqueID()); }
