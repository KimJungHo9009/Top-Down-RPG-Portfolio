// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterListRow.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"

void UUI_CharacterListRow::SetText(FString _CharName, FString _Level, FString _Class, int32 _UserIndex) {
	CharacterName->Text = FText::FromString(_CharName);
	CharacterInfo->Text = FText::FromString("Lv." + _Level + "  " + _Class);
	Index = _UserIndex;
}