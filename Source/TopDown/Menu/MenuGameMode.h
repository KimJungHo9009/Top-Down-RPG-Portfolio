// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Common.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 메뉴 화면 관리하는 객체
 캐릭터 슬롯은 5개
 **/
UCLASS()
class TOPDOWN_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMenuGameMode();

	UFUNCTION(BlueprintCallable)
	void SetWidget();

	UFUNCTION()
	void CreateNewCharacter(FString _CharName);

	UFUNCTION()
	void DeleteCharacter();

	UFUNCTION()
	void LoadCharacterList(bool _Refresh);

	UFUNCTION()
	void SelectedChar();

	UFUNCTION()
	void SelectCharType(const CharacterType _Type);

private:
	int32 CheckEmptySlot();

public:
	TSubclassOf<class UUI_SelectMapMenu> SelectMapMenuClass;
	TSubclassOf<class UUI_CreateCharacter> CreateCharClass;
	TSubclassOf<class UUI_CharacterListRow> CharListClass;

	TArray<class UUI_CharacterListRow*> CharRowArr;
	TArray<class ACharacterDummy*> DummyArr;

	class UUI_CharacterListRow* ChooseChar;
	CharacterType CharType = CharacterType::None;

private:
	class UUserWidget* CurrentWidget;
	class UUI_SelectMapMenu* SelectUI;
	class UUI_CreateCharacter* CreateUI;
};
