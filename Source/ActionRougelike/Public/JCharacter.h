// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	AJCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//�����е��
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//����ͷ
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//��ǰ�ƶ�
	void MoveForward(float value);
	//�����ƶ�
	void MoveRight(float value);
	//��������
	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
