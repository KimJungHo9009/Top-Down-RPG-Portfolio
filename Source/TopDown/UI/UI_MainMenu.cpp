// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MainMenu.h"
#include "Components/Button.h"
#include "kismet/GameplayStatics.h"

bool UUI_MainMenu::Initialize() 
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(StartButton != nullptr)) return false;
	StartButton->OnClicked.AddDynamic(this, &UUI_MainMenu::GameStart);
	if (!ensure(OptionButton != nullptr)) return false;
	OptionButton->OnClicked.AddDynamic(this, &UUI_MainMenu::ShowOption);
	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UUI_MainMenu::GameExit);

	return true;
}

void UUI_MainMenu::GameStart()
{
	UE_LOG(LogTemp, Log, TEXT("Game Start"));
	UGameplayStatics::OpenLevel(this, TEXT("SelectMap"));
}

void UUI_MainMenu::ShowOption()
{
	UE_LOG(LogTemp, Log, TEXT("Show Option"));
}

void UUI_MainMenu::GameExit()
{
	//FGenericPlatformMisc::RequestExit(false);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
