// Fill out your copyright notice in the Description page of Project Settings.


#include "JMagicProjectile.h"

// Sets default values
AJMagicProjectile::AJMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ʼ�����岢��Ϊ�����
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	//��ײ�趨ΪProjectileԤ��
	SphereComp->SetCollisionProfileName("Projectile");


	//��ʼ���˶�
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");

	MovementComp->InitialSpeed = 1000.0F;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	//��ʼ��������Ч
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	//����������ײ��
	EffectComp->SetupAttachment(SphereComp);

}

// Called when the game starts or when spawned
void AJMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

