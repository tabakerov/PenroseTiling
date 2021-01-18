// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"


#include "PenroseTilingGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	AGameModeBase* Gamemode = UGameplayStatics::GetGameMode(GetWorld());
	MyGamemode = Cast<APenroseTilingGameModeBase>(Gamemode);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("AddTile", EInputEvent::IE_Pressed, this, &AMyPawn::AddTile);
	PlayerInputComponent->BindAxis("Rotate", this, &AMyPawn::Rotate);
}

void AMyPawn::Rotate(float Value)
{
	if (Value != 0 && SelectedTile != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
		FRotator Rotator = FRotator(0, Value*36, 0);
		SelectedTile->AddActorLocalRotation(FQuat(Rotator));		
	}
}

void AMyPawn::AddTile()
{
	if (SelectedTile != nullptr)
	{
		return;
	}

	if (FMath::RandBool())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Kite"));
		GetWorld()->SpawnActor<ATile>(
			MyGamemode->KiteClass,
			FVector(0, 0, 0),
			FRotator::ZeroRotator);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Dart"));
		GetWorld()->SpawnActor<ATile>(
			MyGamemode->DartClass,
			FVector(0, 0, 0),
			FRotator::ZeroRotator);
	}
}

void AMyPawn::HandleTileClicked(ATile* Tile)
{
	if (SelectedTile == nullptr) // EMPTY HAND
	{
		SelectedTile = Tile;
		Tile->SetActive(true);
		UE_LOG(LogTemp, Warning, TEXT("Selected"));
	}
	else // ALREADY HAS SOMETHING
	{
		if (Tile == SelectedTile)
		{
			Tile->SetActive(false);
			SelectedTile = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Deselected"));

		}
	}
}
