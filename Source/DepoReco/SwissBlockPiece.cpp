// Fill out your copyright notice in the Description page of Project Settings.

#include "SwissBlockPiece.h"
#include "ArtworkActor.h"

// Sets default values
ASwissBlockPiece::ASwissBlockPiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	PreviousStaticMesh = nullptr;
 }

// Called when the game starts or when spawned
void ASwissBlockPiece::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASwissBlockPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UStaticMesh* ASwissBlockPiece::GetStaticMesh() const
{
	auto currentMesh = MeshComponent->GetStaticMesh();
	return currentMesh ? currentMesh : PreviousStaticMesh;
}

TArray<UMaterialInterface*> ASwissBlockPiece::GetMaterials() const
{
	auto currentMaterials = MeshComponent->GetMaterials();
	return currentMaterials.Num() > 0 ? currentMaterials : PreviousMaterials;
}

bool ASwissBlockPiece::FindMappedPosition(const ASwissBlockPieceReceiver* block, ESwissBlockPosition& outputPosition) const
{
	bool isFound = false;
	for (const TPair<int, ESwissBlockPosition>& mapping : BlockPositionMappings)
	{
		if (block->IsA(ArtworkTypeMappings[mapping.Key]))
		{
			isFound = true;
			outputPosition = mapping.Value;
			break;
		}
	}
	return isFound;
}

void ASwissBlockPiece::MakeInvisibleAndUninteractable()
{
	PreviousStaticMesh = MeshComponent->GetStaticMesh();
	PreviousMaterials = MeshComponent->GetMaterials();
	MeshComponent->SetVisibility(false);
	MeshComponent->SetStaticMesh(nullptr);
}

void ASwissBlockPiece::MakeVisibleAndInteractable()
{
	MeshComponent->SetVisibility(true);

	if (PreviousStaticMesh)
	{
		MeshComponent->SetStaticMesh(PreviousStaticMesh);
		PreviousStaticMesh = nullptr;
	}

	for (int i = 0; i < PreviousMaterials.Num(); i++)
	{
		MeshComponent->SetMaterial(i, PreviousMaterials[i]);
	}
	PreviousMaterials.Empty();
}
