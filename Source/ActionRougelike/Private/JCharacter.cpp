// Fill out your copyright notice in the Description page of Project Settings.


#include "JCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "JInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "JMagicProjectile.h"


// Sets default values
AJCharacter::AJCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//����ʵ�����������ڸ����
	SpringArmComp = CreateDefaultSubobject <USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject <UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UJInteractionComponent>("InteractionComp");
	
	//ʹ�� Controller �������������ת
	SpringArmComp->bUsePawnControlRotation = true;

	//��ɫ����controller����

	//��ʹ�� Controller ���ƽ�ɫ��ת
	bUseControllerRotationYaw = false;
	
	//��ɫ�Զ������˶�����
	GetCharacterMovement()->bOrientRotationToMovement = true;

	
}

// Called when the game starts or when spawned
void AJCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}





// Called every frame
void AJCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//UE_LOG(LogTemp, Error, TEXT("%d"), bUseControllerRotationYaw ? 1 : 0);

}

// Called to bind functionality to input
void AJCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�ƶ�
	PlayerInputComponent->BindAxis("MoveForward",this,&AJCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJCharacter::MoveRight);


	//�ӽǣ����������뵽 Controller
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//����
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&AJCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AJCharacter::PrimaryInteract);
}


void AJCharacter::MoveForward(float value)
{

	//��������Rotation����
	FRotator ControlRot = GetControlRotation();
	//ת��Ϊ�����ǰ������
	FVector ContorlFrontVector = UKismetMathLibrary::GetForwardVector(ControlRot);
	//���뵽input
	AddMovementInput(ContorlFrontVector, value);
}

void AJCharacter::MoveRight(float value)
{

	//��������Rotation����
	FRotator ControlRot = GetControlRotation();
	//ת��Ϊ�����ǰ������
	FVector ContorlRightVector = UKismetMathLibrary::GetRightVector(ControlRot);
	//���뵽Movementinput
	AddMovementInput(ContorlRightVector,value);
}




void AJCharacter::PrimaryAttack()
{
	//һ����������ɫ�ͳ��򹥻����򣬲��ӳ�1.0f��
	GetWorldTimerManager().SetTimer(ViewModDelay,this,&AJCharacter::RotationToMovement,1.0f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	//SetActorRotation()�����ӳ�

	PlayAnimMontage(AttackAnim);
	//�ӳٲ��Ŷ���
	GetWorldTimerManager().SetTimer(AttackDelay, this, &AJCharacter::PrimaryAttackDelay, TimeToHandUp);

}
void AJCharacter::PrimaryAttackDelay(){
	//���������Ϸ���
	FVector HandLocation = GetMesh()->GetSocketLocation("ik_hand_r");

	//���߼��
	FHitResult OutHit;
	FVector Start = CameraComp->GetComponentLocation();
	FRotator StartRotation = CameraComp->GetComponentRotation();
	FVector End = Start + (StartRotation.Vector() * 100000);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Start.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *End.ToString());
	// 
	//���߼�⣺ �������������㣬�����յ㣬�������ͣ��������壻
	bool bBlock = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_WorldDynamic, Params);

	FRotator TargetRotation;
	if (bBlock) {
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, OutHit.Location);
		//UE_LOG(LogTemp, Warning, TEXT("FIND:%s"), *OutHit.Location.ToString());
	}else{
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
		//UE_LOG(LogTemp, Warning, TEXT("NOT FIND:%s"), *End.ToString());
		
	}

	FTransform SpawnTM = FTransform(TargetRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void AJCharacter::RotationToMovement() {
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetWorldTimerManager().ClearTimer(ViewModDelay);
}

void AJCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}