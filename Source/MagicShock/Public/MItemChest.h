// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGameplayInterface.h"
#include "MItemChest.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class MAGICSHOCK_API AMItemChest : public AActor, public IMGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMItemChest();

	UPROPERTY(EditAnywhere)
	float TargetRoll;

	void Interact_Implementation(APawn* InstigatorPawn);
	
protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TreasureMesh;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
};
