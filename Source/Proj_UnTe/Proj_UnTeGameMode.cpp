// Copyright Epic Games, Inc. All Rights Reserved.

#include "Proj_UnTeGameMode.h"
#include "Proj_UnTePlayerController.h"
#include "Proj_UnTeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProj_UnTeGameMode::AProj_UnTeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProj_UnTePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}