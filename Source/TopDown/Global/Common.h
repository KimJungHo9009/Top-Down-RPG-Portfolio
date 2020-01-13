// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common.generated.h"

UENUM(BlueprintType)
enum class CharacterType : uint8 {
	None,
	Warrior,
	Wizard,
	Archer,
};

USTRUCT(BlueprintType)
struct TOPDOWN_API FStat {
	GENERATED_BODY()
	
	UPROPERTY()
	int32 STR;

	UPROPERTY()
	int32 INT;

	UPROPERTY()
	int32 DEX;

	UPROPERTY()
	int32 VIT;

	FStat() {
		STR = 1;
		INT = 1;
		DEX = 1;
		VIT = 1;
	}

	FStat(int32 _STR, int32 _INT, int32 _DEX, int32 _VIT) {
		STR = _STR;
		INT = _INT;
		DEX = _DEX;
		VIT = _VIT;
	}
};