// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MBaseProjectile.h"
#include "MExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MAGICSHOCK_API AMExplosiveProjectile : public AMBaseProjectile
{
	GENERATED_BODY()
public:
	AMExplosiveProjectile();

protected:

	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
