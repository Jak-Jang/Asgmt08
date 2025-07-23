#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Waterjet.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class ASGMT_08_API AActor_Waterjet : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_Waterjet();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* SpawnMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ActiveMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ActivateDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float DestroyDelay;


protected:

	virtual void BeginPlay() override;

	bool bIsActive;

	FTimerHandle ActivateTimerHandle;
	FTimerHandle DestroyTimerHandle;

	UFUNCTION()
	void ActivateWaterjet();
	UFUNCTION()
	void DestroyWaterjet();
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
