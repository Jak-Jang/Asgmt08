#include "Projectile_Enemy.h"
#include "Player_Pawn.h"


AProjectile_Enemy::AProjectile_Enemy()
{
	DamageAmount = 1;
	ActorType = "Enemy";
}

void AProjectile_Enemy::Activated(AActor* Activator)
{
	Super::Activated(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(Activator))
		{
			Player->TakeDamage(DamageAmount);
		}
	}

	Destroy();
}