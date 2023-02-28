// Fill out your copyright notice in the Description page of Project Settings.
// ��ȡblackboard�ϵ����ݣ���ai controller ���ƽ�ɫ�ƶ�

#include "AI/JBTTaskNode.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UJBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Error, TEXT("go"));

	// �����Ϊ��������controler
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());

	//FVector temp = { 0,0,0 };
	//AIController->MoveToLocation(temp);
	
	// ��úڰ��ϵ�����
	AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
	UBlackboardComponent* BlackboardComp = AICharacter->BlackboardComp;
	if (BlackboardComp != nullptr) {
		FVector TargetLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));
		UE_LOG(LogTemp, Error, TEXT("go! %s"),*TargetLocation.ToString());
		if (AICharacter != nullptr) // ��AI�ƶ���targetlocation
		{
			AIController->MoveToLocation(TargetLocation);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
