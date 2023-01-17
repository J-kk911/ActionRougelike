// Fill out your copyright notice in the Description page of Project Settings.


#include "JBaseProjectile.h"

// Sets default values
AJBaseProjectile::AJBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	* ��ʼ�����岢��Ϊ�����
	* ��ײ�趨ΪProjectileԤ��
	* ��ģ������
	*/
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->SetSimulatePhysics(false);
	RootComponent = SphereComp;

	//��ʼ���˶�
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0F;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	//Particle
	ParticleStartComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleStartComp");
	ParticleStartComp->SetupAttachment(RootComponent);
	ParticleFlyComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleFlyComp");
	ParticleFlyComp->SetupAttachment(RootComponent);
	ParticleEndComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEndComp");
	ParticleEndComp->SetupAttachment(RootComponent);
	ParticleEndComp->SetAutoActivate(false);

	//Audio
	AudioStartComp = CreateDefaultSubobject<UAudioComponent>("AudioStartComp");
	AudioStartComp->SetupAttachment(RootComponent);
	AudioStartComp->bOverrideAttenuation = true;
	AudioFlyComp = CreateDefaultSubobject<UAudioComponent>("AudioFlyComp");
	AudioFlyComp->SetupAttachment(RootComponent);
	AudioFlyComp->bOverrideAttenuation = true;
	AudioEndComp = CreateDefaultSubobject<UAudioComponent>("AudioEndComp");
	AudioEndComp->SetupAttachment(RootComponent);
	AudioEndComp->bOverrideAttenuation = true;
	AudioEndComp->SetAutoActivate(false);


}

// Called when the game starts or when spawned
void AJBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	//����ײ��
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.AddDynamic(this, &AJBaseProjectile::OnActorHit);
}


// Called every frame
void AJBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AJBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ParticleFlyComp->Activate(false);
	ParticleEndComp->Activate(true);

	AudioFlyComp->Activate(false);
	AudioEndComp->Activate(true);

	GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &AJBaseProjectile::Destroy, TimeToDestroy);
	
}

void AJBaseProjectile::Destroy()
{
	GetWorld()->DestroyActor(this);
}
