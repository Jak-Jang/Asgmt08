#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Blind.generated.h"


UCLASS()
class ASGMT_08_API AProjectile_Blind : public AProjectile_Base
{
	GENERATED_BODY()
	

public:
	AProjectile_Blind();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blind")
	float BlindDuration;

	void Activated(AActor* Activator) override;
};
