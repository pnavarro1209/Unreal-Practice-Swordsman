// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Sword.h"
#include "GameFramework/Character.h"
#include "SwordFighter.generated.h"

UCLASS()
class SWORDFIGHT_PRACTICE_API ASwordFighter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwordFighter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon();

	UFUNCTION(BlueprintPure)
	bool GetIsJumping();

	UFUNCTION(BlueprintPure)
	bool GetIsAttacking();

	UFUNCTION(BlueprintPure)
	bool GetIsAttackingHeavy();

	UFUNCTION(BlueprintPure)
	bool GetIsDodging();

	UFUNCTION(BlueprintCallable)
    void ResetJumping();

	UFUNCTION(BlueprintCallable)
    void ResetAttacking();

	UFUNCTION(BlueprintCallable)
    void ResetAttackingHeavy();

	UFUNCTION(BlueprintCallable)
    void ResetDodging();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveRight(float AxisValue);
	void MoveForward(float AxisValue);
	void CameraUpRate(float AxisValue);
	void CameraRightRate(float AxisValue);
	virtual void Jump() override;
	void Attack();
	void HeavyAttack();
	void Dodge();

	UPROPERTY(EditAnywhere)
	float RotationRate = 20.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASword> EquipSwordClass;

	ASword* Sword;

	FTimerHandle EquipTimer;

	bool bJump = false;
	bool bAttack = false;
	bool bHeavyAttack = false;
	bool bDodge = false;
};
