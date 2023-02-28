// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTDecorator.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "Character/JCharacter.h"

bool UJBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UE_LOG(LogTemp, Error, TEXT("think "));

	AJAIController* AIC = Cast<AJAIController>(OwnerComp.GetAIOwner());
	if (AIC != nullptr)
	{
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIC->GetPawn());
		FVector AILocation = AICharacter->GetActorLocation();
		AJCharacter* Player = Cast<AJCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); // ������
		if (Player != nullptr)
		{
			FVector PlayerLocation = Player->GetActorLocation();
			// �������
			float Dis = (PlayerLocation - AILocation).Size();
			if (Dis < fDis)
			{
				return false; // �㹻�������ƶ���
			}
			else
			{
				return true; // �������������ƶ�
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}