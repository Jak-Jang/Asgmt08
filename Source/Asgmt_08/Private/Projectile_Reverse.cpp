#include "Projectile_Reverse.h"
#include "Player_Pawn.h"


AProjectile_Reverse::AProjectile_Reverse()
{
	ReverseDuration = 3.0f;
	ActorType = "Reverse";
}

void AProjectile_Reverse::Activated(AActor* Activator)
{
	Super::Activated(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(Activator))
		{
			Player->Reverse(ReverseDuration);
		}
	}

	Destroy();
}
