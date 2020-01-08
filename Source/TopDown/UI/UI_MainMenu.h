// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public :
	virtual bool Initialize();

	UFUNCTION()
	void GameStart();

	UFUNCTION()
	void ShowOption();

	UFUNCTION()
	void GameExit();

public :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;
};
