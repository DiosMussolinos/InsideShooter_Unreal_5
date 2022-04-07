// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UCLASS()
class APPEALPROGTEST_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo();

protected:

	void NotifyActorBeginOverlap(AActor* OtherActor);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int ammoValue;
};
