// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTJudgeDistanceDecorator.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "Character/JCharacter.h"


bool UJBTJudgeDistanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//UE_LOG(LogTemp, Error, TEXT("think "));

	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());
	if (AIController != nullptr)
	{
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
		FVector AILocation = AICharacter->GetActorLocation();
		AJCharacter* Player = Cast<AJCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); // ������
		if (Player != nullptr)
		{
			//�ж��Ƿ��ܿ������
			if (AICharacter->PawnSensingComp->CouldSeePawn(Player)) {
				FVector PlayerLocation = Player->GetActorLocation();
				// �������
				float Dis = (PlayerLocation - AILocation).Size();
				if (Dis > fDis)
				{
					return true; // �������������ƶ�
				}
			}
		}
	}
	return false;
}
