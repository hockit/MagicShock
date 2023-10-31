// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MBaseProjectile.h"
#include "MMagicProjectile.generated.h"


UCLASS()
class MAGICSHOCK_API AMMagicProjectile : public AMBaseProjectile
{
	GENERATED_BODY()

public:
	AMMagicProjectile();

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
