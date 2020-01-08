// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "MenuController.h"
#include "MenuPawn.h"

AMenuGameMode::AMenuGameMode()
{
	PlayerControllerClass = AMenuController::StaticClass();
	DefaultPawnClass = AMenuPawn::StaticClass();
}