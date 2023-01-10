// Fill out your copyright notice in the Description page of Project Settings.


#include "JCharacter.h"
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


	//ʹ�� Controller �������������ת
	SpringArmComp->bUsePawnControlRotation = true;
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
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
	AddMovementInput(ContorlRightVector, value);
}




void AJCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

}