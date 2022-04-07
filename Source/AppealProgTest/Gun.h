// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM()
enum GunEnum
{
	Riffle		  UMETA(DisplayName = "Rifle"),
	CrossBow      UMETA(DisplayName = "CrossBow"),
	Sniper		  UMETA(DisplayName = "Sniper"),
	Pistol		  UMETA(DisplayName = "Pistol")
};

UCLASS()
class APPEALPROGTEST_API AGun : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NotifyActorBeginOverlap(AActor* OtherActor);

	void NotifyActorEndOverlap(AActor* OtherActor);

	void CreateProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shooting(float DeltaTime);
	void UpdateAmmoOnReload();
	void PlaySound();
	void Reload(float DeltaTime);
	
	AActor* gunOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		TEnumAsByte<GunEnum> GunType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		bool equipted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		bool isShooting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		bool monoShoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		float reloadTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		float reloadTimeDefault = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		float timeBetweenShots = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		float timeBetweenShotsDefault = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "This Gun")
		TSubclassOf<AActor> projectileBp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "This Gun")
		TArray <USoundBase*> FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "This Gun")
		int innerAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "This Gun")
		int innerAmmoMax = 30;

};
