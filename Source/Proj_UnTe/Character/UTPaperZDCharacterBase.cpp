// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UTPaperZDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "PaperFlipbook.h"

AUTPaperZDCharacterBase::AUTPaperZDCharacterBase()
{

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//capsule
	GetCapsuleComponent()->InitCapsuleSize(20.f, 20.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));


	// Movement

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 80.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;



	//// sprite
	GetSprite()->AddRelativeLocation(FVector(0.f, 0.f, -20.f));
	GetSprite()->SetCastShadow( true);
	GetSprite()->bCastDynamicShadow = true;
	GetSprite()->bCastStaticShadow = true;
	//static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipBookRef(TEXT("/Script/Paper2D.PaperFlipbook'/Game/UT_Assets/Player/CharaIdle.CharaIdle'"));
	//if (FlipBookRef.Object)
	//{
	//	GetSprite()->SetFlipbook(FlipBookRef.Object);
	//}
	

	// Animation
	static ConstructorHelpers::FClassFinder<UPaperZDAnimInstance> ZDAnimRef(TEXT("/Game/UT_Assets/Player/ABP_Chara.ABP_Chara_C"));
	if (ZDAnimRef.Class)
	{
		GetAnimationComponent()->SetAnimInstanceClass(ZDAnimRef.Class);
	}


}
