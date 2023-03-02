// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JAICharacter.h"
#include "AI/JAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/JAttributeComponent.h"

// Sets default values
AJAICharacter::AJAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//����AI������
	AIControllerClass = AJAIController::StaticClass();

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComp");
	AttributeComp = CreateDefaultSubobject<UJAttributeComponent>("AttributeComp");

}

void AJAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//�����󶨵��¼��ϣ������¼�����
	AttributeComp->OnHealthChanged.AddDynamic(this, &AJAICharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void AJAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//�󶨿�����ɫʱ��Ķ���
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AJAICharacter::HaveSeePawn);

	BlackboardComp->SetValueAsVector("TargetLocation", this->GetActorLocation());

	AttributeComp->SetHealth(200.0);

}


// Called every frame
void AJAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f"),AttributeComp->GetHealth());
}

// Called to bind functionality to input
void AJAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJAICharacter::HaveSeePawn(APawn* Pawn)
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == Pawn) {
		FVector Location = Pawn->GetActorLocation();
		BlackboardComp->SetValueAsVector("TargetLocation", Location);
		//UE_LOG(LogTemp, Error, TEXT("i see you %s "), *Location.ToString());
	}
}

void AJAICharacter::OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f) {
		PlayAnimMontage(DeadthAnim);
		AAIController* AIController = Cast<AAIController>(GetController());
		//AIControllerClass = NULL;//
		this->Controller->UnPossess();
	}

	if (InstigatorActor) {
		UE_LOG(LogTemp, Warning, TEXT("character"));
		BlackboardComp->SetValueAsVector("TargetLocation", InstigatorActor->GetActorLocation());
	}
	AttackedLately.Invalidate();
	GetWorldTimerManager().SetTimer(AttackedLately,this,&AJAICharacter::AttackedLatelyClear, 30.0f, false);
}

void AJAICharacter::Attack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(AttackTimeHandle, this, &AJAICharacter::DealDemage, TimeToDealDemage);
	AttackCDTimeHandle.Invalidate();
	GetWorldTimerManager().SetTimer(AttackCDTimeHandle, this, &AJAICharacter::AttackCDClaer, AttackCD);

}

void AJAICharacter::DealDemage()
{
	TArray<struct FOverlapResult> OutOverlaps;
	const FVector Pos = GetActorLocation();
	FQuat Rot = GetActorQuat();
	ECollisionChannel TraceChannel = ECC_Pawn;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(AttackRadius/2);
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	GetWorld()->OverlapMultiByChannel(OutOverlaps, Pos, Rot, TraceChannel, CollisionShape);

	for (auto OverLapPawn : OutOverlaps)
	{
		//�������������Ѫ
		UJAttributeComponent* OtherAttributeComp = Cast<UJAttributeComponent>(OverLapPawn.Actor->GetComponentByClass(UJAttributeComponent::StaticClass()));
		if (OtherAttributeComp && OtherAttributeComp->GetOwner()!=this) {
			OtherAttributeComp->ApplyHealthChange(-10.0, OverLapPawn.Actor->GetActorLocation(), this->GetInstigator());
		}
	}
}

void AJAICharacter::AttackedLatelyClear()
{
	AttackedLately.Invalidate();
}

void AJAICharacter::AttackCDClaer()
{
	AttackCDTimeHandle.Invalidate();
}
