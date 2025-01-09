// Fill out your copyright notice in the Description page of Project Settings.

#include "HideableStaticMeshComponent.h"

bool UHideableStaticMeshComponent::IsHidden() { return !IsVisible(); }

void UHideableStaticMeshComponent::Hide() { SetVisibility(false); }

void UHideableStaticMeshComponent::Unhide() { SetVisibility(true); }
