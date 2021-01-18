// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class APenroseTilingGameModeBase;
class ATile;

UCLASS()
class PENROSETILING_API AMyPawn : public APawn
{
	GENERATED_BODY()

private:
	void Rotate(float Value);
	

	UPROPERTY()
	AActor* SelectedTile;

	UPROPERTY()
	APenroseTilingGameModeBase* MyGamemode;
	
public:
	// Sets default values for this pawn's properties
	AMyPawn();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Snap();
	void Unsnap();
	bool bSnapping;
	void AddTile();

	void HandleTileClicked(ATile* Tile);
};
