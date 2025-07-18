#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Slowing.generated.h"


UCLASS()
class ASGMT_08_API AProjectile_Slowing : public AProjectile_Base
{
	GENERATED_BODY()

public:
	AProjectile_Slowing();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deceleration")
	float Deceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deceleration")
	float SlowDuration;

	void Activated(AActor* Activator) override;
};