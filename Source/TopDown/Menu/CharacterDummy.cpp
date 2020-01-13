// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDummy.h"
#include "Components/CapsuleComponent.h"
#include "components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "ConstructorHelpers.h"
#include "Menu/MenuGameMode.h"

// Sets default values
ACharacterDummy::ACharacterDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");

	RootComponent = Capsule;
	Mesh->SetupAttachment(RootComponent);
	Text->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skel(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin"));
	if (Skel.Succeeded()) {
		Mesh->SetSkeletalMesh(Skel.Object);
	}	

	Capsule->OnClicked.AddDynamic(this, &ACharacterDummy::SelectCharacterType);
}

// Called when the game starts or when spawned
void ACharacterDummy::BeginPlay()
{
	Super::BeginPlay();
	AMenuGameMode* MenuGM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());

	MenuGM->DummyArr.Add(this);
	Text->SetText(TypeText);
}

// Called every frame
void ACharacterDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterDummy::SelectCharacterType(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	AMenuGameMode* MenuGM = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());

	for (ACharacterDummy* var : MenuGM->DummyArr) {
		if (var != this) {
			var->ShowOutline(false);
		}
	}
	this->ShowOutline(true);
	MenuGM->SelectCharType(CharType);
	UE_LOG(LogTemp, Error, TEXT("clickclickclick"));
}

void ACharacterDummy::ShowOutline(bool _Active)
{
	Mesh->SetRenderCustomDepth(_Active);
}

