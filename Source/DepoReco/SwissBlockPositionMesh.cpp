// Fill out your copyright notice in the Description page of Project Settings.

#include "SwissBlockPositionMesh.h"

bool USwissBlockPositionMesh::Initialize(ASwissBlock* Parent, ESwissBlockPosition Position)
{
    if (bInitialized)
    {
        return false;
    }

    SwissBlockParent = Parent;
    SBPosition = Position;
    return true;
}

void USwissBlockPositionMesh::Hide()
{
    Super::Hide();

    this->SetStaticMesh(nullptr);
    SwissBlockParent->VacatePosition(SBPosition);
}

bool USwissBlockPositionMesh::HideAndGetPiece(ASwissBlockPiece*& outputPiece)
{
    Super::Hide();

    return SwissBlockParent->VacatePositionAndGetPiece(SBPosition, outputPiece);
}

ESwissBlockPosition USwissBlockPositionMesh::GetSBPosition() const { return SBPosition; }
