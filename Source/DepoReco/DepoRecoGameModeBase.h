// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DepoRecoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEPORECO_API ADepoRecoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
