// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CreateCharacter.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Menu/MenuGameMode.h"

bool UUI_CreateCharacter::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(OKButton != nullptr)) return false;
	OKButton->OnClicked.AddDynamic(this, &UUI_CreateCharacter::PressCreate);
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UUI_CreateCharacter::PressCancel);

	MenuGM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
	OKButton->SetIsEnabled(false);

	return Success;
}

void UUI_CreateCharacter::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!EnterName->Text.IsEmpty() && MenuGM->CharType != CharacterType::None) {
		OKButton->SetIsEnabled(true);
	}
	else {
		OKButton->SetIsEnabled(false);
	}
}

void UUI_CreateCharacter::PressCreate()
{
	MenuGM->CreateNewCharacter(EnterName->GetText().ToString());
	EnterName->SetText(FText::GetEmpty());
}

void UUI_CreateCharacter::PressCancel()
{
	EnterName->SetText(FText::GetEmpty());
	MenuGM->SetWidget();
}
