// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "AppealChar.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	doorRotation = GetActorRotation();

	if (open)
	{
		SetActorRotation(FMath::Lerp(doorRotation, FRotator(0.0f, rotateValue, 0.f), 0.1f));
	}
	else
	{
		SetActorRotation(FMath::Lerp(doorRotation, FRotator(0.0f, 0.0f, 0.0f), 0.1f));
	}
}

void ADoor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->IsA<AAppealChar>())
		{
			//Open Manually
			AAppealChar* charCast = Cast<AAppealChar>(OtherActor);

			charCast->door = this;

			/* Open for you

			FVector OtherActorLoc = OtherActor->GetActorLocation();
			FVector Direction = GetActorLocation() - OtherActorLoc;

			Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

			if (Direction.X > 0.f)
			{
				rotateValue = -90.f;
			}
			else
			{
				rotateValue = 90.f;
			}

			open = true;
			*/
		}
	}
}

void ADoor::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->IsA<AAppealChar>())
		{
			//Open Manually
			AAppealChar* charCast = Cast<AAppealChar>(OtherActor);

			charCast->door = nullptr;

			/* Close For you
			open = false;
			*/
		}
	}
}



