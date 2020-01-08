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
	UFUNCTION()
	void SetText();
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterInfo;
};
