// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "AppealChar.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	gunOwner = UGameplayStatics::GetActorOfClass(GetWorld(), AAppealChar::StaticClass());
	
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Shooting(DeltaTime);
}

void AGun::Shooting(float DeltaTime)
{

	#pragma region continuous_and_single_shoot
	if (equipted)
	{
		if (innerAmmo > 0)
		{
			if (isShooting)
			{
				if (GunType == Riffle)
				{
					timeBetweenShots -= DeltaTime;

					if (timeBetweenShots < 0)
					{
						PlaySound();
						CreateProjectile();
						innerAmmo--;
						timeBetweenShots = timeBetweenShotsDefault;
					}
				}
				else
				{
					PlaySound();
					CreateProjectile();
					innerAmmo--;
					isShooting = false;
				}
			}
		}
		else
		{
			Reload(DeltaTime);
		}
	}
	#pragma endregion

}

void AGun::PlaySound()
{
	int rand = FMath::RandRange(0, FireSound.Num() - 1);
	 
	// try and play the sound if specified
	if (FireSound[rand])
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound[rand], gunOwner->GetActorLocation());
	}
	
}

void AGun::CreateProjectile()
{
	FVector location = gunOwner->GetActorLocation();
	FRotator rot = gunOwner->GetActorRotation();

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBp, location, rot);
}

void AGun::Reload(float DeltaTime)
{
	reloadTime -= DeltaTime;

	if (reloadTime < 0)
	{
		AAppealChar* CharCast = Cast<AAppealChar>(gunOwner);

		innerAmmo = FGenericPlatformMath::Min(innerAmmoMax, CharCast->ammo);
		CharCast->ammo = FGenericPlatformMath::Min(CharCast->ammo, innerAmmoMax);
		reloadTime = reloadTimeDefault;
	}

}

void AGun::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->IsA<AAppealChar>())
		{
			AAppealChar* castChar = Cast<AAppealChar>(OtherActor);

			if (castChar)
			{
				castChar->ToEquipGun = this;
			}
		}
	}
}

void AGun::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->IsA<AAppealChar>())
		{
			AAppealChar* castChar = Cast<AAppealChar>(OtherActor);

			if (castChar)
			{
				castChar->ToEquipGun = nullptr;
			}
		}
	}
}