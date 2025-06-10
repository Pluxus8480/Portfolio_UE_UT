// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UTTalkBoxWidget.h"

DEFINE_LOG_CATEGORY(LogUIManager);

UUIManager::UUIManager()
{
	UE_LOG(LogUIManager, Log, TEXT("Manager Create"));
}

void UUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogUIManager, Log, TEXT("Manager Initialize"));

	TSoftClassPtr<UUserWidget> TalkWidgetSoftClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(TEXT("/Game/UT_Assets/UI/WBP_TalkBox.WBP_TalkBox_C")));

	if (TalkWidgetSoftClass.IsValid())
	{
		// 이미 로드되어 있는 경우
		TalkWidget = TalkWidgetSoftClass.Get();
		UE_LOG(LogUIManager, Log, TEXT("TalkWidget already valid."));
	}
	else
	{
		// 아직 로드되지 않은 경우 로드
		TalkWidget = TalkWidgetSoftClass.LoadSynchronous();
		if (IsValid(TalkWidget))
		{
			UE_LOG(LogUIManager, Log, TEXT("TalkWidget loaded successfully."));
		}
		else
		{
			UE_LOG(LogUIManager, Error, TEXT("Failed to load TalkWidget class!"));
		}
	}
	//static ConstructorHelpers::FClassFinder<UUserWidget> TalkWidgetRef(TEXT("/Game/UT_Assets/UI/WBP_TalkBox.WBP_TalkBox_C"));

	//if (TalkWidgetRef.Succeeded())
	//{
	//	UE_LOG(LogUIManager, Log, TEXT("Ref Success"));
	//	TalkWidget = TalkWidgetRef.Class; // 저장만 해두기
	//}
	//else
	//{
	//	UE_LOG(LogUIManager, Error, TEXT("Ref failed!"));
	//}

}

void UUIManager::Talk(APlayerController* playerController, FText DialogueText, UTexture2D* NewImage )
{	

	if (TalkBoxWidget.IsValid())
	{
		UE_LOG(LogUIManager, Log, TEXT("UIManager Talk Called"));
		TalkBoxWidget->SetDialogueText(DialogueText);
		TalkBoxWidget->SetDialogueImage(NewImage);
		TalkBoxWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogUIManager, Log, TEXT("UIManager Talk Create"));
		TalkBoxWidget = CreateWidget<UUTTalkBoxWidget>(playerController, TalkWidget);
		TalkBoxWidget->SetDialogueText(DialogueText);
		TalkBoxWidget->SetDialogueImage(NewImage);
		TalkBoxWidget->AddToViewport();

	}
}

void UUIManager::TalkEnd()
{
	if (TalkBoxWidget.IsValid())
		TalkBoxWidget->RemoveFromViewport();
}

