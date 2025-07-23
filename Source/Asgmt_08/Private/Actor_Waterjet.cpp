#include "Actor_Waterjet.h"
#include "Player_Pawn.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AActor_Waterjet::AActor_Waterjet()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	SpawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnMesh"));
	SpawnMesh->SetupAttachment(RootComponent);
	SpawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ActiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActiveMesh"));
	ActiveMesh->SetupAttachment(RootComponent);
	ActiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActiveMesh->SetVisibility(false);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AActor_Waterjet::OnOverlapBegin);

	ActivateDelay = 3.0f;
	DestroyDelay = 2.0f;
	bIsActive = false;
}

void AActor_Waterjet::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		ActivateTimerHandle,
		this,
		&AActor_Waterjet::ActivateWaterjet,
		ActivateDelay,
		false
	);
}

void AActor_Waterjet::ActivateWaterjet()
{
	bIsActive = true;

	SpawnMesh->SetVisibility(false);
	ActiveMesh->SetVisibility(true);

	GetWorldTimerManager().SetTimer(
		DestroyTimerHandle,
		this,
		&AActor_Waterjet::DestroyWaterjet,
		DestroyDelay,
		false);
}

void AActor_Waterjet::DestroyWaterjet()
{
	GetWorldTimerManager().ClearTimer(ActivateTimerHandle);
	GetWorldTimerManager().ClearTimer(DestroyTimerHandle);

	Destroy();
}

void AActor_Waterjet::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bIsActive)
	{
		if (OtherActor && OtherActor->ActorHasTag("Player"))
		{
			if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(OtherActor))
			{
				Player->TakeDamage(1);
				DestroyWaterjet();
			}
		}
	}
}
