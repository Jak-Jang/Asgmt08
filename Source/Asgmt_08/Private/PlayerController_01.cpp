#include "PlayerController_01.h"
#include "GameState_01.h"
#include "GameInstance_01.h"
#include "EnhancedInputSubSystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"


APlayerController_01::APlayerController_01()
	: InputMappingContext(nullptr), 
	MoveAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}


void APlayerController_01::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance_01* GameInstance_01
		= Cast<UGameInstance_01>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance_01) return;

	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	if (CurrentLevelName.Equals(GameInstance_01->MenuLevelName.ToString()))
	{
		ShowMainMenu(GameInstance_01->bIsRestart);
	}
	else if (CurrentLevelName.Equals(GameInstance_01->GameLevelName.ToString()))
	{
		ShowGameHUD();
	}
	else
	{
		ShowGameHUD();
	}

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

}

void APlayerController_01::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromViewport();
		HUDWidgetInstance = nullptr;
	}
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromViewport();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
			//SetPause(false);
		}
	}

	AGameState_01* GameState = GetWorld() ? GetWorld()->GetGameState<AGameState_01>() : nullptr;
	if (GameState) GameState->UpdateHUD();
}


void APlayerController_01::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromViewport();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromViewport();
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
			//SetPause(true);
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart) ButtonText->SetText(FText::FromString(TEXT("Restart")));
			else ButtonText->SetText(FText::FromString(TEXT("Start")));
		}

		if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}
		}
	}
}

UUserWidget* APlayerController_01::GetHUDWidget() const
{
	return HUDWidgetInstance;
}