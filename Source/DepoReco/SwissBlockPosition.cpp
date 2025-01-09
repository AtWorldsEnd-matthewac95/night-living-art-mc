// Fill out your copyright notice in the Description page of Project Settings.

#include "SwissBlockPosition.h"

ESwissBlockPosition IndexToSwissBlockPosition(int index)
{
    if (index < 0 || index > SBP_MAX_INDEX)
    {
        index = 0;
    }

    return (ESwissBlockPosition)(0x1 << index);
}

int SwissBlockPositionToIndex(ESwissBlockPosition position)
{
    int index = 0;

    if (position >= ESwissBlockPosition::SBP_0 && (int32)position <= SBP_MAX_VALUE)
    {
        auto posval = (int32)position;

        while (posval != 0x1 && posval > 0x0)
        {
            posval >>= 1;
            index++;
        }
    }

    return index;
}
