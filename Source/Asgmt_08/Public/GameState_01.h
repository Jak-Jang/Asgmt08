#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState_01.generated.h"

class ASpawnActor_Base;

UCLASS()
class ASGMT_08_API AGameState_01 : public AGameState
{
	GENERATED_BODY()

public:
	AGameState_01();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameStatus")
	double PlayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStatus")
	float WaveDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameStatus")
	int32 CurrentWave;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameStatus")
	int32 MaxWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStatus")
	TSubclassOf<AActor> WaterjetActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStatus")
	TSubclassOf<AActor> MineActorClass;

	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void OnGameOver();
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void UpdateHUD();
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GameStart();
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void NextWave();

protected:
	virtual void BeginPlay() override;

	bool bIsMaxWave;
	bool bIsSpawnMine;
	bool bIsSpawnWaterjet;
};
