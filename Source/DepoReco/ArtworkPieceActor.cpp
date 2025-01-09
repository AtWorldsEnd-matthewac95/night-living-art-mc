// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtworkPieceActor.h"

AArtworkPieceActor::AArtworkPieceActor()
{
    PickupSound = nullptr;
}

UTexture2D* AArtworkPieceActor::GetInventoryTexture() const { return InventoryTexture; }

FString AArtworkPieceActor::GetInventoryName() const { return InventoryName; }

USoundBase* AArtworkPieceActor::PickUpWithSound()
{
    MakeInvisibleAndUninteractable();
    return PickupSound;
}
