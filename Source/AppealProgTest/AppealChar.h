// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AppealChar.generated.h"

UCLASS()
class APPEALPROGTEST_API AAppealChar : public ACharacter
{
	GENERATED_BODY()
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	// Sets default values for this character's properties
	AAppealChar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor* selfRef;

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void Aim();

	void StopAiming();

	void Shoot();
	
	void StopShooting();

	void Equipt();

	void ChangeWeapon(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aim")
		FVector offSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aim")
		float armLenght = 75.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guns")
		TArray<AActor*> Guns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guns")
		int index = 0;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guns")
		int ammo = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guns")
		AActor* ToEquipGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Doors")
		AActor* door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guns")
		int points = 0;

	void ChangeAmmo(int AddValue);

};
