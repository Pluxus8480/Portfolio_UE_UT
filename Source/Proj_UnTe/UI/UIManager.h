// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManager.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogUIManager, Log, All);
/**
 * 
 */
UCLASS()
class PROJ_UNTE_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Talk(class APlayerController* playerController, FText DialogueText, UTexture2D* NewImage = nullptr);
	void TalkEnd();
private:
	UUIManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;

private:
	// UI Section

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> TalkWidget;


	TWeakObjectPtr<class UUTTalkBoxWidget> TalkBoxWidget;

};
