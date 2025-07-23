#include "GameState_01.h"
#include "PlayerController_01.h"
#include "GameInstance_01.h"
#include "Player_Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/HorizontalBoxSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"


AGameState_01::AGameState_01()
{
	PlayTime = 0.0f;
	WaveDuration = 20.0f;
	CurrentWave = 1;
	MaxWave = 3;
	bIsMaxWave = false;
	bIsSpawnMine = false;
	bIsSpawnWaterjet = false;
}

void AGameState_01::BeginPlay()
{
	Super::BeginPlay();

	GameStart();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AGameState_01::UpdateHUD,
		0.1f,
		true
	);

	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&AGameState_01::NextWave,
		WaveDuration,
		true
	);
}

void AGameState_01::OnGameOver()
{
	GetWorldTimerManager().ClearTimer(HUDUpdateTimerHandle);
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (UGameInstance_01* GameInstance_01
		= Cast<UGameInstance_01>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GameInstance_01->FlyTime = PlayTime;
		GameInstance_01->ReturnToMenuLevel();
	}

	//if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	//{
	//	PlayerController->SetPause(true);
	//}
}

void AGameState_01::UpdateHUD()
{
	PlayTime += 0.1f;

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerController_01* PlayerController_01
			= Cast<APlayerController_01>(PlayerController))
		{
			if (UUserWidget* HUDWidget = PlayerController_01->GetHUDWidget())
			{
				if (UTextBlock* TimeText
					= Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					TimeText->SetText(FText::FromString(FString::Printf(
						TEXT("Time: %.1f"), PlayTime)));
				}

				if (UTextBlock* WaveText
					= Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
				{
					WaveText->SetText(FText::FromString(FString::Printf(
						TEXT("Wave %d"), CurrentWave)));
				}

				if (APlayer_Pawn* PlayerPawn
					= Cast<APlayer_Pawn>(PlayerController_01->GetPawn()))
				{
					int32 CurrentHP = PlayerPawn->GetHealth();
					int32 MaxHP = PlayerPawn->GetMaxHealth();

					UHorizontalBox* HeartContainer
						= Cast<UHorizontalBox>(HUDWidget->GetWidgetFromName(TEXT("HeartContainer")));
					if (HeartContainer)
					{
						HeartContainer->ClearChildren();
						for (int32 i = 0; i < MaxHP; i++)
						{
							UImage* HeartImage = NewObject<UImage>(HeartContainer);
							if (HeartImage)
							{
								HeartImage->SetDesiredSizeOverride(FVector2D(150.0f, 150.0f));
								UHorizontalBoxSlot* HBoxSlot
									= HeartContainer->AddChildToHorizontalBox(HeartImage);
								if (HBoxSlot)
								{
									HBoxSlot->SetPadding(FMargin(15.0f));
								}

								if (i < CurrentHP)
								{
									HeartImage->SetBrushFromTexture(PlayerController_01->HeartFull);
								}
								else
								{
									HeartImage->SetBrushFromTexture(PlayerController_01->HeartEmpty);
								}
							}
						}
					}
				}
			}
		}
	}
}

void AGameState_01::GameStart()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerController_01* PlayerController_01
			= Cast<APlayerController_01>(PlayerController))
		{
			PlayerController_01->ShowGameHUD();
		}
	}
}

void AGameState_01::NextWave()
{
	if (CurrentWave < MaxWave) CurrentWave++;

	if (bIsMaxWave)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Red,
			FString::Printf(TEXT("Keep Flying!!")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Red,
			FString::Printf(TEXT("Wave %d Start!!"), CurrentWave));
	}

	if (CurrentWave == MaxWave)
		bIsMaxWave = true;

	if (CurrentWave == 2 && !bIsSpawnMine)
	{
		if (!WaterjetActorClass) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride
			= ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(
			WaterjetActorClass,
			FVector(-1000.0f, 0.0f, 150.0f),
			FRotator::ZeroRotator,
			SpawnParams);

		bIsSpawnMine = true;
	}
	if (CurrentWave == 3 && !bIsSpawnWaterjet)
	{
		if (!MineActorClass) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride
			= ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(
			MineActorClass,
			FVector(-1000.0f, 0.0f, 150.0f),
			FRotator::ZeroRotator,
			SpawnParams);

		bIsSpawnWaterjet = true;
	}
}