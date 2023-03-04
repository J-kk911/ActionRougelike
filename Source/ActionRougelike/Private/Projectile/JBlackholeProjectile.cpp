// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/JBlackholeProjectile.h"

AJBlackholeProjectile::AJBlackholeProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 750.0f;
	RadialForceComp->ForceStrength = -5000000.0f;
	RadialForceComp->bImpulseVelChange = true;
	//��Ӱ���ɫ
	//RadialForceComp
	//����ײ�Ķ�����������
	RadialForceComp->RemoveObjectTypeToAffect(ObjectTypeQuery3);//��Ӱ��pawn
	RadialForceComp->AddObjectTypeToAffect(ObjectTypeQuery2);//Ӱ��WorldDynamic

	SphereComp->SetCollisionProfileName("OverlapAll");

}

void AJBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExisetTimeHandle, this, &AJBlackholeProjectile::ReadyToDestroy, ExistTime);
}

void AJBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
