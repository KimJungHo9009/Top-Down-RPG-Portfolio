// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMenuGameMode();

	UFUNCTION(BlueprintCallable)
	void SetWidget();

	UFUNCTION()
	void CreateNewCharacter(FString _CharName, FString _CharClass);

	UFUNCTION()
	void DeleteCharacter(UCharacterSaveData* _DeleteChar);

	UFUNCTION()
	void LoadCharacterList();

	int32 CheckEmptySlot();

public:
	TSubclassOf<class UUI_SelectMapMenu> SelectMapMenuClass;
	TSubclassOf<class UUI_CreateCharacter> CreateCharClass;
	TSubclassOf<class UUI_CharacterListRow> CharListClass;
	TArray<class UCharacterSaveData*> CharacterListArr;
	class UCharacterSaveData* ChooseChar;

private:
	class UUserWidget* CurrentWidget;
	class UUI_SelectMapMenu* SelectUI;
	class UUI_CreateCharacter* CreateUI;
};
