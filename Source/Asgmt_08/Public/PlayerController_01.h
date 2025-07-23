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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* HUDWidgetInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|HP")
	UTexture2D* HeartFull;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|HP")
	UTexture2D* HeartEmpty;

	UFUNCTION(BlueprintPure, Category = "UI")
	UUserWidget* GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowMainMenu(bool bIsRestart);

protected:
	virtual void BeginPlay() override;
};
