// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "JBaseProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJBaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//�������
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;
	//�ƶ����
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* MovementComp;
	//����������Ч
	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent* ParticleStartComp;
	//����������Ч
	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent* ParticleFlyComp;
	//����������Ч
	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent* ParticleEndComp;
	//������Ч
	UPROPERTY(VisibleAnywhere, Category = "Audio")
		UAudioComponent* AudioStartComp;
	//������Ч
	UPROPERTY(VisibleAnywhere, Category = "Audio")
		UAudioComponent* AudioFlyComp;
	//������Ч
	UPROPERTY(VisibleAnywhere, Category = "Audio")
		UAudioComponent* AudioEndComp;
	
	//ײ����
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Destroy();
protected:
	UPROPERTY(VisibleAnywhere)
		float TimeToDestroy = 0.5;
	UPROPERTY(VisibleAnywhere)
		FTimerHandle DestroyTimeHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
