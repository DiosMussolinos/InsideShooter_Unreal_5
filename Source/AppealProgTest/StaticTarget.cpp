// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticTarget.h"
#include "AppealChar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStaticTarget::AStaticTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStaticTarget::BeginPlay()
{
	Super::BeginPlay();
	
	gunOwner = UGameplayStatics::GetActorOfClass(GetWorld(), AAppealChar::StaticClass());

}

void AStaticTarget::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Projectile"))
		{
			AAppealChar* CastChar = Cast<AAppealChar>(gunOwner);

			CastChar->points += valuePoints;

			Destroy();
		}
	}
}

