#include "GameMode_01.h"
#include "GameState_01.h"
#include "Player_Pawn.h"
#include "PlayerController_01.h"


AGameMode_01::AGameMode_01()
{
	DefaultPawnClass = APlayer_Pawn::StaticClass();
	PlayerControllerClass = APlayerController_01::StaticClass();
	GameStateClass = AGameState_01::StaticClass();
}