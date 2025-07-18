#include "Projectile_Heal.h"
#include "Player_Pawn.h"


AProjectile_Heal::AProjectile_Heal()
{
	HealAmount = 1;
	ActorType = "Heal";
}

void AProjectile_Heal::Activated(AActor* Activator)
{
	Super::Activated(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayer_Pawn* Player = Cast<APlayer_Pawn>(Activator))
		{
			Player->TakeHeal(HealAmount);
		}
	}

	Destroy();
}
