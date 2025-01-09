// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwissBlockPiece.h"
#include "HideableStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "SwissBlock.generated.h"

UCLASS()
class DEPORECO_API ASwissBlock : public ASwissBlockPieceReceiver
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwissBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Represents the current positions being occupied in this block.
	int32 PositionalBitmask;

	// Represents the value of OccupiedPositions when the block is complete.
	int32 CompletionBitmask;

	TMap<ESwissBlockPosition, ASwissBlockPiece*> PiecesOccupyingPositions;

	// Incomplete block mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* MeshForIncompleteBlock;

	// Complete block mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* MeshForCompleteBlock;

	// Array for the pieces of the block to reappear
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TMap<ESwissBlockPosition, UHideableStaticMeshComponent*> PieceMeshes;

	UFUNCTION(BlueprintCallable)
	virtual bool AssessCompleteness();

	virtual void InitializePieceMeshes();

	UFUNCTION(BlueprintCallable)
	bool FindNextVacantPosition(ESwissBlockPosition& outputPosition) const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// List of position placements which constitute as correct for this block
	UPROPERTY(EditAnywhere, Category = "SwissBlock")
	TSet<ESwissBlockPosition> CorrectPositions;

	// List of position placements which should not result in random placement. CorrectPositions is automatically considered along this list for that calculation.
	UPROPERTY(EditAnywhere, Category = "SwissBlock")
	TSet<ESwissBlockPosition> FixedPositions;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetPositionalBitmask() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsComplete() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCompletionCorrect() const;

	UFUNCTION(BlueprintCallable)
	bool OccupyPosition(ASwissBlockPiece* piece, bool useLocation, const FVector& worldLocation);

	UFUNCTION(BlueprintCallable)
	bool OccupyPositionAndVerifyCorrect(ASwissBlockPiece* piece, bool useLocation, const FVector& worldLocation, bool& isCorrect, ESwissBlockPosition& occupiedPosition);

	UFUNCTION(BlueprintCallable)
	bool VacatePosition(const ESwissBlockPosition position);

	UFUNCTION(BlueprintCallable)
	bool VacatePositionAndGetPiece(const ESwissBlockPosition position, ASwissBlockPiece*& outputPieceAtPosition);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsPositionOccupied(const ESwissBlockPosition position) const;
};
