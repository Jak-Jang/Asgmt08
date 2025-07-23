#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Enemy.generated.h"


UCLASS()
class ASGMT_08_API AProjectile_Enemy : public AProjectile_Base
{
	GENERATED_BODY()
	
public:
	AProjectile_Enemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 DamageAmount;

	void Activated(AActor* Activator) override;
};