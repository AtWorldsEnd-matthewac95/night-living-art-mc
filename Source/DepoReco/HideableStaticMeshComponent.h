// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "HideableStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEPORECO_API UHideableStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool IsHidden();

	UFUNCTION(BlueprintCallable)
	virtual void Hide();

	UFUNCTION(BlueprintCallable)
	virtual void Unhide();
};
