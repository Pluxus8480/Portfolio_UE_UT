// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UTTalkBoxWidget.h"
#include "UTTalkBoxWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Slate/SlateBrushAsset.h"

UUTTalkBoxWidget::UUTTalkBoxWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UUTTalkBoxWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ensure(TextBox);
    
}

void UUTTalkBoxWidget::SetDialogueText(const FText& NewText)
{
    if (TextBox)
    {
        TextBox->SetText(NewText);
    }
}

void UUTTalkBoxWidget::SetDialogueImage(UTexture2D* NewImage)
{
    if (TalkHeadImage && NewImage)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(NewImage);
        Brush.ImageSize = FVector2D(NewImage->GetSizeX(), NewImage->GetSizeY());

        TalkHeadImage->SetBrush(Brush);
    }
    else if (!NewImage)
    {
        TalkHeadImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
