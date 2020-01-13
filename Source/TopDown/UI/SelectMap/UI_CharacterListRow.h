// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_CharacterListRow.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UUI_CharacterListRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void SetText(FString _CharName, FString _Level, FString _Class, int32 _UserIndex);

	UFUNCTION()
	void SelectCharacter();

	UFUNCTION()
	void ChangeStyle(bool _Selected);
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterInfo;

	UPROPERTY(meta = (BindWidget))
	class UButton* CharacterButton;

	int32 UserIndex;
	bool Selected = false;

	class UCharacterSaveData* CharacterData;
};
