// Made by d2Sokol

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "ChaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UBoxComponent;
class UChaseHUD;
class UInteractComponent;

UENUM(BlueprintType)
enum EActualMappingContext {
	DEFAULT_CONTEXT = 0,
	JUMP_CONTEXT
};


UCLASS()
class PROJECT_CHASE_API AChaseCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AChaseCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* BoxColl;

	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
		UInteractComponent* InteractComponent;

	UPROPERTY(EditAnywhere, Category = "Subclass")
		TSubclassOf<UChaseHUD> ChaseHUDClass;

	EActualMappingContext ActualMappingContext;

	UChaseHUD* ChaseHUD;


	bool bCanJump;

	UPROPERTY(EditAnywhere, Category="Jumping Data")
		float MinJumpValue = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Jumping Data")
		float MaxJumpValue = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Jumping Data", Meta = (ClampMin = 0.1, ClampMax = 1.0f))
		float TickJumpMultiplayer = 0.0f;

	float JumpValue = 0.0f;
	float JumpDir = 0.0f;

	bool bIsCastingJump;

protected: // Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* JumpMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* SwitchMappingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpRightAction;

private:
	void SetMappingContext(UInputMappingContext* MappingContext);

	void SetSpriteRotation();

	void SetupHUD();

protected:

	void Move(const FInputActionValue& ActionValue);

	void SwitchMappingContext();

	void CastJump(const FInputActionValue& ActionValue);
	void JumpOnRelease(const FInputActionValue& ActionValue);
	void JumpInDirection(float Direction, float Strength);
};
