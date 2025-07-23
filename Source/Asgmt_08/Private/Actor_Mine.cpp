#include "Actor_Mine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Player_Pawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


AActor_Mine::AActor_Mine()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AActor_Mine::OnOverlapBegin);

	ActivateDelay = 2.0f;
	DestroyDelay = 3.0f;
	bIsActive = false;
}

void AActor_Mine::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(
		ActivateTimerHandle,
		this,
		&AActor_Mine::ActivateMine,
		ActivateDelay,
		false
	);
}

void AActor_Mine::ActivateMine()
{
	bIsActive = true;

	GetWorldTimerManager().SetTimer(
		DestroyTimerHandle,
		this,
		&AActor_Mine::ExplodeMine,
		DestroyDelay,
		false);

	ChangeMaterial();
}

void AActor_Mine::ExplodeMine()
{
	UParticleSystemComponent* Particle = nullptr;

	if (ActivateParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ActivateParticle,
			GetActorLocation(),
			GetActorRotation(),
			false
		);
		if (Particle)TWeakObjectPtr<UParticleSystemComponent> WeakParticle(Particle);
	}

	GetWorldTimerManager().ClearTimer(ActivateTimerHandle);
	GetWorldTimerManager().ClearTimer(DestroyTimerHandle);

	Destroy();
}

void AActor_Mine::OnOverlapBegin(
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
				ExplodeMine();
			}
		}
	}
}

