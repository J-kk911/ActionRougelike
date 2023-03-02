// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTMovementTaskNode.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UJBTMovementTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(LogTemp, Error, TEXT("go"));

	// �����Ϊ��������controler
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());


	// ��úڰ��ϵ�����
	AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
	
	UBlackboardComponent* BlackboardComp = AICharacter->BlackboardComp;
	if (BlackboardComp != nullptr && AICharacter != nullptr) {
		FVector TargetLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));
		//UE_LOG(LogTemp, Error, TEXT("go! %s"), *TargetLocation.ToString());
		 // ��AI�ƶ���targetlocation
		AIController->MoveToLocation(TargetLocation);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
