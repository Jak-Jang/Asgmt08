#include "Projectile_Boost.h"
#include "Player_Pawn.h"


AProjectile_Boost::AProjectile_Boost()
{
	Acceleration = 1.5f;
	BoostDuration = 3.0f;
	ActorType = "Boost";
}

void AProjectile_Boost::Activated(AActor* Activator)
{
	Super::Activated(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(Activator))
		{
			Player->Boost(Acceleration, BoostDuration);
		}
	}

	Destroy();
}