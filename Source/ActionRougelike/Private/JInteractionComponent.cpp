// Fill out your copyright notice in the Description page of Project Settings.


#include "JInteractionComponent.h"
#include "JGamePlayInterface.h"


// Sets default values for this component's properties
UJInteractionComponent::UJInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UJInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJInteractionComponent::PrimaryInteract()
{

	FHitResult OutHit;
	FVector EyeLocation;

	AActor* Myowner = GetOwner();
	FRotator EyeRoation;
	Myowner->GetActorEyesViewPoint(EyeLocation,EyeRoation);

	FVector End = EyeLocation + (EyeRoation.Vector()*1000);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Myowner);

	//���߼�⣺ �������������㣬�����յ㣬������壬�������壻
	GetWorld()->LineTraceSingleByChannel(OutHit, EyeLocation, End, ECC_WorldStatic, Params);

	AActor* HitActor = OutHit.GetActor();
	if (HitActor) {
		//������Ŀ��̳��Ի����ӿ�
		if (HitActor->Implements<UJGamePlayInterface>()) 
		{
			APawn* MyPawn = Cast<APawn>(Myowner);
			IJGamePlayInterface::Execute_Interact(HitActor,MyPawn);
		}
	}

}