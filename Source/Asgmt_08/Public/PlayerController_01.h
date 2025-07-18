#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_01.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ASGMT_08_API APlayerController_01 : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerController_01();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

protected:
	virtual void BeginPlay() override;
	
};
