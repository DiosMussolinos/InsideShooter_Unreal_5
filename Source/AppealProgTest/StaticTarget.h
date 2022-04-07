// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticTarget.generated.h"

UCLASS()
class APPEALPROGTEST_API AStaticTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NotifyActorBeginOverlap(AActor* OtherActor);

public:	


	AActor* gunOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		int valuePoints;
};
