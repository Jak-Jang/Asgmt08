#include "Player_Pawn.h"
#include "PlayerController_01.h"
#include "GameState_01.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

APlayer_Pawn::APlayer_Pawn()
	: MoveSpeed(600.0f),
	MoveInput(FVector::ZeroVector),
	RotateSpeed(60.0f),
	StartRotation(FRotator::ZeroRotator),
	MaxHealth(3),
	bIsBoost(false),
	bIsBlind(false)
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(RootComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 3000.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(10.0f, 0.0f, 0.0f));

	Health = MaxHealth;
	BaseSpeed = MoveSpeed;
	MinSpeed = MoveSpeed * 0.5;
	MaxSpeed = MoveSpeed * 1.5;
}

void APlayer_Pawn::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = Mesh->GetRelativeRotation();

}

void APlayer_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(
		FVector(MoveInput.X * MoveSpeed * DeltaTime, MoveInput.Y * MoveSpeed * DeltaTime, 0.0f), true);
	
	FRotator CurrentRotation = Mesh->GetRelativeRotation();
	float CurrentPitch = CurrentRotation.Pitch;
	float NewPitch = FMath::Clamp(
		CurrentPitch + MoveInput.Y * RotateSpeed * DeltaTime,
		StartRotation.Pitch - 15.0f,
		StartRotation.Pitch + 15.0f);
	Mesh->SetRelativeRotation(FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll));
}

void APlayer_Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayerController_01* PlayerController = Cast<APlayerController_01>(GetController()))
		{
			// MoveAction Binding // W A S D
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APlayer_Pawn::Move);
			}
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&APlayer_Pawn::StopMove);
			}
		}
	}
}

void APlayer_Pawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	MoveInput = value.Get<FVector2D>();
}
void APlayer_Pawn::StopMove(const FInputActionValue& value)
{
	if (!Controller) return;
	MoveInput = FVector2D::ZeroVector;
}

int32 APlayer_Pawn::GetHealth() const
{
	return Health;
}
void APlayer_Pawn::SetHealth(int32 Amount)
{
	Health = Amount;
	if (Health > MaxHealth) Health = MaxHealth;
	if (Health <= 0) OnDeath();
}
float APlayer_Pawn::GetSpeed() const
{
	return BaseSpeed;
}
void APlayer_Pawn::SetSpeed(float Amount)
{
	MoveSpeed = Amount;
	if (MoveSpeed < MinSpeed) MoveSpeed = MinSpeed;
	if (MoveSpeed > MaxSpeed) MoveSpeed = MaxSpeed;
}

void APlayer_Pawn::OnDeath()
{
	AGameState_01* GameState = GetWorld() ? GetWorld()->GetGameState<AGameState_01>() : nullptr;
	if (GameState)
	{
		GameState->OnGameOver();
	}
}

void APlayer_Pawn::Boost(float Amount, float Duration)
{
	bIsBoost = true;
	StopSlow();
	SetSpeed(MoveSpeed * Amount);
	
	GetWorldTimerManager().ClearTimer(BoostTimerHandle);

	GetWorldTimerManager().SetTimer
	(
		BoostTimerHandle,
		this,
		&APlayer_Pawn::StopBoost,
		Duration,
		false
	);
}
void APlayer_Pawn::StopBoost()
{
	MoveSpeed = BaseSpeed;
	bIsBoost = false;
	GetWorldTimerManager().ClearTimer(BoostTimerHandle);
}

void APlayer_Pawn::Slow(float Amount, float Duration)
{
	if (!bIsBoost)
	{
		SetSpeed(MoveSpeed * Amount);

		GetWorldTimerManager().ClearTimer(SlowTimerHandle);

		GetWorldTimerManager().SetTimer
		(
			SlowTimerHandle,
			this,
			&APlayer_Pawn::StopSlow,
			Duration,
			false
		);
	}
}
void APlayer_Pawn::StopSlow()
{
	MoveSpeed = BaseSpeed;
	GetWorldTimerManager().ClearTimer(SlowTimerHandle);
}

void APlayer_Pawn::TakeHeal(int32 Amount)
{
	SetHealth(GetHealth() + Amount);
}

void APlayer_Pawn::TakeDamage(int32 Amount)
{
	SetHealth(GetHealth() - Amount);
}

void APlayer_Pawn::Blind(float Duration)
{
	bIsBlind = true;
	if (!bIsBlind) 
	{
		// UI 추가
	}
	GetWorldTimerManager().ClearTimer(BlindTimerHandle);

	GetWorldTimerManager().SetTimer
	(
		BlindTimerHandle,
		this,
		&APlayer_Pawn::StopBlind,
		Duration,
		false
	);
}
void APlayer_Pawn::StopBlind()
{
	bIsBlind = false;
	// UI 제거
}