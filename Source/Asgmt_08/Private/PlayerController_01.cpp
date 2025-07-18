#include "PlayerController_01.h"
#include "EnhancedInputSubSystems.h"


APlayerController_01::APlayerController_01()
	: InputMappingContext(nullptr), MoveAction(nullptr)
{
}


void APlayerController_01::BeginPlay()
{
	Super::BeginPlay();

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