// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTAttackTaskNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"

EBTNodeResult::Type UJBTAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//ͨ����Ϊ�������ÿ�����
	AJAIController* AAIController = Cast<AJAIController>(OwnerComp.GetOwner());
	//ͨ�����������Character
	AJAICharacter* AAICharacter = Cast<AJAICharacter>(AAIController->GetPawn());

	AAICharacter->ChangeToAttackMode();
	AAICharacter->Attack();
	return EBTNodeResult::Succeeded;
}
