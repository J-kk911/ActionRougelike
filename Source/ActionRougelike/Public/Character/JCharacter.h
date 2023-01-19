// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JInteractionComponent.h"
#include "JAttributeComponent.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;

UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//����ͼ���ֶ�����һ�����ʵ����ħ���ӵ�
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> MagiskProjectileClass;

	//����ͼ���ֶ�����һ�����ʵ�����ڶ��ӵ�
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackholeProjectileClass;

	//����ͼ���ֶ�����һ�����ʵ����λ���ӵ�
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> DisplacementProjectileClass;

	//���Ŷ���
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	//̧���ӳ�
	UPROPERTY(EditAnywhere, Category = "Attack")
	float TimeToHandUp = 0.2;

public:
	// Sets default values for this character's properties
	AJCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//�����е��
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//����ͷ
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//�������
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Component")
	UJAttributeComponent* AttributeComp;

	//�����ӿ����
	UJInteractionComponent* InteractionComp;

	//������Ұת��handle
	FTimerHandle ViewModDelay;

	//�����ӳ�
	FTimerHandle AttackDelay;



	//��ǰ�ƶ�
	void MoveForward(float value);
	//�����ƶ�
	void MoveRight(float value);
	//ħ������
	void MagiskProjectileAttack();
	//�ڶ�����
	void BlackholeProjectileAttack();
	//λ��Ͷ����
	void DisplacementProjectileAttack();
	//�����ӵ�
	void SendProjectile(TSubclassOf<AActor>);
	//���ƶ����Ʒ���
	void RotationToMovement();
	//���ӽǿ��Ʒ���
	void RotationToAttack();
	//����
	void PrimaryInteract();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
