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
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
		USpringArmComponent* SpringArm;

	EActualMappingContext ActualMappingContext;

	bool bCanJump;

	float MinJumpValue = 0.0f;
	float MaxJumpValue = 0.0f;
	float JumpValue = 0.0f;

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

protected:

	void Move(const FInputActionValue& ActionValue);

	void SwitchMappingContext();

	void CastJump(const FInputActionValue& ActionValue);
	void JumpInDirection(float Direction, float Strength);
};
