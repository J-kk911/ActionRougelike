// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "JMagicProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//�������
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	//�ƶ����
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	//������Ч���
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
	
	//�ȴ�����ʱ��
	UPROPERTY(VisibleAnywhere)
	uint64 WaitTime = 0.5; 

	//�ӳ�����
	FTimerHandle TimeToDestroy;

	//������Ч
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;


	//�����
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//����
	void Destroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
