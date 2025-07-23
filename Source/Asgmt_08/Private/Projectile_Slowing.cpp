#include "Projectile_Slowing.h"
#include "Player_Pawn.h"


AProjectile_Slowing::AProjectile_Slowing()
{
	Deceleration = 0.5f;
	SlowDuration = 5.0f;
	ActorType = "Slowing";
}

void AProjectile_Slowing::Activated(AActor* Activator)
{
	Super::Activated(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(Activator))
		{
			Player->Slow(Deceleration, SlowDuration);
		}
	}

	Destroy();
}