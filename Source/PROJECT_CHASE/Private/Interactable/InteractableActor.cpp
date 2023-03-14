// Made by d2Sokol


#include "Interactable/InteractableActor.h"
#include "Components/BoxComponent.h"
#include "Character/ChaseCharacter.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	LocationToSet = FVector(0.0f, 0.0f, 0.0f);

}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::OnStartInteraction()
{
	if (InteractionType == EInteractionType::PositionTrigger) 
	{
		if (AChaseCharacter* Character = Cast<AChaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
		{
			Character->SetActorLocation(LocationToSet);
		}
	}
}

void AInteractableActor::Interact()
{
}

