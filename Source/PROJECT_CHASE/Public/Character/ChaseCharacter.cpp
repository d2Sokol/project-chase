// Made by d2Sokol


#include "Character/ChaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Pawn.h"
#include "PaperCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/ChaseHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Components/InteractComponent.h"

AChaseCharacter::AChaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));

	BoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColl"));
	BoxColl->SetupAttachment(GetRootComponent());

	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(RootComponent);
	InteractComponent->GetInteractBox()->SetupAttachment(GetRootComponent());

	MinJumpValue = 3.0f;
	MaxJumpValue = 10.0f;
	TickJumpMultiplayer = 0.2f;
}

void AChaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetMappingContext(DefaultMappingContext);
	ActualMappingContext = EActualMappingContext::DEFAULT_CONTEXT;

	if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(GetRootComponent()))
	{
		Capsule->SetSimulatePhysics(false);
	}

	SetupHUD();

	bCanJump = true;
	bIsCastingJump = false;

	
	JumpDir = 0.0f;
}

void AChaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpriteRotation();

	
}

void AChaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChaseCharacter::Move);
		Input->BindAction(SwitchMappingAction, ETriggerEvent::Started, this, &AChaseCharacter::SwitchMappingContext);
		Input->BindAction(JumpLeftAction, ETriggerEvent::Triggered, this, &AChaseCharacter::CastJump);
		Input->BindAction(JumpRightAction, ETriggerEvent::Triggered, this, &AChaseCharacter::CastJump);
		Input->BindAction(JumpLeftAction, ETriggerEvent::Completed, this, &AChaseCharacter::JumpOnRelease);
		Input->BindAction(JumpRightAction, ETriggerEvent::Completed, this, &AChaseCharacter::JumpOnRelease);
	}
}

void AChaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AChaseCharacter::SetMappingContext(UInputMappingContext* MappingContext)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AChaseCharacter::SetSpriteRotation()
{
	if (GetCharacterMovement()->Velocity.X > 0.0f)
	{
		GetSprite()->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	}
	else if (GetCharacterMovement()->Velocity.X < 0.0f)
	{
		GetSprite()->SetRelativeScale3D(FVector(-0.1f, 0.1f, 0.1f));
	}
}

void AChaseCharacter::SetupHUD()
{
	if (IsLocallyControlled() && ChaseHUDClass)
	{
		ChaseHUD = CreateWidget<UChaseHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ChaseHUDClass, "CHASE_HUD");
		ChaseHUD->AddToViewport();
		ChaseHUD->OnBeginPlay();
	}
}

void AChaseCharacter::Move(const FInputActionValue& ActionValue)
{
	float Value = ActionValue.Get<float>();
	
	AddMovementInput(FVector(Value, 0.0f, 0.0f));
}

void AChaseCharacter::SwitchMappingContext()
{
	switch (ActualMappingContext)
	{
	case EActualMappingContext::DEFAULT_CONTEXT:
		SetMappingContext(JumpMappingContext);
		ActualMappingContext = EActualMappingContext::JUMP_CONTEXT;
		break;
	case EActualMappingContext::JUMP_CONTEXT:
		SetMappingContext(DefaultMappingContext);
		ActualMappingContext = EActualMappingContext::DEFAULT_CONTEXT;
		break;
	default:
		break;
	}

	JumpValue = 0.0f;
	ChaseHUD->SetActualContextImage(ActualMappingContext);
}

void AChaseCharacter::CastJump(const FInputActionValue& ActionValue)
{
	bIsCastingJump = true;

	JumpValue += TickJumpMultiplayer;

	float Value = ActionValue.Get<float>();

	JumpDir = Value;

	if (JumpValue >= MaxJumpValue) 
	{
		JumpValue = MaxJumpValue;
	}

	if (JumpValue <= MinJumpValue)
	{
		JumpValue = MinJumpValue;
	}
}

void AChaseCharacter::JumpOnRelease(const FInputActionValue& ActionValue)
{	
	JumpInDirection(JumpDir, JumpValue);
	JumpDir = 0.0f;
	JumpValue = 0.0f;
}

void AChaseCharacter::JumpInDirection(float Direction, float Strength)
{
	if (GetCharacterMovement()->IsMovingOnGround()) //bCanJump
	{
		//200.0f //700.0f
		
		LaunchCharacter(FVector(Direction * 200.0f, 0.0f, Strength*70.0f), false, false);
		//bCanJump = false;
	}
}
