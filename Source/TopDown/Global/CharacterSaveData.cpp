// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSaveData.h"

void UCharacterSaveData::SetCharacterType(CharacterType _Type) {
	CharacterClass = _Type;

	switch (_Type)
	{
	case CharacterType::None:
		CharacterClassName = "None";
		break;
	case CharacterType::Warrior:
		CharacterClassName = "Warrior";
		break;
	case CharacterType::Wizard:
		CharacterClassName = "Wizard";
		break;
	case CharacterType::Archer:
		CharacterClassName = "Archer";
		break;
	}
}

void UCharacterSaveData::SetDefault()
{
	Level = 1;
	BaseStat = FStat();
}
