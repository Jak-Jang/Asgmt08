#include "GameInstance_01.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


void UGameInstance_01::Init()
{
	Super::Init();

	MenuLevelName = TEXT("Menu_Level");
	GameLevelName = TEXT("Base_Level");
	FlyTime = 0;
	bIsRestart = false;
}

void UGameInstance_01::GoToGameLevel()
{
	bIsRestart = false;
	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UGameInstance_01::ReturnToMenuLevel()
{
	bIsRestart = true;
	UGameplayStatics::OpenLevel(this, MenuLevelName);
}