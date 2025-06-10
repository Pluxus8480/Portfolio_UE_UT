// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UTTalkBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_UNTE_API UUTTalkBoxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UUTTalkBoxWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetDialogueText(const FText& NewText);
	void SetDialogueImage(UTexture2D* NewImage);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBox;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> TalkHeadImage;
};
