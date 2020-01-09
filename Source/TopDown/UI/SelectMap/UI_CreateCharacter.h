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
	virtual bool Initialize() override;

	UFUNCTION()
	void PressCreate();

	UFUNCTION()
	void PressCancel();

public:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EnterName;

	UPROPERTY(meta = (BindWidget))
	class UButton* OKButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY()
	FString CharClassName = "None";

private:
	class AMenuGameMode* MenuGM;
};
