// Fill out your copyright notice in the Description page of Project Settings.
// ����������ɫ�ƶ�
// �����������ºڰ�ֵ
// 

#include "AI/JAIController.h"
#include "Character/JCharacter.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AJAIController::AJAIController()
{
	//
	RootComponent->Activate(true);
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/RiskOnDream/AI/BehaviorTree")); // �ҵ��༭���е���Ϊ��
	if (BehaviorTreeAssert.Succeeded())
	{
		BehaviorTree = BehaviorTreeAssert.Object; // �����tree
	}

}

void AJAIController::OnPossess(APawn* InPawn)
{
	ControllPawn = InPawn;

	AJAICharacter* AICharacter = Cast<AJAICharacter>(InPawn);
	if (AICharacter == nullptr) {
		return;
	}

	Super::OnPossess(InPawn);

	if (BehaviorTreeComp != nullptr)
	{
		if (BehaviorTree != nullptr) {
			//������Ϊ��
			BehaviorTreeComp->StartTree(*BehaviorTree);
			AICharacter->BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset); // ��ʼ��
			//UE_LOG(LogTemp, Error, TEXT("start"));
		}
	}
	AICharacter->BlackboardComp->SetValueAsVector("TargetLocation", AICharacter->GetActorLocation());

}

void AJAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//ֹͣ��Ϊ��
	BehaviorTreeComp->StopTree(EBTStopMode::Safe);


}



FORCEINLINE UBehaviorTreeComponent* AJAIController::GetBehaviorTreeComp()
{
	return AJAIController::BehaviorTreeComp;
}

void AJAIController::HaveSeePawn(APawn* TargetPawn)
{
	//UE_LOG(LogTemp, Error, TEXT("this! "));

	TargetPawn = Cast<AJCharacter>(TargetPawn);
	if (TargetPawn) {
		FVector Location = TargetPawn->GetActorLocation();
		AJAICharacter* AICharacter  = Cast<AJAICharacter>(this->ControllPawn);
		//UE_LOG(LogTemp, Error, TEXT("i see you ! "));

		if (AICharacter) {
			AICharacter->BlackboardComp->SetValueAsVector("TargetLocation", Location);
			UE_LOG(LogTemp, Error, TEXT("i see you %s "), *Location.ToString());
			AICharacter->ChangeToAttackMode();
		}
	}



		

}