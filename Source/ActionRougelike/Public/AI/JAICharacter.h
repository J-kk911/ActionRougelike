// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "JAICharacter.generated.h"

class JAttributeComponent;
class UJAttributeComponent;
class UBlackboardComponent;
UCLASS()
class ACTIONROUGELIKE_API AJAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//���������
	UFUNCTION()
	void HaveSeePawn(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�ڰ������Դ
	UPROPERTY(EditAnywhere)
		UBlackboardComponent* BlackboardComp;

	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UJAttributeComponent* AttributeComp;

	//�Ӿ�
	UPROPERTY(EditAnywhere, Category = See)
		UPawnSensingComponent* PawnSensingComp;

	//��������
	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* DeadthAnim;

	UPROPERTY()
		AController* MyController;

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta);

	

//����
protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
		float AttackCD = 5.0f;

	UPROPERTY(EditAnywhere,Category="Attack")
		float AttackRadius = 500.0f;

	UPROPERTY(EditAnyWhere, Category = "Attack")
		float TimeToDealDemage = 0.5f;

	UPROPERTY(EditAnyWhere, Category = "Attack")
		float Demage = 10.0f;

	UPROPERTY(EditAnyWhere, Category = "Attack")
		float IdleTime = 0.5f;


	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackedAnim;

	UFUNCTION()
		void AttackCDClaer();

	UFUNCTION(BlueprintCallable)
		void DealDemage();

	UFUNCTION(BlueprintCallable)
		void AttackedLatelyClear();


public:
	UPROPERTY(VisibleAnywhere)
		FTimerHandle AttackTimeHandle;

	UPROPERTY()
		FTimerHandle AttackedLatelyTimeHandle;

	UPROPERTY()
		FTimerHandle AttackCDTimeHandle;

	UPROPERTY()
		FTimerHandle IdleTimeHandle;

	UFUNCTION()
		void Attack();

};
