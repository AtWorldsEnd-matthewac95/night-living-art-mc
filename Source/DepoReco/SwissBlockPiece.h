// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwissBlockPosition.h"
#include "SwissBlockPieceReceiver.h"
#include "GameFramework/Actor.h"
#include "SwissBlockPiece.generated.h"

UCLASS()
class DEPORECO_API ASwissBlockPiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwissBlockPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SwissBlockPiece")
	TMap<int, TSubclassOf<ASwissBlockPieceReceiver>> ArtworkTypeMappings;

	// Mapping of artwork types to positions.
	UPROPERTY(EditAnywhere, Category = "SwissBlockPiece")
	TMap<int, ESwissBlockPosition> BlockPositionMappings;

	// Piece mesh component
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* MeshComponent;

	UStaticMesh* PreviousStaticMesh;
	TArray<UMaterialInterface*> PreviousMaterials;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets the static mesh of the mesh component, or the previous static mesh if that is currently null.
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetStaticMesh() const;

	// Gets the materials of the mesh component, or the previous materials if those don't exist.
	UFUNCTION(BlueprintCallable)
	TArray<UMaterialInterface*> GetMaterials() const;

	// Returns false if this piece has no association with the given block, or true otherwise. If returning true, the given position field will have the associated position.
	UFUNCTION(BlueprintCallable)
	bool FindMappedPosition(const ASwissBlockPieceReceiver* block, ESwissBlockPosition& outputPosition) const;

	// Makes the piece invisible and uninteractable.
	UFUNCTION(BlueprintCallable)
	void MakeInvisibleAndUninteractable();

	// Makes the piece visible and interactable.
	UFUNCTION(BlueprintCallable)
	void MakeVisibleAndInteractable();
};
