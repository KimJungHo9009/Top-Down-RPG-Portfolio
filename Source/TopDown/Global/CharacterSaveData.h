// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Common.h"
#include "CharacterSaveData.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UCharacterSaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetCharacterType(const CharacterType _Type);

	UFUNCTION()
	void SetDefault();
	
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
	CharacterType CharacterClass;

	UPROPERTY(VisibleAnywhere, Category = "Infomation")
	FString CharacterClassName;

	UPROPERTY(VisibleAnywhere, Category = "Infomation")
	FStat BaseStat;

};
