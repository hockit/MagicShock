// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MAICharacter.generated.h"

class UMAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class MAGICSHOCK_API AMAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMAICharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* DeathVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMAttributeComponent* AttributeComp;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwnComp, float NewHealth, float Delta);
};
