// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CharacterSaveData.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UCharacterSaveData : public USaveGame
{
	GENERATED_BODY()
	
public :
	UPROPERTY(VisibleAnywhere, Category = "Basics")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Basics")
	uint32 UserIndex;
	
	UPROPERTY(VisibleAnywhere, Category = "Infomation")
	FString CharacterName;

	UPROPERTY(VisibleAnywhere, Category = "Infomation")
	int32 Level;

	UPROPERTY(VisibleAnywhere, Category = "Infomation")
	FString CharacterClass;
};
