// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTJudgePartolDecorator.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"

bool UJBTJudgePartolDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());
	if (AIController != nullptr)
	{
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
		//UE_LOG(LogTemp, Error, TEXT("NOW "));

		//�������������ǰ�ڵ����Ч
		if (!AICharacter->AttackModeTimeHandle.IsValid()) {
			return true;
		}
	}
	return false;
}
