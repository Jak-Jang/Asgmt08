#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Reverse.generated.h"


UCLASS()
class ASGMT_08_API AProjectile_Reverse : public AProjectile_Base
{
	GENERATED_BODY()
	
public:
	AProjectile_Reverse();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reverse")
	float ReverseDuration;

	void Activated(AActor* Activator) override;
};