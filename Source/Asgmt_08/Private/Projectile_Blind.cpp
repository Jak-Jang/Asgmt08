#include "Projectile_Blind.h"
#include "Player_Pawn.h"

AProjectile_Blind::AProjectile_Blind()
{
	BlindDuration = 3.0f;
	ActorType = "Blind";
}

void AProjectile_Blind::Activated(AActor* Activator)
{
	Super::Activated(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(Activator))
		{
			Player->Blind(BlindDuration);
		}
	}
	Destroy();
}