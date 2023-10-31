// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGameplayInterface.h"
#include "MPickupItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class MAGICSHOCK_API AMPickupItem : public AActor, public IMGameplayInterface
{
	GENERATED_BODY()
	
public:	
	
	AMPickupItem();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BottleMesh;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* EffectVFX;


};
