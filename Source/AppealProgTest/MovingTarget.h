// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTarget.generated.h"

UCLASS()
class APPEALPROGTEST_API AMovingTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NotifyActorBeginOverlap(AActor* OtherActor);

	void MoveActor(float DeltaTime);

	void Fall(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* gunOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		TArray<FVector> positions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		int targetMoveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float distanceToUpdate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float LerpAlpha = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		bool hitted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		FRotator hittedAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		float timer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		float timerDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		int valuePoints;


};
