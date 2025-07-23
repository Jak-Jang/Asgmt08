#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Heal.generated.h"


UCLASS()
class ASGMT_08_API AProjectile_Heal : public AProjectile_Base
{
	GENERATED_BODY()
	
public:
	AProjectile_Heal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	int32 HealAmount;

	void Activated(AActor* Activator) override;
};
