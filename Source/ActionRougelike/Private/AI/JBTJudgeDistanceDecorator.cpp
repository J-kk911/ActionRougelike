// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTJudgeDistanceDecorator.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "Character/JCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"



bool UJBTJudgeDistanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//UE_LOG(LogTemp, Error, TEXT("think "));

	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());
	if (AIController != nullptr)
	{
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
		//UE_LOG(LogTemp, Error, TEXT("NOW "));

		//�������������ǰ�ڵ����Ч
		if (AICharacter ->AttackedLatelyTimeHandle.IsValid()) {
			//UE_LOG(LogTemp, Error, TEXT("ATTACKED! "));

			FVector AILocation = AICharacter->GetActorLocation();
			UBlackboardComponent* BlackboardComp = AICharacter->BlackboardComp;
			FVector TargetLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));
			// �������
			float Dis = (TargetLocation - AILocation).Size();
			if (Dis > fDis)
			{
				return true; // �������������ƶ�
			}
		}
		
			
		
	}
	return false;
}
