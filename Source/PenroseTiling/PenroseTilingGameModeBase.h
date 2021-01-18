// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Tile.h"
#include "GameFramework/GameModeBase.h"
#include "PenroseTilingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PENROSETILING_API APenroseTilingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APenroseTilingGameModeBase();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATile> KiteClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATile> DartClass;

};
