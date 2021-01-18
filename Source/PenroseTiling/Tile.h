// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MyPawn.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/TriggerSphere.h"

#include "Tile.generated.h"

UCLASS()
class PENROSETILING_API ATile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SphereSlot;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* BaseMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* ActiveMaterial;

	UPROPERTY()
	AMyPawn* Pawn;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* TriggerSphere;

	bool bActive;

	UFUNCTION()
	void HandleClick(UPrimitiveComponent* Component, FKey Key);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetActive(bool bActive);
	
};

