// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UTPaperZDCharacterBase.h"
#include "Interface/UTUIInteractionInterface.h"
#include "Interface/UTUITalkInterface.h"
#include "UTPaperZDNPC.generated.h"


/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogCharacterNPC, Log, All);

UCLASS()
class PROJ_UNTE_API AUTPaperZDNPC : public AUTPaperZDCharacterBase,public IUTUIInteractionInterface, public IUTUITalkInterface
{
	GENERATED_BODY()
	
public:
	AUTPaperZDNPC();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText DialogueText;

	// UIInteractionInterface
	virtual void ActiveIntercationableUI() override;
	virtual void DeactiveIntercationableUI() override;
	virtual void InteractionFunction() override;

	// UI TalkInterface
	virtual void TalkStart() override;
	virtual void TalkEnd() override;


	// 블루프린트에서 이미지 지정 가능하게 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TObjectPtr<class UTexture2D> PortraitTexture;


protected:
	virtual void BeginPlay()override;


protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class USphereComponent> Trigger;


// UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UWidgetComponent> InterActionable;


private:
	bool bTalking = false;

};
