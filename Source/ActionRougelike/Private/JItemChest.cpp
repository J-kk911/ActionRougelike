// Fill out your copyright notice in the Description page of Project Settings.


#include "JItemChest.h"

// Sets default values
AJItemChest::AJItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>("OpenTimeline");

	Curver = CreateDefaultSubobject<UCurveFloat>("Curver");

	//������������
	FRichCurve RichCurve;
	FKeyHandle KeyHandle;

	//��Ϊƽ��
	KeyHandle = RichCurve.AddKey(0, 0);
	Curver->FloatCurve.SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Cubic);
	KeyHandle = RichCurve.AddKey(0.5, 110);
	Curver->FloatCurve.SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Cubic);

	Curver->FloatCurve = RichCurve;

}

// Called when the game starts or when spawned
void AJItemChest::BeginPlay()
{
	Super::BeginPlay();

	//�ⲿ�ֲ����ڹ��캯�����Ϊcurve��û��
	if (Curver) {
		/*
		* �����ֱ�ͨ��TEXT���������������ٴ���Timeline�У�ע���������
		* һ���ǹ�����
		* һ���ǽ���ʱ�򴥷�
		*/
		FOnTimelineFloat OnTimelineFloatEvent;
		FOnTimelineEvent OnTimelineFinishedEvent;

		OnTimelineFloatEvent.BindUFunction(this, TEXT("OnTimelineTick"));
		//OnTimelineFinishedEvent.BindUFunction(this, TEXT("SetState"));

		OpenTimeline->AddInterpFloat(Curver, OnTimelineFloatEvent);
		//OpenTimeline->SetTimelineFinishedFunc(OnTimelineFinishedEvent);

		//���ý���ʱ��Ϊ���һ���ؼ�֡
		OpenTimeline->SetTimelineLength(ETimelineLengthMode::TL_LastKeyFrame);
	}

}

// Called every frame
void AJItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJItemChest::Interact_Implementation(APawn* OperaterPawn)
{
	if (!OpenTimeline->IsPlaying()) {
		if (Open) {
			OpenTimeline->ReverseFromEnd();
		}else{
			OpenTimeline->PlayFromStart();
		}
		Open = !Open;
	}
}

void AJItemChest::OnTimelineTick(float Output)
{
	//UE_LOG(LogTemp, Warning, TEXT("output:%f"), Output);
	LidMesh->SetRelativeRotation(FRotator(Output, 0, 0));

}

