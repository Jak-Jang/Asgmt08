#include "Projectile_Base.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AProjectile_Base::AProjectile_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	Mesh->SetupAttachment(RootComponent);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile_Base::OnProjectileOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AProjectile_Base::OnProjectileEndOverlap);

	MoveSpeed = 500.0f;
}

void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		DeleteTimerHandle,
		this,
		&AProjectile_Base::DeleteActor,
		15.0f,
		false
	);
}

void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move
	AddActorWorldOffset(FVector(MoveSpeed * DeltaTime * -1, 0.0f, 0.0f));
}

void AProjectile_Base::OnProjectileOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!")));
		Activated(OtherActor);
	}
}

void AProjectile_Base::OnProjectileEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void AProjectile_Base::DeleteActor()
{
	Destroy();
}

void AProjectile_Base::Activated(AActor* Activator) {}