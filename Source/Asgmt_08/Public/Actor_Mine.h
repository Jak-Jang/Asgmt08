#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Mine.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class ASGMT_08_API AActor_Mine : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_Mine();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	USphereComponent* Sphere;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UParticleSystem* ActivateParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ActivateDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float DestroyDelay;


protected:

	virtual void BeginPlay() override;

	bool bIsActive;

	FTimerHandle ActivateTimerHandle;
	FTimerHandle DestroyTimerHandle;

	UFUNCTION(BlueprintImplementableEvent, Category = "MineFunc")
	void ChangeMaterial();
	UFUNCTION(BlueprintCallable, Category = "MineFunc")
	void ActivateMine();
	UFUNCTION()
	void ExplodeMine();
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
