// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UJInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//����ͼ���ֶ�����һ�����ʵ�����ӵ�
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

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

	//������Ұת��handle
	FTimerHandle ViewModDelay;

	//�����ӳ�
	FTimerHandle AttackDelay;

	//actor���
	UJInteractionComponent* InteractionComp;

	//��ǰ�ƶ�
	void MoveForward(float value);
	//�����ƶ�
	void MoveRight(float value);
	//��������
	void PrimaryAttack();
	//̧���ӳ�
	void PrimaryAttackDelay();
	//�ָ�������Ұ
	void RotationToMovement();
	//����
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
