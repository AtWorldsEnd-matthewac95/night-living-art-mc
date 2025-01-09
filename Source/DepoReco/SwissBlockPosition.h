// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(Meta = (BlueprintType, Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ESwissBlockPosition: uint8
{
    SBP_NONE = 0x00,
    SBP_0 = 0x01,
    SBP_1 = 0x02,
    SBP_2 = 0x04,
    SBP_3 = 0x08,
    SBP_4 = 0x10,
    SBP_5 = 0x20,
    SBP_6 = 0x40,
    SBP_7 = 0x80
};

const int32 SBP_MAX_VALUE = 0xFF;
const int SBP_MAX_INDEX = 7;

ESwissBlockPosition IndexToSwissBlockPosition(int);
int SwissBlockPositionToInt(ESwissBlockPosition);
