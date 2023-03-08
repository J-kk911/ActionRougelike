// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JAttributeComponent.generated.h"

/*
* �ಥ����˼�ǿ��԰󶨶��
�Զ��嶯̬�ಥ����
	�㲥���������ϲ㺯������
	������һ�ֱ���ΪFOnHealthChanged�ı���
	�ڸ��ļ���.cpp�п�����.broadcast()�����㲥
 ����
	OnHealthChanged.Broadcast(Instigator, this, Health, Delta);
 
	�ϲ�ͨ����������̬�󶨵����������ʵ�ֵ���
 ����
	AttributeComp->OnHealthChanged.AddDynamic(this, &AJAICharacter::OnHealthChanged);
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UJAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API UJAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float Health;

public:
	//const �¼�����ͼ��Ͳ���Ҫ������
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta,FVector Location,AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth();
		
	void SetHealth(float MaxHealth);


};
