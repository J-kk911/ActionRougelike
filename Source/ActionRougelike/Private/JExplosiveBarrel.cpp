// Fill out your copyright notice in the Description page of Project Settings.


#include "JExplosiveBarrel.h"
#include "Projectile/JMagicProjectile.h"


// Sets default values
AJExplosiveBarrel::AJExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;
	 

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(MeshComp);
	//Ӱ��worldDynamic
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->Radius = 750.0f;
	//ǿ��,������������
	RadialForceComp->ImpulseStrength = 1000.0f;
	RadialForceComp->bImpulseVelChange = true;

	//shift+alt+s �����÷�
	MeshComp->OnComponentHit.AddDynamic(this, &AJExplosiveBarrel::OnActorHit);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

}


void AJExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//ͨ���ܲ���ת���ж��ǲ���Ŀ����
	AJMagicProjectile* MagicProjectile = Cast<AJMagicProjectile>(OtherActor);
	if(MagicProjectile){
		RadialForceComp->FireImpulse();
		GetWorldTimerManager().SetTimer(DestroyTimeHandle,this,&AJExplosiveBarrel::Destroy,1.0f,false);
	}

}

void AJExplosiveBarrel::Destroy()
{
	GetWorld()->DestroyActor(this);
}

