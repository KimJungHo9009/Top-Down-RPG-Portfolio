// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "MenuController.h"
#include "MenuPawn.h"
#include "Global/CharacterSaveData.h"

#include "UI/SelectMap/UI_SelectMapMenu.h"
#include "UI/SelectMap/UI_CreateCharacter.h"
#include "UI/SelectMap/UI_CharacterListRow.h"
#include "components/VerticalBox.h"

#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AMenuGameMode::AMenuGameMode()
{
	PlayerControllerClass = AMenuController::StaticClass();
	DefaultPawnClass = AMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UUI_SelectMapMenu> SelectMenuBPClass(TEXT("/Game/UI/SelectMap/WBP_UI_SelectMapMenu"));
	if (!ensure(SelectMenuBPClass.Class != nullptr)) return;
	SelectMapMenuClass = SelectMenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUI_CreateCharacter> CreateCharBPClass(TEXT("/Game/UI/SelectMap/WBP_UI_CreateCharacter"));
	if (!ensure(CreateCharBPClass.Class != nullptr)) return;
	CreateCharClass = CreateCharBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUI_CharacterListRow> CharRowBPClass(TEXT("/Game/UI/SelectMap/WBP_UI_CharacterListRow"));
	if (!ensure(CharRowBPClass.Class != nullptr)) return;
	CharListClass = CharRowBPClass.Class;
}

void AMenuGameMode::SetWidget()
{
	AMenuController* MenuPC = Cast<AMenuController>(GetWorld()->GetFirstPlayerController());
	if (MenuPC == nullptr) return;

	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();

		APawn* PawnTemp = MenuPC->GetPawn();
		if (PawnTemp == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("GetPawn Faild"));
			return;
		}

		if (CurrentWidget == SelectUI) {			
			PawnTemp->SetActorLocation(FVector(-760, 3960, 165));
			if (CreateUI == nullptr) {
				CreateUI = CreateWidget<UUI_CreateCharacter>(MenuPC, CreateCharClass);
			}
			CurrentWidget = CreateUI;
		}
		else if (CurrentWidget == CreateUI) {
			PawnTemp->SetActorLocation(FVector(-760, 0, 165));
			if (SelectUI == nullptr) {
				SelectUI = CreateWidget<UUI_SelectMapMenu>(MenuPC, SelectMapMenuClass);
			}
			CurrentWidget = SelectUI;
			LoadCharacterList();
		}
	}
	else {
		SelectUI = CreateWidget<UUI_SelectMapMenu>(MenuPC, SelectMapMenuClass);
		CurrentWidget = SelectUI;
		LoadCharacterList();
	}
	CurrentWidget->AddToViewport();
}

void AMenuGameMode::CreateNewCharacter(FString _CharName, FString _CharClass)
{
	int Index = CheckEmptySlot();
	if (Index != -1) {
		UCharacterSaveData* SaveGameInstance = Cast<UCharacterSaveData>(UGameplayStatics::CreateSaveGameObject(UCharacterSaveData::StaticClass()));
		SaveGameInstance->CharacterName = _CharName;
		SaveGameInstance->CharacterClass = _CharClass;
		SaveGameInstance->Level = 1;
		SaveGameInstance->UserIndex = Index;
		FString Path = "CharacterData" + FString::FromInt(Index);
		SaveGameInstance->SaveSlotName = Path;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, Path, Index);
	}
	SetWidget();
}

void AMenuGameMode::DeleteCharacter(UCharacterSaveData* _DeleteChar)
{
	FString Path = "CharacterData" + FString::FromInt(_DeleteChar->UserIndex);
	UGameplayStatics::DeleteGameInSlot(Path, _DeleteChar->UserIndex);
}

void AMenuGameMode::LoadCharacterList()
{
	CharacterListArr.Empty();
	SelectUI->CharacterList->ClearChildren();

	for (int i = 0; i < 5; i++) {
		FString Path = "CharacterData" + FString::FromInt(i);
		if (UGameplayStatics::DoesSaveGameExist(Path, i)) {
			UCharacterSaveData* SaveTemp = Cast<UCharacterSaveData>(UGameplayStatics::LoadGameFromSlot(Path, i));
			CharacterListArr.Add(SaveTemp);

			UUI_CharacterListRow* CharRow = CreateWidget<UUI_CharacterListRow>(SelectUI, CharListClass);
			CharRow->SetText(SaveTemp->CharacterName, FString::FromInt(SaveTemp->Level), 
				SaveTemp->CharacterClass, SaveTemp->UserIndex);

			SelectUI->CharacterList->AddChildToVerticalBox(CharRow);
		}
	}
	if (CharacterListArr.Num() > 0) {
		ChooseChar = CharacterListArr[0];
	}	
}

int32 AMenuGameMode::CheckEmptySlot()
{
	if (CharacterListArr.Num() > 0) {
		for (int i = 0; i < 5; i++) {
			FString Path = "CharacterData" + FString::FromInt(i);
			if (!UGameplayStatics::DoesSaveGameExist(Path, i)) {
				return i;
			}
		}
	}
	else {
		return 0;
	}
	
	return -1;
}
