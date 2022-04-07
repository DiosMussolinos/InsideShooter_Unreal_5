// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingTarget.h"
#include "AppealChar.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMovingTarget::AMovingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingTarget::BeginPlay()
{
	Super::BeginPlay();
	
	positions[0] = GetActorLocation();

	targetMoveIndex = 1;

	gunOwner = UGameplayStatics::GetActorOfClass(GetWorld(), AAppealChar::StaticClass());


}

void AMovingTarget::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!hitted)
	{
		if (OtherActor)
		{
			if (OtherActor->ActorHasTag("Projectile"))
			{
				hitted = true;

				AAppealChar* CastChar = Cast<AAppealChar>(gunOwner);

				CastChar->points += valuePoints;
			}
		}
	}
}


// Called every frame
void AMovingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!hitted)
	{
		MoveActor(DeltaTime);
	}
	else
	{
		Fall(DeltaTime);
	}

}

void AMovingTarget::MoveActor(float DeltaTime)
{
	//Verify target location && Update
	if (FVector::Distance(GetActorLocation(), positions[targetMoveIndex]) < distanceToUpdate)
	{
		if (targetMoveIndex == positions.Num() - 1)
		{
			targetMoveIndex = 0;
		}
		else
		{
			targetMoveIndex++;
		}
	}

	SetActorLocation(FMath::Lerp(GetActorLocation(), positions[targetMoveIndex], LerpAlpha * DeltaTime));
}

void AMovingTarget::Fall(float DeltaTime)
{
	timer -= DeltaTime;

	if (timer > 0.2 * timerDefault)
	{
		SetActorRotation(FMath::Lerp(GetActorRotation(), hittedAngle, LerpAlpha * DeltaTime));
	}
	else
	{
		SetActorRotation(FMath::Lerp(GetActorRotation(), FRotator(0,0,0), LerpAlpha * DeltaTime));

		if (GetActorRotation().Roll > -2)
		{
			SetActorRotation(FRotator(0,0,0));
			timer = timerDefault;
			hitted = false;
		}
	}
}