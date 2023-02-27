// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AJAIController::AJAIController()
{
	//
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
}

void AJAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AJAICharacter* AICharacter = Cast<AJAICharacter>(InPawn);

	//������Ϊ��
	BehaviorTreeComp->StartTree(*BehaviorTree);

	//���úڰ���Դ
	AICharacter->BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

}

void AJAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//ֹͣ��Ϊ��
	BehaviorTreeComp->StopTree(EBTStopMode::Safe);

}
