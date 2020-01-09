// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	class UCharacterSaveData* CurrentSaveData;
};
