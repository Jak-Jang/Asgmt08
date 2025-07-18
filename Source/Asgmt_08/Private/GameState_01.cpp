#include "GameState_01.h"
#include "PlayerController_01.h"


AGameState_01::AGameState_01()
{
	PlayTime = 0;
	WaveDuration = 20.0f;
	CurrentWave = 0;
	MaxWave = 3;

}

void AGameState_01::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerController_01* PlayerController_01 = Cast<APlayerController_01>(PlayerController))
		{
			PlayerController_01->SetPause(true);
			//PlayerController_01->ShowMainMenu(true);
		}
	}
}