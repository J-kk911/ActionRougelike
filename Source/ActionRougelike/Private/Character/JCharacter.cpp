// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile/JMagicProjectile.h"
#include "Character/JAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


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
	
	AttributeComp = CreateDefaultSubobject<UJAttributeComponent>("AttributeComp");

	/*
	* ʹ�� Controller �������������ת
	* ��ʹ�� Controller ���ƽ�ɫ��ת
	* ��ɫ�Զ������˶�����
	*/
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void AJCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//�����󶨵��¼��ϣ������¼�����
	AttributeComp->OnHealthChanged.AddDynamic(this,&AJCharacter::OnHealthChanged);
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AJCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("QuitGame", IE_Pressed, this, &AJCharacter::QuitGame);

	//����
	PlayerInputComponent->BindAction("MagiskProjectil", IE_Pressed, this, &AJCharacter::MagiskProjectileAttack);
	PlayerInputComponent->BindAction("BlackholeProjectile", IE_Pressed, this, &AJCharacter::BlackholeProjectileAttack);
	PlayerInputComponent->BindAction("DisplacementProjectile", IE_Pressed, this, &AJCharacter::DisplacementProjectileAttack);
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




void AJCharacter::MagiskProjectileAttack()
{
	RotationToAttack();

	PlayAnimMontage(AttackAnim);
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AJCharacter::SendProjectile, MagiskProjectileClass);

	//�ӵ��ȴ�����
	GetWorldTimerManager().SetTimer(AttackDelay, TimerDel, TimeToHandUp,false);

}

void AJCharacter::BlackholeProjectileAttack()
{
	RotationToAttack();

	PlayAnimMontage(AttackAnim);
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AJCharacter::SendProjectile, BlackholeProjectileClass);

	//�ӵ��ȴ�����
	GetWorldTimerManager().SetTimer(AttackDelay, TimerDel, TimeToHandUp, false);

}

void AJCharacter::DisplacementProjectileAttack()
{
	RotationToAttack();

	PlayAnimMontage(AttackAnim);
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AJCharacter::SendProjectile, DisplacementProjectileClass);

	//�ӵ��ȴ�����
	GetWorldTimerManager().SetTimer(AttackDelay, TimerDel, TimeToHandUp, false);

}

void AJCharacter::SendProjectile(TSubclassOf<AActor> ProjectileClass){

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
	HandLocation = HandLocation + TargetRotation.Vector() * 30;

	FTransform SpawnTM = FTransform(TargetRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	AActor* SpawnActor =  GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	Super::MoveIgnoreActorAdd(SpawnActor);

}

void AJCharacter::RotationToMovement() {
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetWorldTimerManager().ClearTimer(ViewModDelay);
}

void AJCharacter::RotationToAttack()
{
	//һ����������ɫ�ͳ��򹥻����򣬲��ӳ�1.0f��
	GetWorldTimerManager().SetTimer(ViewModDelay, this, &AJCharacter::RotationToMovement, 1.0f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
}

void AJCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void AJCharacter::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit,true); 
}


void AJCharacter::OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f) {
		PlayAnimMontage(DeadthAnim);
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
		GetWorldTimerManager().SetTimer(RestartLevelTimeHandle,this, &AJCharacter::ReatartLevel, TimeToRestart, false);
	}
}

void AJCharacter::ReatartLevel() {
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->RestartLevel();
}