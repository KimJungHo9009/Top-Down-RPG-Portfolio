// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "MenuController.h"
#include "MenuPawn.h"
#include "Global/CharacterSaveData.h"
#include "CharacterDummy.h"

#include "UI/SelectMap/UI_SelectMapMenu.h"
#include "UI/SelectMap/UI_CreateCharacter.h"
#include "UI/SelectMap/UI_CharacterListRow.h"
#include "components/VerticalBox.h"
#include "Components/Button.h"

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
			for (ACharacterDummy* var : DummyArr) {
				var->ShowOutline(false);
			}
			CharType = CharacterType::None;
		}
		else if (CurrentWidget == CreateUI) {
			PawnTemp->SetActorLocation(FVector(-760, 0, 165));
			if (SelectUI == nullptr) {
				SelectUI = CreateWidget<UUI_SelectMapMenu>(MenuPC, SelectMapMenuClass);
			}
			CurrentWidget = SelectUI;			
		}
	}
	else {
		SelectUI = CreateWidget<UUI_SelectMapMenu>(MenuPC, SelectMapMenuClass);
		CurrentWidget = SelectUI;
	}
	LoadCharacterList(true);
	CurrentWidget->AddToViewport();
}

void AMenuGameMode::CreateNewCharacter(FString _CharName)
{
	int Index = CheckEmptySlot();
	if (Index != -1) {
		UCharacterSaveData* SaveGameInstance = Cast<UCharacterSaveData>(UGameplayStatics::CreateSaveGameObject(UCharacterSaveData::StaticClass()));
		SaveGameInstance->CharacterName = _CharName;
		SaveGameInstance->SetCharacterType(CharType);
		SaveGameInstance->SetDefault();
		SaveGameInstance->UserIndex = Index;
		FString Path = "CharacterData" + FString::FromInt(Index);
		SaveGameInstance->SaveSlotName = Path;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, Path, Index);
	}
	SetWidget();
	LoadCharacterList(true);
}

void AMenuGameMode::DeleteCharacter()
{
	//FString Path = "CharacterData" + FString::FromInt(ChooseChar->UserIndex);
	UGameplayStatics::DeleteGameInSlot(ChooseChar->CharacterData->SaveSlotName, ChooseChar->UserIndex);
	ChooseChar->RemoveFromParent();
	ChooseChar->Destruct();	
	ChooseChar = nullptr;
	LoadCharacterList(true);
}

void AMenuGameMode::LoadCharacterList(bool _Refresh = false)
{
	if (_Refresh) {
		CharRowArr.Empty();
		SelectUI->CharacterList->ClearChildren();
	}	

	for (int i = 0; i < 5; i++) {
		FString Path = "CharacterData" + FString::FromInt(i);
		if (UGameplayStatics::DoesSaveGameExist(Path, i)) {
			UCharacterSaveData* SaveTemp = Cast<UCharacterSaveData>(UGameplayStatics::LoadGameFromSlot(Path, i));

			UUI_CharacterListRow* CharRow = CreateWidget<UUI_CharacterListRow>(SelectUI, CharListClass);
			CharRow->CharacterData = SaveTemp;
			CharRow->SetText(SaveTemp->CharacterName, FString::FromInt(SaveTemp->Level), 
				SaveTemp->CharacterClassName, SaveTemp->UserIndex);
			CharRowArr.Add(CharRow);

			SelectUI->CharacterList->AddChildToVerticalBox(CharRow);
		}
	}
	if (CharRowArr.Num() > 0) {
		ChooseChar = CharRowArr[0];
		CharRowArr[0]->ChangeStyle(true);
		SelectUI->Delete->SetIsEnabled(true);
	}
	else {
		SelectUI->Delete->SetIsEnabled(false);
	}

	if (CharRowArr.Num() >= 5) {
		SelectUI->Create->SetIsEnabled(false);
	}
	else {
		SelectUI->Create->SetIsEnabled(true);
	}
}

void AMenuGameMode::SelectedChar()
{
	// 선택된 캐릭터 행 강조
	for (auto var : CharRowArr) {
		if (var != ChooseChar) {
			var->ChangeStyle(false);
		}
	}
	// 정보 읽어와서 화면에 캐릭터 외형 보여주기
}

void AMenuGameMode::SelectCharType(const CharacterType _Type)
{
	if (CurrentWidget == CreateUI) {
		CharType = _Type;
	}
}

int32 AMenuGameMode::CheckEmptySlot()
{
	if (CharRowArr.Num() > 0) {
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
