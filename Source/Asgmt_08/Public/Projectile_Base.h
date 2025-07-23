#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ASGMT_08_API AProjectile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile_Base();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float MoveSpeed;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName ActorType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* Sphere;

	FTimerHandle DeleteTimerHandle;

	UFUNCTION()
	void DeleteActor();

	UFUNCTION()
	void OnProjectileOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnProjectileEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	virtual void BeginPlay() override;
	virtual void Activated(AActor* Activator);
};
