// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonHUD.h"

void AFirstPersonHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // Find the center of the canvas.
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        // Offset by half of the texture's dimensions so that te center of the texture aligns with the center of the canvas.
        FVector2D CrosshairDrawPosition(
            Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f),
            Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f)
        );

        // Draw the crosshair at the centerpoint.
        FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}
