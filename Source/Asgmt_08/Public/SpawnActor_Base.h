#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnActor_Base.generated.h"

class USceneComponent;

UCLASS()
class ASGMT_08_API ASpawnActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnActor_Base();
	
	virtual void Tick(float DeltaTime) override;

protected:
	float RandSpeed;
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOptions")
	FVector SpawnAreaExtent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOptions")
	float SpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnOptions")
	UDataTable* ItemDataTable;
	
	FItemSpawnRow* GetRandomActorFromDataTable() const;
	AActor* SpawnActorClass(TSubclassOf<AActor> ActorClass, FVector SpawnLocation);
	FVector GetRandomLocation() const;
	void SpawnActor();

	virtual void BeginPlay() override;
};
