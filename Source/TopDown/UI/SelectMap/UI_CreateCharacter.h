// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_CreateCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UUI_CreateCharacter : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EnterName;

	UPROPERTY(meta = (BindWidget))
	class UButton* OKButton;
};
