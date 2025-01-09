// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArtworkCounter.h"
#include "SwissBlock.h"
#include "ArtworkActor.generated.h"

/**
 * 
 */
UCLASS()
class DEPORECO_API AArtworkActor : public ASwissBlock
{
	GENERATED_BODY()

public:
	AArtworkActor();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "ArtworkActor")
	UArtworkCounter* Counter;

	TSet<ESwissBlockPosition> UniqueSoundPlayHistory;

	UPROPERTY(EditAnywhere, Category = Audio)
	TMap<ESwissBlockPosition, USoundBase*> UniqueSounds;

	virtual bool AssessCompleteness() override;
	virtual void InitializePieceMeshes() override;

public:
	UFUNCTION(BlueprintCallable)
	void ClearUniqueSoundPlayHistory();

	UFUNCTION(BlueprintCallable)
	void ClearSpecificUniqueSoundPlayHistory(const ESwissBlockPosition position);

	UFUNCTION(BlueprintCallable)
	bool GetUniqueSoundForPlaying(const ESwissBlockPosition position, USoundBase*& outputUniqueSound);
};
