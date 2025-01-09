// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtworkActor.h"
#include "ArtworkPositionMesh.h"

AArtworkActor::AArtworkActor()
{
	Counter = CreateDefaultSubobject<UArtworkCounter>(TEXT("Counter"));
}

bool AArtworkActor::AssessCompleteness()
{
	bool result = ASwissBlock::AssessCompleteness();

	if (IsComplete())
	{
		Counter->IncrementCompleteArtworkCount();
	}
	else
	{
		Counter->DecrementCompleteArtworkCount();
	}

	if (IsCompletionCorrect())
	{
		Counter->IncrementCorrectArtworkCount();
	}
	else
	{
		Counter->DecrementCorrectArtworkCount();
	}

	return result;
}

void AArtworkActor::InitializePieceMeshes()
{
	for (int i = 0; i <= SBP_MAX_INDEX; i++)
	{
		auto piece = CreateDefaultSubobject<UArtworkPositionMesh>(FName(TEXT("PieceMesh") + FString::FromInt(i)));
		auto position = IndexToSwissBlockPosition(i);
		piece->Initialize(this, position);
		PieceMeshes.Add(position, piece);
		piece->SetupAttachment(RootComponent);
		piece->Hide();
	}
}

void AArtworkActor::ClearUniqueSoundPlayHistory()
{
	UniqueSoundPlayHistory.Empty();
}

void AArtworkActor::ClearSpecificUniqueSoundPlayHistory(const ESwissBlockPosition position)
{
	UniqueSoundPlayHistory.Remove(position);
}

bool AArtworkActor::GetUniqueSoundForPlaying(const ESwissBlockPosition position, USoundBase*& outputUniqueSound)
{
	bool success = (CorrectPositions.Contains(position) || FixedPositions.Contains(position)) && UniqueSounds.Contains(position) && !UniqueSoundPlayHistory.Contains(position);

	if (success)
	{
		outputUniqueSound = *(UniqueSounds.Find(position));
		UniqueSoundPlayHistory.Add(position);
	}

	return success;
}
