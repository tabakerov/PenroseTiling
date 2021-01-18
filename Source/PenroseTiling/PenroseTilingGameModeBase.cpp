// Copyright Epic Games, Inc. All Rights Reserved.


#include "PenroseTilingGameModeBase.h"

#include "MyPawn.h"
#include "MyPlayerController.h"

APenroseTilingGameModeBase::APenroseTilingGameModeBase()
{
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
