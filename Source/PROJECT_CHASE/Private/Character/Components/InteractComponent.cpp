// Made by d2Sokol


#include "Character/Components/InteractComponent.h"
#include "Components/BoxComponent.h"
#include "Character/InteractInterface.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));

}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateInteraction();
}

void UInteractComponent::UpdateInteraction()
{
	ClearOldInteractingActors();
	
	TArray<UPrimitiveComponent*> InteractingComponents;
	InteractBox->GetOverlappingComponents(InteractingComponents);

	if (InteractingComponents.Num() > 0)
	{
		for (UPrimitiveComponent* Component : InteractingComponents)
		{
			if (IInteractInterface* InteractingActor = Cast<IInteractInterface>(Component->GetOwner()))
			{
				InteractingActor->OnStartInteraction();
				InteractingActors.Push(InteractingActor);
			}
		}
	}
}

void UInteractComponent::ClearOldInteractingActors()
{
	if (InteractingActors.Num() > 0)
	{
		for (IInteractInterface* Actor : InteractingActors)
		{
			Actor = nullptr;
		}

		InteractingActors.Empty();
	}
}

UBoxComponent* UInteractComponent::GetInteractBox()
{
	return InteractBox;
}

