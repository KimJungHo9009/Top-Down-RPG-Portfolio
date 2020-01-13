// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Common.h"
#include "CharacterDummy.generated.h"

UCLASS()
class TOPDOWN_API ACharacterDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SelectCharacterType(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void ShowOutline(bool _Active);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CharacterType CharType = CharacterType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TypeText;

};
