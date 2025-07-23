#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor_Waterjet.generated.h"

UCLASS()
class ASGMT_08_API ASpawnActor_Waterjet : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnActor_Waterjet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOptions")
	float SpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOptions")
	TSubclassOf<AActor> SpawnActorClass;

protected:
	virtual void BeginPlay() override;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Scene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnOptions")
	FVector SpawnAreaExtent;

	FVector GetRandomLocation() const;
	void SpawnActor();
};
