// Fill out your copyright notice in the Description page of Project Settings.

#include "SwissBlock.h"
#include "SwissBlockPositionMesh.h"

// Sets default values
ASwissBlock::ASwissBlock()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PositionalBitmask = 0;
	CompletionBitmask = 0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Mesh for incomplete block
	MeshForIncompleteBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForIncompleteBlock"));
	MeshForIncompleteBlock->SetupAttachment(RootComponent);

	// Mesh for complete block
	MeshForCompleteBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForCompleteBlock"));
	MeshForCompleteBlock->SetupAttachment(RootComponent);
	MeshForCompleteBlock->SetVisibility(false);

	// Create piece mesh map
	InitializePieceMeshes();
}

void ASwissBlock::InitializePieceMeshes()
{
	for (int i = 0; i <= SBP_MAX_INDEX; i++)
	{
		auto piece = CreateDefaultSubobject<USwissBlockPositionMesh>(FName(TEXT("PieceMesh") + FString::FromInt(i)));
		auto position = IndexToSwissBlockPosition(i);
		piece->Initialize(this, position);
		PieceMeshes.Add(position, piece);
		piece->SetupAttachment(RootComponent);
		piece->Hide();
	}
}

// Called when the game starts or when spawned
void ASwissBlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASwissBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASwissBlock::AssessCompleteness()
{
	if (CompletionBitmask <= 0)
	{
		CompletionBitmask = 0;
		for (auto position : CorrectPositions)
		{
			CompletionBitmask += (int32)position;
		}
	}

	bool isComplete = IsComplete();
	MeshForIncompleteBlock->SetVisibility(!isComplete);
	MeshForCompleteBlock->SetVisibility(isComplete);
	return isComplete;
}

int32 ASwissBlock::GetPositionalBitmask() const { return PositionalBitmask; }

bool ASwissBlock::IsComplete() const { return PositionalBitmask >= CompletionBitmask; }

bool ASwissBlock::IsCompletionCorrect() const { return PositionalBitmask == CompletionBitmask; }

bool ASwissBlock::OccupyPosition(ASwissBlockPiece* piece, bool useLocation, const FVector& worldLocation) { bool _; ESwissBlockPosition __; return OccupyPositionAndVerifyCorrect(piece, useLocation, worldLocation, _, __); }

bool ASwissBlock::OccupyPositionAndVerifyCorrect(ASwissBlockPiece* piece, bool useLocation, const FVector& worldLocation, bool& isCorrect, ESwissBlockPosition& occupiedPosition)
{
	bool isOccupying = false;
	bool isMapped = piece->FindMappedPosition(this, occupiedPosition);
	isCorrect = CorrectPositions.Contains(occupiedPosition);

	bool isFixed = (isMapped && (isCorrect || FixedPositions.Contains(occupiedPosition)));

	if ((isFixed || FindNextVacantPosition(occupiedPosition)) && !PiecesOccupyingPositions.Contains(occupiedPosition))
	{
		isOccupying = true;
		PiecesOccupyingPositions.Add(occupiedPosition, piece);

		if ((PositionalBitmask & (int32)occupiedPosition) == 0)
		{
			PositionalBitmask += (int32)occupiedPosition;
		}

		if (auto mesh = PieceMeshes[occupiedPosition])
		{
			mesh->Unhide();
			mesh->SetStaticMesh(piece->GetStaticMesh());
			auto pieceMaterials = piece->GetMaterials();

			for (int i = 0; i < pieceMaterials.Num(); i++)
			{
				mesh->SetMaterial(i, pieceMaterials[i]);
			}

			if (!isFixed && useLocation)
			{
				mesh->SetWorldLocation(worldLocation);
			}
		}

		AssessCompleteness();
	}

	return isOccupying;
}

bool ASwissBlock::VacatePosition(const ESwissBlockPosition position) { ASwissBlockPiece* _ = nullptr; return VacatePositionAndGetPiece(position, _); }

bool ASwissBlock::VacatePositionAndGetPiece(const ESwissBlockPosition position, ASwissBlockPiece*& outputPieceAtPosition)
{
	bool isVacating = false;

	if (PiecesOccupyingPositions.Contains(position))
	{
		isVacating = true;
		PiecesOccupyingPositions.RemoveAndCopyValue(position, outputPieceAtPosition);

		if ((PositionalBitmask & (int32)position) != 0)
		{
			PositionalBitmask -= (int32)position;
		}

		if (auto mesh = PieceMeshes[position])
		{
			mesh->Hide();
		}

		AssessCompleteness();
	}

	return isVacating;
}

bool ASwissBlock::IsPositionOccupied(const ESwissBlockPosition position) const
{
	return PiecesOccupyingPositions.Contains(position);
}

bool ASwissBlock::FindNextVacantPosition(ESwissBlockPosition& outputPosition) const
{
	for (int i = 0; i <= SBP_MAX_INDEX; i++) {
		auto position = IndexToSwissBlockPosition(i);

		if (!CorrectPositions.Contains(position) && !FixedPositions.Contains(position) && !IsPositionOccupied(position))
		{
			outputPosition = position;
			return true;
		}
	}
	return false;
}
