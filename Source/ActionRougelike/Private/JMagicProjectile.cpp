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

	//��ʼ��Ĭ����Դ
	//��̬������Դ
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(
		TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_Projectile.P_Gideon_Primary_Projectile"));
	EffectComp->SetTemplate(ParticleAsset.Object);

	//����������ײ��
	EffectComp->SetupAttachment(SphereComp);

	//��ײ��ʱ����
	SphereComp->OnComponentHit.AddDynamic(this,&AJMagicProjectile::OnActorHit);

	//�������
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");

	//���ݾ���˥��
	AudioComp->bOverrideAttenuation = true;
	//AudioComp->SetAutoActivate(false);

	IsHit = false;
	WaitTick = 30;

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
	DestroyCheck();
}

void AJMagicProjectile::DestroyCheck()
{
	if (IsHit) {
		WaitTick--;
		if (WaitTick == 0) {
			GetWorld()->DestroyActor(this);
		}
	}
}

void AJMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	USoundBase* sb = LoadObject<USoundBase>(nullptr,TEXT("/Game/ExampleContent/Audio/Abilities/A_Ability_MeteorImpact01.A_Ability_MeteorImpact01"));
	AudioComp->SetSound(sb);
	AudioComp->Play(); 
		
	//��̬������Դ
	UParticleSystem* ps = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitWorld.P_Gideon_Primary_HitWorld"));
	EffectComp->SetTemplate(ps);

	IsHit = true;
}