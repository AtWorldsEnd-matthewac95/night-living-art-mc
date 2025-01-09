// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwissBlock.h"
#include "HideableStaticMeshComponent.h"
#include "SwissBlockPositionMesh.generated.h"

/**
 * 
 */
UCLASS()
class DEPORECO_API USwissBlockPositionMesh : public UHideableStaticMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SBPosition")
	ESwissBlockPosition SBPosition;

	bool bInitialized;
	ASwissBlock* SwissBlockParent;

public:
	bool Initialize(ASwissBlock* Parent, ESwissBlockPosition Position);

	UFUNCTION(BlueprintCallable)
	ESwissBlockPosition GetSBPosition() const;

	virtual void Hide() override;

	UFUNCTION(BlueprintCallable)
	virtual bool HideAndGetPiece(ASwissBlockPiece*& outputPiece);
};
