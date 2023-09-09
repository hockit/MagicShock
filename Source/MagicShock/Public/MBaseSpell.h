// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBaseSpell.generated.h"

class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class MAGICSHOCK_API AMBaseSpell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMBaseSpell();

	void Explode();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* EffectVFX;

};
