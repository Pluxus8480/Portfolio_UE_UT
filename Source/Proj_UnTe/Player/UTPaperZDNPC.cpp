// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UTPaperZDNPC.h"
#include "UTPaperZDNPC.h"
#include "../UI/UTTalkBoxWidget.h"
#include "UI/UTTalkBoxWidget.h"
#include "UI/UIManager.h"
#include "Components/CapsuleComponent.h"
#include "Physics/UTCollision.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "PaperFlipbookComponent.h"

#define LOCTEXT_NAMESPACE "DialogueNamespace"
DEFINE_LOG_CATEGORY(LogCharacterNPC);
AUTPaperZDNPC::AUTPaperZDNPC()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("UTNPC"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));

	Trigger->SetupAttachment(GetSprite());

	Trigger->SetCollisionProfileName(CPROFILE_UTTRIGGER);
	Trigger->SetSphereRadius(30.f);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AUTPaperZDNPC::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AUTPaperZDNPC::OnOverlapEnd);


	InterActionable = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	InterActionable->SetupAttachment(GetSprite());
	InterActionable->SetRelativeLocation(FVector(0.0f,0.0f,20.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> InteractionableRef(TEXT("/Game/UT_Assets/UI/WBP_Interactionable.WBP_Interactionable_C"));
	if (InteractionableRef.Class)
	{
		UE_LOG(LogCharacterNPC, Log, TEXT("NPC Create Interaction UI"));
		InterActionable->SetWidgetClass(InteractionableRef.Class);
		InterActionable->SetWidgetSpace(EWidgetSpace::Screen);
		InterActionable->SetDrawSize(FVector2D(40, 40));
		InterActionable->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AUTPaperZDNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{

}

void AUTPaperZDNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AUTPaperZDNPC::ActiveIntercationableUI()
{
	InterActionable->GetWidget()->SetVisibility(ESlateVisibility::Visible);
}

void AUTPaperZDNPC::DeactiveIntercationableUI()
{
	InterActionable->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
	TalkEnd();
}

void AUTPaperZDNPC::InteractionFunction()
{
	if (!bTalking)
		TalkStart();
	else
		TalkEnd();
}

void AUTPaperZDNPC::TalkStart()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UUIManager* UM = GetGameInstance()->GetSubsystem<UUIManager>();
	UM->Talk(PlayerController, DialogueText, PortraitTexture);
	bTalking = true;
}

void AUTPaperZDNPC::TalkEnd()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UUIManager* UM = GetGameInstance()->GetSubsystem<UUIManager>();
	UM->TalkEnd();
	bTalking = false;
}




void AUTPaperZDNPC::BeginPlay()
{
	if (InterActionable && InterActionable->GetWidgetClass())
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), InterActionable->GetWidgetClass());
		InterActionable->SetWidget(Widget);
		InterActionable->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
	}

#if ENABLE_DRAW_DEBUG
	FVector PlayerLocation = GetActorLocation();
	float Radius = 30.f;

	DrawDebugSphere(GetWorld(), PlayerLocation, Radius, 12, FColor::Green, true);

#endif
}

// LOCTEXT 매크로 닫기
#undef LOCTEXT_NAMESPACE