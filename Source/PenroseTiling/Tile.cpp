// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ATile::ATile()
{
	bActive = false;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);


	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	
	MeshComponent->SetMaterial(0, BaseMaterial);
	MeshComponent->OnClicked.AddDynamic(this, &ATile::HandleClick);

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlap);
	
}

void ATile::HandleClick(UPrimitiveComponent* Component, FKey Key)
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger's location: %f %f %f"), TriggerSphere->GetComponentLocation().X, TriggerSphere->GetComponentLocation().Y, TriggerSphere->GetComponentLocation().Z);
	UE_LOG(LogTemp, Warning, TEXT("Clicked!"));
	if (Component != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("I'm a %s"), *Component->GetOwner()->GetName());
		Pawn->HandleTileClicked(this);
	}
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	APawn* SomePawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (SomePawn != nullptr)
	{
		Pawn = Cast<AMyPawn>(SomePawn);
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bActive)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC != nullptr)
		{
			FVector Start, Dir;
			bool Ok = PC->DeprojectMousePositionToWorld(Start, Dir);
			if (Ok)
			{
				float Cosine = FVector::DotProduct(Dir, FVector(0, 0, -1));
				float Sine = FMath::Sqrt(1 - Cosine*Cosine);
				FVector CamPos = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
				MeshComponent->GetOwner()->SetActorLocation(Start+ CamPos.Z*Dir/Cosine);
				//UE_LOG(LogTemp, Warning, TEXT("Cos: %f, Height: %f"), Cosine, CamPos.Z);
			}
		}
	}
}

inline void ATile::SetActive(bool IsActive)
{
	bActive = IsActive;
	if (IsActive)
	{		
		MeshComponent->SetMaterial(0, ActiveMaterial);
	} else
	{
		MeshComponent->SetMaterial(0, BaseMaterial);
	}
}


void ATile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP with %s || %s || %s "), *OverlappedComponent->GetName(), *OtherActor->GetName(), *OtherComp->GetName());
	if (bActive)
	{
		
		FVector OtherLocation = OtherComp->GetComponentLocation();
		//this->AddActorWorldOffset(-(OverlappedComponent->GetComponentLocation() - OtherLocation));
		this->SetActorLocation(this->GetActorLocation() - (OverlappedComponent->GetComponentLocation() - OtherLocation) );
		//bActive = false;
		Pawn->HandleTileClicked(this);
		TriggerSphere->OnComponentBeginOverlap.RemoveDynamic(this, &ATile::OnOverlap);
	}
	
}