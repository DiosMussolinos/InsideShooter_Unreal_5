// Fill out your copyright notice in the Description page of Project Settings.


#include "AppealChar.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"
#include "Door.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AAppealChar::AAppealChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	selfRef = this;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;	
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called to bind functionality to input
void AAppealChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		//Jump
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

		//Aim
		PlayerInputComponent->BindAction("ADS", IE_Pressed, this, &AAppealChar::Aim);
		PlayerInputComponent->BindAction("ADS", IE_Released, this, &AAppealChar::StopAiming);

		//Shoot
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAppealChar::Shoot);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &AAppealChar::StopShooting);

		//Equit
		PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AAppealChar::Equipt);

		//Move foward and back
		PlayerInputComponent->BindAxis("MoveForward", this, &AAppealChar::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AAppealChar::MoveRight);

		//Turn around
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("TurnRate", this, &AAppealChar::TurnAtRate);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("LookUpRate", this, &AAppealChar::LookUpAtRate);

		//Change Weapon
		PlayerInputComponent->BindAxis("ChangeGun", this, &AAppealChar::ChangeWeapon);

	}
}

void AAppealChar::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAppealChar::MoveRight(float Value)
{
	if (Controller != nullptr) 
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AAppealChar::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAppealChar::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAppealChar::Aim()
{
	CameraBoom->TargetArmLength = armLenght;
	CameraBoom->SocketOffset = offSet;
}

void AAppealChar::StopAiming()
{
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset.Y = 0.f;
}

void AAppealChar::Shoot()
{
	if (Guns[index])
	{
		AGun* GunCast = Cast<AGun>(Guns[index]);

		if (GunCast)
		{
			//GunCast
			GunCast->isShooting = true;
		}
	}
}

void AAppealChar::StopShooting()
{
	if (Guns[index])
	{
		AGun* GunCast = Cast<AGun>(Guns[index]);

		if (GunCast)
		{
			//GunCast
			GunCast->isShooting = false;
		}
	}
}

void AAppealChar::Equipt()
{
	if (ToEquipGun)
	{

		#pragma region Adaptable_Gun_Handler_WorkingButNeverSawInAShooterGame
		//This will see if there is an available space in the "inventory"
		//if yes, will give the gun
		//if not, will change the gun at the current index to this new one
		/*
		if (Guns[index])
		{
			for (int i = 0; i < Guns.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("%d"), i);
				if (!Guns[i])
				{
					UE_LOG(LogTemp, Warning, TEXT("UPDATE GUN"));

					Guns[i] = ToEquipGun;
					break;
				}
			}
		}
		else
		{
			Guns[index] = ToEquipGun;
		}
		*/
		#pragma endregion

		#pragma region If_Null_Occupy_WarzoneType
		Guns[index] = ToEquipGun;

		AGun* GunCast = Cast<AGun>(Guns[index]);

		if (GunCast)
		{
			GunCast->equipted = true;

			if (ammo >= GunCast->innerAmmoMax)
			{
				GunCast->innerAmmo = ammo - GunCast->innerAmmoMax;

				ammo = FGenericPlatformMath::Min(ammo, GunCast->innerAmmoMax);

				if (ammo < 0)
				{
					ammo = 0;
				}
			}
			else
			{
				GunCast->innerAmmo = ammo;

				ammo = 0;
			}
		}
		#pragma endregion
	}
	
	if (door)
	{
		FVector OtherActorLoc = door->GetActorLocation();
		FVector Direction = GetActorLocation() - OtherActorLoc;
		ADoor* doorCast = Cast<ADoor>(door);


		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, door->GetActorRotation());

		if (!doorCast->open)
		{
			if (Direction.X > 0.f)
			{
				doorCast->rotateValue = 90.f;
			}
			else
			{
				doorCast->rotateValue = -90.f;
			}

			doorCast->open = true;
		}
		else
		{
			doorCast->open = false;
		}
	}
}

void AAppealChar::ChangeWeapon(float Value)
{
	if (Value != 0)
	{
		index += Value;

		if (index < 0)
		{
			index = Guns.Num() - 1;
		}

		if (index > Guns.Num() - 1)
		{
			index = 0;
		}
	}
}

void AAppealChar::ChangeAmmo(int AddValue)
{
	ammo += AddValue;
}
