// Made by d2Sokol

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChaseHUD.generated.h"

/**
 * 
 */
class UImage;
class UWidgetAnimation;

enum EActualMappingContext;

UCLASS()
class UChaseHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UChaseHUD(const FObjectInitializer& ObjectInitializer);
	
	void SetShowHUD(bool bNewShow);

	void PlayHUDAnimation(FString AnimationName);

	void SetActualContextImage(EActualMappingContext EMappingContext);

	void OnBeginPlay();

	UFUNCTION(BlueprintCallable)
		void SetShowTutorial(bool bNewShow);

private:
	UWidgetAnimation* GetWidgetAnimation(FString AnimationName) const;

	template <typename T>
	T* GetWidgetReference(FName WidgetName);

private:
	UImage* MappingContextThumbnail;

	UPROPERTY(EditAnywhere)
		UTexture2D* WalkingContextThumbnail;

	UPROPERTY(EditAnywhere)
		UTexture2D* JumpingContextThumbnail;
};

template<typename T>
inline T* UChaseHUD::GetWidgetReference(FName WidgetName)
{
	if (T* Widget = dynamic_cast<T*>(GetWidgetFromName(WidgetName)))
	{
		return Widget;
	}

	return nullptr;
}
