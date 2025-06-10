// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UTPaperZDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "PaperFlipbook.h"
#include "Physics/UTCollision.h"

AUTPaperZDCharacterBase::AUTPaperZDCharacterBase()
{

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = true;

	//capsule
	GetCapsuleComponent()->InitCapsuleSize(20.f, 20.f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_UTCAPSULE);

	// Movement

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 80.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360*60.0f, 0.0f);

	//// sprite
	GetSprite()->AddRelativeLocation(FVector(0.f, 0.f, -20.f));
	GetSprite()->SetCastShadow( true);
	GetSprite()->bCastDynamicShadow = true;
	GetSprite()->bCastStaticShadow = true;

	GetSprite()->SetUsingAbsoluteRotation(true);

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
