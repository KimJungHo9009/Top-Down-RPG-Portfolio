// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPreview.h"
#include "Global/CharacterSaveData.h"
#include "components/SkeletalMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Menu/MenuGameMode.h"

// Sets default values
ACharacterPreview::ACharacterPreview()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skel(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin"));
	if (Skel.Succeeded()) {
		Mesh->SetSkeletalMesh(Skel.Object);
	}

	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	

	static ConstructorHelpers::FClassFinder<UAnimInstance> DefaultAnim(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP"));
	if (DefaultAnim.Succeeded()) {
		Mesh->SetAnimInstanceClass(DefaultAnim.Class);
	}
}

void ACharacterPreview::SetCharacter(UCharacterSaveData* _Char)
{
	// ���õ� ĳ���� ������ ���ͼ� �̸������ ĳ���͸� ����
	// ĳ���� �������� �⺻ �� ����
	// ���� �����۵� ���̵��� ����

	/*USkeletalMesh* NewMesh = Cast< USkeletalMesh >(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, ContentPath));
	if (NewMesh)
	{
		SetSkeletalMesh(NewMesh);
	}*/
	UserIndex = _Char->UserIndex;
	UE_LOG(LogTemp, Error, TEXT("SetCharacter Func Call, %s, %d"), *_Char->CharacterName, _Char->UserIndex);
}

// Called when the game starts or when spawned
void ACharacterPreview::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterPreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

