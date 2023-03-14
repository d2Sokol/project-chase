// Made by d2Sokol

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class UBoxComponent;
class IInteractInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, Category="Components")
		UBoxComponent* InteractBox;

	TArray<IInteractInterface*> InteractingActors;

private:
	void UpdateInteraction();

	void ClearOldInteractingActors();

public:
	UBoxComponent* GetInteractBox();
};
