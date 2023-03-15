// Made by d2Sokol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/InteractInterface.h"
#include "InteractableActor.generated.h"

class UBoxComponent;

UENUM()
enum EInteractionType
{
	PositionTrigger = 0 UMETA(DisplayName="SetPlayerPosition"),
	CollectableActor UMETA(DisplayName="CollectableStar")
};

UCLASS()
class AInteractableActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere, Category = "Actor Type")
		TEnumAsByte<EInteractionType> InteractionType;

	UPROPERTY(EditAnywhere, Category = "Values")
		FVector LocationToSet;

protected:
	virtual void OnStartInteraction() override;

	virtual void Interact() override;
};
