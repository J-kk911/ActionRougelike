// Fill out your copyright notice in the Description page of Project Settings.


#include "JExplosiveBarrel.h"
#include "Projectile/JMagicProjectile.h"
#include "Character/JAttributeComponent.h"
#include "DrawDebugHelpers.h"


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
	RadialForceComp->Radius = ImpulseRadius;
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
	if(MagicProjectile == NULL || Hited == true){
		return;
	}

	EffectComp->SetActive(false);
	RadialForceComp->FireImpulse();
	Hited = true;

	TArray<struct FOverlapResult> OutOverlaps;
	const FVector Pos = GetActorLocation(); 
	FQuat Rot = GetActorQuat();
	ECollisionChannel TraceChannel = ECC_Pawn;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ImpulseRadius);
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	GetWorld()->OverlapMultiByChannel(OutOverlaps, Pos, Rot, TraceChannel, CollisionShape);

	for (auto OverLapPawn : OutOverlaps) 
	{
		//�������������Ѫ
		UJAttributeComponent* AttributeComp = Cast<UJAttributeComponent>(OverLapPawn.Actor->GetComponentByClass(UJAttributeComponent::StaticClass()));
		if (AttributeComp) {
			//��ʾ��ֵ�˺�
			DrawDebugString(GetWorld(), OverLapPawn.GetActor()->GetActorLocation(), TEXT("-20"), NULL, FColor::Red, 0.5, false, 1.f);
			AttributeComp->ApplyHealthChange(-50.0);
		}
	}
}


