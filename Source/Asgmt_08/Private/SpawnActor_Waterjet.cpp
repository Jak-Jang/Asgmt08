#include "SpawnActor_Waterjet.h"
#include "GameState_01.h"
#include "Kismet/KismetMathLibrary.h"


ASpawnActor_Waterjet::ASpawnActor_Waterjet()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawnAreaExtent = FVector(2000.0f, 0.0f, 0.0f);
	SpawnDelay = 2.0f;
}

void ASpawnActor_Waterjet::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawnActor_Waterjet::SpawnActor,
		SpawnDelay,
		true
	);
}

FVector ASpawnActor_Waterjet::GetRandomLocation() const
{
	FVector SpawnOrigin = GetActorLocation();
	FVector RandomLocation
		= UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnAreaExtent);
	return RandomLocation;
}

void ASpawnActor_Waterjet::SpawnActor()
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