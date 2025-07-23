#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player_Pawn.generated.h"

class UCapsuleComponent;
class UArrowComponent;
class USkeleltalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class UParticleSystem;
struct FInputActionValue;

UCLASS()
class ASGMT_08_API APlayer_Pawn : public APawn
{
	GENERATED_BODY()

public:
	APlayer_Pawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Arrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* ReverseWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BlindWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* BlindWidgetInstance;


	UFUNCTION(BlueprintPure, Category = "GetSet")
	int32 GetMaxHealth() const;
	UFUNCTION(BlueprintPure, Category = "GetSet")
	int32 GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "GetSet")
	void SetHealth(int32 Amount);
	UFUNCTION(BlueprintPure, Category = "GetSet")
	float GetSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "GetSet")
	void SetSpeed(float Amount);
	UFUNCTION()
	void Boost(float Amount, float Duration);
	UFUNCTION()
	void StopBoost();
	UFUNCTION()
	void Slow(float Amount, float Duration);
	UFUNCTION()
	void StopSlow();
	UFUNCTION()
	void TakeHeal(int32 Amount);
	UFUNCTION()
	void TakeDamage(int32 Amount);
	UFUNCTION()
	void Blind(float Duration);
	UFUNCTION()
	void StopBlind();
	UFUNCTION()
	void Reverse(float Duration);
	UFUNCTION()
	void StopReverse();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 MaxHealth;

	FVector2D MoveInput;
	float RotateSpeed;
	FRotator StartRotation;
	float BaseSpeed;
	float MinSpeed;
	float MaxSpeed;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StopMove(const FInputActionValue& value);

	virtual void BeginPlay() override;

	void OnDeath();

private:
	FTimerHandle BoostTimerHandle;
	FTimerHandle SlowTimerHandle;
	FTimerHandle BlindTimerHandle;
	FTimerHandle ReverseTimerHandle;
	bool bIsBoost;
	bool bIsBlind;
	bool bIsReverse;
};
