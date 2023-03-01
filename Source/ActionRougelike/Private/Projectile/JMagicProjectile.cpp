// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/JMagicProjectile.h"
#include "DrawDebugHelpers.h"
#include "Character/JAttributeComponent.h"


// Sets default values
AJMagicProjectile::AJMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp->InitialSpeed = 2000.0F;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AJMagicProjectile::OnActorBeginOverlap);

}


void AJMagicProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Error, TEXT("begin overlap"));
	//��Ϊ��Overlap�����Կ����պ������ж��ǲ��Ƕ���
	if (OtherActor) {
		//ͨ��actor���ܲ����ҵ� ������� �ж��ܲ��ܽ��ܴ��
		UJAttributeComponent* AttributeComp = Cast<UJAttributeComponent>(OtherActor->GetComponentByClass(UJAttributeComponent::StaticClass()));
		if (AttributeComp != nullptr) {
			if (Hit)return;
			if (this->GetInstigator()) {
				UE_LOG(LogTemp, Warning, TEXT("Projectile"));

			}
			//��ʾ��ֵ�˺�
			AttributeComp->ApplyHealthChange(-20.0,OtherActor->GetActorLocation(), this->GetInstigator());
			ReadyToDestroy();
			Hit = true;
		}
	}

}




