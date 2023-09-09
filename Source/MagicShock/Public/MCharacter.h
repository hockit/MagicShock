// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UMInteractionComponent;
class AMBaseSpell;

UCLASS()
class MAGICSHOCK_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* LeftArmMesh;

	UPROPERTY(VisibleAnywhere)
	UMInteractionComponent* InteractionComp;

	// FUNCTIONS

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Crouch();

	void PrimaryInteract();
	void PrimaryAttack();


	// VARIABLES

	bool bIsCrouch;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMBaseSpell> SpellClass;

	UPROPERTY()
	AMBaseSpell* BaseSpell;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
