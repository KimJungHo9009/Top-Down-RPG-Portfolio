// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterListRow.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Button.h"

#include "Menu/MenuGameMode.h"
#include "Global/CharacterSaveData.h"

bool UUI_CharacterListRow::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	CharacterButton->OnClicked.AddDynamic(this, &UUI_CharacterListRow::SelectCharacter);

	return true;
}

void UUI_CharacterListRow::SetText(FString _CharName, FString _Level, FString _Class, int32 _UserIndex) {
	CharacterName->Text = FText::FromString(_CharName);
	CharacterInfo->Text = FText::FromString("Lv." + _Level + "  " + _Class);
	UserIndex = _UserIndex;
}

void UUI_CharacterListRow::SelectCharacter()
{
	AMenuGameMode* MenuGM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
	MenuGM->ChooseChar = this;
	ChangeStyle(true);
	MenuGM->SelectedChar();
}

void UUI_CharacterListRow::ChangeStyle(bool _Selected)
{
	FButtonStyle NewStyle;
	FSlateBrush Highlight;
	Highlight.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 0.5f));
	FSlateBrush NonSelected;
	NonSelected.TintColor = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f));
	NewStyle.SetNormal(_Selected ? Highlight : NonSelected);
	NewStyle.SetHovered(Highlight);
	NewStyle.SetPressed(Highlight);

	CharacterButton->SetStyle(NewStyle);
}