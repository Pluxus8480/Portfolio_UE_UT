// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UTPaperZDPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "UI/UTTalkBoxWidget.h"
#include "UI/UIManager.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "PaperFlipbookComponent.h"
#include "Interface/UTUIInteractionInterface.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY(LogUTCharacter);


AUTPaperZDPlayer::AUTPaperZDPlayer()
{	
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = false;
	FRotator NewRotation = FRotator(-25.f, -90.0f, 0.0f); // Pitch, Yaw, Roll
	CameraBoom->SetRelativeRotation(NewRotation);
	CameraBoom->SetUsingAbsoluteRotation(true);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AUTPaperZDPlayer::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AUTPaperZDPlayer::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/UT_Assets/Input/IMC_Default.IMC_Default'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/UT_Assets/Input/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputInteractionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/UT_Assets/Input/IA_Interaction.IA_Interaction'"));
	if (nullptr != InputInteractionRef.Object)
	{
		InteractionAction = InputInteractionRef.Object;
	}
	//static ConstructorHelpers::FClassFinder<UUserWidget> TalkWidgetRef(
	//	TEXT("/Game/UT_Assets/UI/WBP_TalkBox.WBP_TalkBox_C")
	//);

	//if (TalkWidgetRef.Succeeded())
	//{
	//	UE_LOG(LogUTCharacter, Log, TEXT("Ref Success"));
	//	TalkWidget = TalkWidgetRef.Class; // 저장만 해두기
	//}
	//else
	//{
	//	UE_LOG(LogUTCharacter, Error, TEXT("Ref failed!"));
	//}
}

void AUTPaperZDPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	//UUIManager* UM = GetGameInstance()->GetSubsystem<UUIManager>();
	//UM->Talk(PlayerController, FText::FromString(TEXT("언더테일")), PortraitTexture);

}

void AUTPaperZDPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUTPaperZDPlayer::Move);
	EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &AUTPaperZDPlayer::Interaction);

}

void AUTPaperZDPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	IUTUIInteractionInterface* InteractionActor = Cast<IUTUIInteractionInterface>(OtherActor);
	if (InteractionActor)
	{
		InteractionTarget = TScriptInterface<IUTUIInteractionInterface>(OtherActor);
		InteractionActor->ActiveIntercationableUI();
		
	}
}

void AUTPaperZDPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IUTUIInteractionInterface* InteractionActor = Cast<IUTUIInteractionInterface>(OtherActor);
	if (InteractionActor)
	{
		InteractionActor->DeactiveIntercationableUI();
		InteractionTarget = nullptr;

	}
}

void AUTPaperZDPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AUTPaperZDPlayer::Look(const FInputActionValue& Value)
{
}

void AUTPaperZDPlayer::Interaction(const FInputActionValue& Value)
{
	if (InteractionTarget)
	{
		InteractionTarget->InteractionFunction();
	}
}

