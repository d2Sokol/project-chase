// Made by d2Sokol


#include "Character/Components/SpellsCompoenent.h"
#include "Character/ChaseCharacter.h"
#include "Character/ChaseHUD.h"

USpellsCompoenent::USpellsCompoenent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SavedPosition = FVector(0.0f, 0.0f, 0.0f);
	SavePositionStarsNeeded = 5;
}

void USpellsCompoenent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USpellsCompoenent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USpellsCompoenent::SavePosition(FVector NewSavePosition)
{
	if (AChaseCharacter* Character = Cast<AChaseCharacter>(GetOwner()))
	{
		if (Character->GetStarAmount() >= SavePositionStarsNeeded)
		{
			SavedPosition = NewSavePosition;
			Character->RemoveStars(SavePositionStarsNeeded);
			Character->GetCharacterHUD()->SavePositionSpell();
		}
	}
	
}

void USpellsCompoenent::SpellSetPlayerPosition()
{
	
	if (SavedPosition != FVector(0.0f, 0.0f, 0.0f))
	{
		if (AChaseCharacter* Character = Cast<AChaseCharacter>(GetOwner()))
		{
			Character->SetActorLocation(SavedPosition);
			SavedPosition = FVector(0.0f, 0.0f, 0.0f);
			Character->GetCharacterHUD()->SetPlayerPositionSpell();
		}
	}
}


