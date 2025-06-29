// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UTPaperZDCharacterBase.h"
#include "InputActionValue.h"
#include "UTPaperZDPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_UNTE_API AUTPaperZDPlayer : public AUTPaperZDCharacterBase
{
	GENERATED_BODY()
	

public:
	AUTPaperZDPlayer();



protected:
	virtual void BeginPlay()override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Input Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

};
