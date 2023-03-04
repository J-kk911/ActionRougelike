// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JGamePlayInterface.h"
#include "Components/TimelineComponent.h"
#include "JItemChest.generated.h"



UCLASS()
class ACTIONROUGELIKE_API AJItemChest : public AActor, public IJGamePlayInterface
{
	GENERATED_BODY()
	//ʵ�ֽӿ�
	void Interact_Implementation(APawn* OperaterPawn) override;

public:	
	// Sets default values for this actor's properties
	AJItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LidMesh;

	//����һ��ʱ�����¼�����������ڼ����ʱ�򣬲��ϴ����¼�
	UPROPERTY(EditDefaultsOnly)
		UTimelineComponent* OpenTimeline;

	// �������߶���,Ҫ����ͼ��
	UPROPERTY(EditDefaultsOnly)
		UCurveFloat* Curver;

	UPROPERTY(EditDefaultsOnly)
		bool Open = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnTimelineTick(float OpenAngle);	// Timeline ����ʱ����

};
