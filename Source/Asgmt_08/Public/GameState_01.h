#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState_01.generated.h"


UCLASS()
class ASGMT_08_API AGameState_01 : public AGameState
{
	GENERATED_BODY()

public:
	AGameState_01();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameStatus")
	int32 PlayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStatus")
	float WaveDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameStatus")
	int32 CurrentWave;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameStatus")
	int32 MaxWave;

	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	void OnGameOver();
};
