// Made by d2Sokol


#include "Character/ChaseHUD.h"
#include "ChaseCharacter.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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

void UChaseHUD::SetStarAmount(uint8 StarAmount)
{
	if (UTextBlock* StarAmountText = GetWidgetReference<UTextBlock>("StarAmount"))
	{
		StarAmountText->SetText(FText::AsNumber(StarAmount));
	}

	if (UTextBlock* StarSpellText = GetWidgetReference<UTextBlock>("StarNeeded"))
	{
		if (5 - StarAmount <= 0)
		{
			StarSpellText->SetText(FText::AsNumber(0));
			StarSpellText->SetOpacity(0.0f);
		}
		else 
		{
			StarSpellText->SetText(FText::AsNumber(5 - StarAmount));
		}
	}
}

void UChaseHUD::SavePositionSpell()
{
	if (UImage* SpellImage = GetWidgetReference<UImage>("SetPositionSpellThumbnail"))
	{
		SpellImage->SetOpacity(1.0f);
	}
}

void UChaseHUD::SetPlayerPositionSpell()
{
	if (UImage* SpellImage = GetWidgetReference<UImage>("SetPositionSpellThumbnail"))
	{
		SpellImage->SetOpacity(0.3f);
	}

	if (UTextBlock* StarSpellText = GetWidgetReference<UTextBlock>("StarNeeded"))
	{
		StarSpellText->SetOpacity(0.4f);
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
