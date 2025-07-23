#include "SpawnActor_Mine.h"
#include "GameState_01.h"
#include "Kismet/KismetMathLibrary.h"


ASpawnActor_Mine::ASpawnActor_Mine()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawnAreaExtent = FVector(2000.0f, 2000.0f, 0.0f);
	SpawnDelay = 1.0f;
}

void ASpawnActor_Mine::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawnActor_Mine::SpawnActor,
		SpawnDelay,
		true
	);
}

FVector ASpawnActor_Mine::GetRandomLocation() const
{
	FVector SpawnOrigin = GetActorLocation();
	FVector RandomLocation
		= UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnAreaExtent);
	return RandomLocation;
}

void ASpawnActor_Mine::SpawnActor()
{
	if (!SpawnActorClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride
		= ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(
		SpawnActorClass,
		GetRandomLocation(),
		FRotator::ZeroRotator,
		SpawnParams);
}