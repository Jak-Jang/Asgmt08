#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Boost.generated.h"


UCLASS()
class ASGMT_08_API AProjectile_Boost : public AProjectile_Base
{
	GENERATED_BODY()
	

public:
	AProjectile_Boost();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
	float Acceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
	float BoostDuration;

	void Activated(AActor* Activator) override;
};