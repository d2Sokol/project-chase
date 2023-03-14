// Made by d2Sokol


#include "Character/ChaseHUD.h"
#include "ChaseCharacter.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Components/Image.h"

UChaseHUD::UChaseHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetRenderOpacity(0.0f);
}

void UChaseHUD::SetShowHUD(bool bNewShow)
{
	if (bNewShow)
	{
		PlayHUDAnimation("FadeIn_INST");
	}
	else
	{
		PlayHUDAnimation("FadeOut_INST");
	}
}

void UChaseHUD::PlayHUDAnimation(FString AnimationName)
{
	PlayAnimation(GetWidgetAnimation(AnimationName));
}

void UChaseHUD::SetActualContextImage(EActualMappingContext EMappingContext)
{
	switch (EMappingContext)
	{
	case EActualMappingContext::DEFAULT_CONTEXT:
		if (MappingContextThumbnail)
		{
			MappingContextThumbnail->SetBrushFromTexture(WalkingContextThumbnail);
		}
		break;
	case EActualMappingContext::JUMP_CONTEXT:
		if (MappingContextThumbnail)
		{
			MappingContextThumbnail->SetBrushFromTexture(JumpingContextThumbnail);
		}
		break;
	default:
		break;
	}
}

void UChaseHUD::OnBeginPlay()
{
	MappingContextThumbnail = GetWidgetReference<UImage>("MappingContextThumbnail");
	SetActualContextImage(EActualMappingContext::DEFAULT_CONTEXT);
	SetShowHUD(true);
	SetShowTutorial(true);
}

void UChaseHUD::SetShowTutorial(bool bNewShow)
{
	if (bNewShow)
	{
		PlayHUDAnimation("FadeInTutorial_INST");
		if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			PC->SetInputMode(FInputModeGameAndUI());
			PC->SetShowMouseCursor(true);
		}
	}
	else
	{
		if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			PC->SetInputMode(FInputModeGameOnly());
			PC->SetShowMouseCursor(false);
		}
		PlayHUDAnimation("FadeOutTutorial_INST");
	}
}

UWidgetAnimation* UChaseHUD::GetWidgetAnimation(FString AnimationName) const
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	for (UWidgetAnimation* WidgetAnimation : WidgetClass->Animations)
	{
		if (WidgetAnimation->GetName() == AnimationName)
		{
			return WidgetAnimation;
		}
	}

	return nullptr;
}
