#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_01.generated.h"


UCLASS()
class ASGMT_08_API UGameInstance_01 : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "LevelManagement")
	FName MenuLevelName;
	UPROPERTY(EditDefaultsOnly, Category = "LevelManagement")
	FName GameLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstanceTime")
	double FlyTime;

	UFUNCTION(BlueprintCallable, Category = "LevelManagement")
	void GoToGameLevel();
	UFUNCTION(BlueprintCallable, Category = "LevelManagement")
	void ReturnToMenuLevel();

	bool bIsRestart;

protected:


	virtual void Init() override;
};
