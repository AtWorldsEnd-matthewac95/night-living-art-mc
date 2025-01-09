// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtworkGameState.h"

int AArtworkGameState::GetTotalArtworkCount() const { return TotalArtworksCounted.Num(); }
int AArtworkGameState::GetCompleteArtworkCount() const { return CompleteArtworksCounted.Num(); }
int AArtworkGameState::GetCorrectArtworkCount() const { return CorrectArtworksCounted.Num(); }

/// <summary>
/// Uses the given unique id to increment the total artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
/// </summary>
bool AArtworkGameState::IncrementTotalArtworkCount(const int32& countedId)
{
    bool isNotIncremented = true;
    TotalArtworksCounted.Add(countedId, &isNotIncremented);
    return !isNotIncremented;
}

/// <summary>
/// Uses the given unique id to increment the completed artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
/// </summary>
bool AArtworkGameState::IncrementCompleteArtworkCount(const int32& countedId)
{
    bool isNotIncremented = true;
    CompleteArtworksCounted.Add(countedId, &isNotIncremented);
    return !isNotIncremented;
}

/// <summary>
/// Uses the given unique id to increment the corrected artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
/// </summary>
bool AArtworkGameState::IncrementCorrectArtworkCount(const int32& countedId)
{
    bool isNotIncremented = true;
    CorrectArtworksCounted.Add(countedId, &isNotIncremented);
    return !isNotIncremented;
}

/// <summary>
/// Uses the given unique id to decrement the total artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
/// </summary>
bool AArtworkGameState::DecrementTotalArtworkCount(const int32& countedId)
{
    bool isDecremented = false;

    if (TotalArtworksCounted.Contains(countedId))
    {
        TotalArtworksCounted.Remove(countedId);
        isDecremented = true;
    }

    return isDecremented;
}

/// <summary>
/// Uses the given unique id to decrement the completed artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
/// </summary>
bool AArtworkGameState::DecrementCompleteArtworkCount(const int32& countedId)
{
    bool isDecremented = false;

    if (CompleteArtworksCounted.Contains(countedId))
    {
        CompleteArtworksCounted.Remove(countedId);
        isDecremented = true;
    }

    return isDecremented;
}

/// <summary>
/// Uses the given unique id to decrement the corrected artwork count. STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the count is incremented.
/// </summary>
bool AArtworkGameState::DecrementCorrectArtworkCount(const int32& countedId)
{
    bool isDecremented = false;

    if (CorrectArtworksCounted.Contains(countedId))
    {
        CorrectArtworksCounted.Remove(countedId);
        isDecremented = true;
    }

    return isDecremented;
}

/// <summary>
/// STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the given unique id is contributing to the total artwork count.
/// </summary>
bool AArtworkGameState::IsCountedForTotalArtworks(const int32& countedId) const { return TotalArtworksCounted.Contains(countedId); }

/// <summary>
/// STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the given unique id is contributing to the completed artwork count.
/// </summary>
bool AArtworkGameState::IsCountedForCompleteArtworks(const int32& countedId) const { return CompleteArtworksCounted.Contains(countedId); }

/// <summary>
/// STRONGLY recommended to only use unique ids of ArtworkCounter components. Returns true if the given unique id is contributing to the corrected artwork count.
/// </summary>
bool AArtworkGameState::IsCountedForCorrectArtworks(const int32& countedId) const { return CorrectArtworksCounted.Contains(countedId); }
