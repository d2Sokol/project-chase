// Made by d2Sokol

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellsCompoenent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class USpellsCompoenent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpellsCompoenent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector SavedPosition;

	UPROPERTY(EditAnywhere, Category = "Spells Settings")
		uint8 SavePositionStarsNeeded;

public:
	void SavePosition(FVector NewSavePosition);

	void SpellSetPlayerPosition();
};
