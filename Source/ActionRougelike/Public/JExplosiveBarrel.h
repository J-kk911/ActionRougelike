// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include "JExplosiveBarrel.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJExplosiveBarrel();

protected:

	//Mesh ���
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	//����� ���
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	//������Ч
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	//��Ч
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle DestroyTimeHandle;

	UFUNCTION()
	void Destroy();

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
