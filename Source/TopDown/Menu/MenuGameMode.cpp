// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "MenuController.h"
#include "MenuPawn.h"
#include "Global/CharacterSaveData.h"
#include "Global/GlobalGameInstance.h"
#include "CharacterDummy.h"
#include "CharacterPreview.h"

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

	PreviewCharArr.Init(nullptr, 5);
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
	PreviewCharArr[ChooseChar->UserIndex]->Destroy();
	PreviewCharArr[ChooseChar->UserIndex] = nullptr;
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
		LoadPreviewCharacter();
		SelectedChar();
		SelectUI->Delete->SetIsEnabled(true);
	}
	else {
		SelectUI->Delete->SetIsEnabled(false);
		SelectUI->Start->SetIsEnabled(false);
	}

	if (CharRowArr.Num() >= 5) {
		SelectUI->Create->SetIsEnabled(false);
	}
	else {
		SelectUI->Create->SetIsEnabled(true);
	}
}

void AMenuGameMode::LoadPreviewCharacter()
{
	// 좌표 (X = -180.000000, Y = 40.000000, Z = 25.000000)
	FTransform CharTransform;
	CharTransform.SetLocation(FVector(-180, 40, 25));
	CharTransform.SetScale3D(FVector(1.5));
	CharTransform.SetRotation(FQuat(FRotator(0.f, 90.f, 0.f)));
	
	//UE_LOG(LogTemp, Error, TEXT("PreviewChar is null"));

	for (int i = 0; i < CharRowArr.Num(); i++) {
		int32 CharIndex = CharRowArr[i]->CharacterData->UserIndex;

		if (PreviewCharArr[CharIndex] == nullptr) {
			ACharacterPreview* PreviewChar = GetWorld()->SpawnActor<ACharacterPreview>(ACharacterPreview::StaticClass(), CharTransform);
			PreviewChar->SetCharacter(CharRowArr[i]->CharacterData);
			PreviewChar->SetActorHiddenInGame(true);
			PreviewCharArr[CharIndex] = PreviewChar;
		}		
	}	
}

void AMenuGameMode::SelectedChar()
{
	// 선택되지 않은 캐릭터 행 강조제거
	for (auto var : CharRowArr) {
		if (var != ChooseChar) {
			var->ChangeStyle(false);
			PreviewCharArr[var->CharacterData->UserIndex]->SetActorHiddenInGame(true);
		}
	}
	
	// 정보 읽어와서 화면에 캐릭터 외형 보여주기
	PreviewCharArr[ChooseChar->CharacterData->UserIndex]->SetActorHiddenInGame(false);
}

void AMenuGameMode::SelectCharType(const CharacterType _Type)
{
	if (CurrentWidget == CreateUI) {
		CharType = _Type;
	}
}

void AMenuGameMode::GameStart()
{
	if (ChooseChar == nullptr) return;

	Cast<UGlobalGameInstance>(GetGameInstance())->CurrentData = ChooseChar->CharacterData;
	
	UGameplayStatics::OpenLevel(this, "PlayMap");
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
