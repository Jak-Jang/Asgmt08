#include "SpawnActor_Base.h"
#include "Projectile_Base.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DataTable.h"
#include "ItemSpawnRow.h"


ASpawnActor_Base::ASpawnActor_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	RandSpeed = 1.0f;
	SpawnAreaExtent = FVector(0.0f, 4000.f, 0.0f);
	SpawnDelay = 1.5f;
}

void ASpawnActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawnActor_Base::SpawnActor,
		SpawnDelay,
		true
	);
}

void ASpawnActor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RandSpeed = FMath::RandRange(1.0f, 2.0f);
}

FItemSpawnRow* ASpawnActor_Base::GetRandomActorFromDataTable() const
{
	if (!ItemDataTable) return nullptr;

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("SpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}


FVector ASpawnActor_Base::GetRandomLocation() const
{
	FVector SpawnOrigin = GetActorLocation();
	FVector RandomLocation
		= UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnAreaExtent);
	return RandomLocation;
}

AActor* ASpawnActor_Base::SpawnActorClass(TSubclassOf<AActor> ActorClass, FVector SpawnLocation)
{
	if (!ActorClass) return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride 
		= ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>
		(
			ActorClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams);

	return SpawnedActor;
}

void ASpawnActor_Base::SpawnActor()
{
	FItemSpawnRow* SelectedRow = GetRandomActorFromDataTable();

	if (SelectedRow)
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			FVector SpawnLocation = GetRandomLocation();
			AActor* SpawnedActor = SpawnActorClass(ActualClass, SpawnLocation);

			if (SpawnedActor)
			{
				AProjectile_Base* Projectile = Cast<AProjectile_Base>(SpawnedActor);
				if (Projectile)
				{
					Projectile->MoveSpeed *= RandSpeed;
				}
			}
		}
	}
}

