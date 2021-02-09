// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordFighter.h"

#include "TimerManager.h"

// Sets default values
ASwordFighter::ASwordFighter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASwordFighter::BeginPlay()
{
	Super::BeginPlay();

	Sword = GetWorld()->SpawnActor<ASword>(EquipSwordClass);
	Sword->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_WeaponSpine"));
	Sword->SetOwner(this);

	GetWorldTimerManager().SetTimer(EquipTimer, this, &ASwordFighter::EquipWeapon, 0.5f);
}

// Called every frame
void ASwordFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASwordFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASwordFighter::Jump);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASwordFighter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASwordFighter::MoveForward);
	PlayerInputComponent->BindAxis("CameraRightRate", this, &ASwordFighter::CameraRightRate);
	PlayerInputComponent->BindAxis("CameraUpRate", this, &ASwordFighter::CameraUpRate);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ASwordFighter::Attack);
	PlayerInputComponent->BindAction("HeavyAttack", EInputEvent::IE_Pressed, this, &ASwordFighter::HeavyAttack);
	PlayerInputComponent->BindAction("Dodge", EInputEvent::IE_Pressed, this, &ASwordFighter::Dodge);
}

void ASwordFighter::EquipWeapon()
{
	if(Sword != nullptr)
	{
		Sword->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Weapon"));
	}
}

void ASwordFighter::MoveRight(float AxisValue)
{
	if(bAttack || bHeavyAttack)
		return;
	
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASwordFighter::MoveForward(float AxisValue)
{
	if(bAttack || bHeavyAttack)
		return;
	
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASwordFighter::CameraUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASwordFighter::CameraRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASwordFighter::Dodge()
{
	bDodge = true;
	
}

void ASwordFighter::HeavyAttack()
{
	bHeavyAttack = true;
}

void ASwordFighter::Attack()
{
	bAttack = true;
}

void ASwordFighter::Jump()
{
	Super::Jump();
	bJump = true;
}

bool ASwordFighter::GetIsJumping()
{
	return bJump;
}

bool ASwordFighter::GetIsAttacking()
{
	return bAttack;
}

bool ASwordFighter::GetIsAttackingHeavy()
{
	return bHeavyAttack;
}

bool ASwordFighter::GetIsDodging()
{
	return bDodge;
}

void ASwordFighter::ResetJumping()
{
	bJump = false;
}

void ASwordFighter::ResetAttacking()
{
	bAttack = false;
}

void ASwordFighter::ResetAttackingHeavy()
{
	bHeavyAttack = false;
}

void ASwordFighter::ResetDodging()
{
	bDodge = false;
}

