// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JAICharacter.h"
#include "AI/JAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AJAICharacter::AJAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//����AI������
	AIControllerClass = AJAIController::StaticClass();

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComp");
}

// Called when the game starts or when spawned
void AJAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//�󶨿�����ɫ����
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AJAICharacter::HaveSeePawn);
}

// Called every frame
void AJAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJAICharacter::HaveSeePawn(APawn* Pawn)
{
	FVector Location = Pawn->GetActorLocation();
	BlackboardComp->SetValueAsVector("TargetLocation", Location);
}

