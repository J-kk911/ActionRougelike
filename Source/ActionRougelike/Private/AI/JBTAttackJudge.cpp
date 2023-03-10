// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTAttackJudge.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"

bool UJBTAttackJudge::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetOwner());
	if (AIController != nullptr) {
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());

		FVector AILocation = AICharacter->GetActorLocation();
		FVector PLayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		if ((PLayerLocation - AILocation).Size() < AttackDis) {
			
			//ȷ�����������������������
			if (!AICharacter->AttackCDTimeHandle.IsValid()&&AICharacter->AttackModeTimeHandle.IsValid()) {
				return true;
			}
		}
	}
	
	return false;


}
