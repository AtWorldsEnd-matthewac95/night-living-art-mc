// Copyright Epic Games, Inc. All Rights Reserved.

#include "DepoRecoGameModeBase.h"

void ADepoRecoGameModeBase::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);
}
