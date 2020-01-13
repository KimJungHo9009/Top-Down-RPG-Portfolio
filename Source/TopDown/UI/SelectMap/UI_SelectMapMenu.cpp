// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SelectMapMenu.h"
#include "Components/Button.h"
#include "Components/Overlay.h"

#include "Menu/MenuGameMode.h"
#include "UI_CharacterListRow.h"

bool UUI_SelectMapMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Start != nullptr)) return false;
	Start->OnClicked.AddDynamic(this, &UUI_SelectMapMenu::PressStart);
	if (!ensure(Delete != nullptr)) return false;
	Delete->OnClicked.AddDynamic(this, &UUI_SelectMapMenu::DeleteCharacter);
	if (!ensure(Create != nullptr)) return false;
	Create->OnClicked.AddDynamic(this, &UUI_SelectMapMenu::ShowCreateCharacter);
	if (!ensure(Exit != nullptr)) return false;
	Exit->OnClicked.AddDynamic(this, &UUI_SelectMapMenu::PressExit);
	if (!ensure(DeleteAccept != nullptr)) return false;
	DeleteAccept->OnClicked.AddDynamic(this, &UUI_SelectMapMenu::PressDeleteAccept);
	if (!ensure(DeleteCancel != nullptr)) return false;
	DeleteCancel->OnClicked.AddDynamic(this, &UUI_SelectMapMenu::PressDeleteCancel);

	MenuGM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());

	return true;
}

void UUI_SelectMapMenu::ShowCreateCharacter()
{
	if (MenuGM->CharRowArr.Num() < 5) {
		MenuGM->SetWidget();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Character Slot is Full"));
	}
}

void UUI_SelectMapMenu::DeleteCharacter()
{
	if (MenuGM->ChooseChar != nullptr) {
		DeleteCheck->SetVisibility(ESlateVisibility::Visible);
	}	
}

void UUI_SelectMapMenu::PressStart()
{
}

void UUI_SelectMapMenu::PressExit()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UUI_SelectMapMenu::PressDeleteAccept()
{
	MenuGM->DeleteCharacter();
	PressDeleteCancel();
}

void UUI_SelectMapMenu::PressDeleteCancel()
{
	DeleteCheck->SetVisibility(ESlateVisibility::Hidden);
}
