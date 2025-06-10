// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UTUITalkInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUTUITalkInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJ_UNTE_API IUTUITalkInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void TalkStart() = 0;
	virtual void TalkEnd() = 0;
};
