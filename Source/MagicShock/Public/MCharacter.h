// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UMInteractionComponent;
class USoundBase;
class UMAttributeComponent;
class UParticleSystemComponent;

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
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	UMInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UParticleSystem* MuzzleVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	USoundBase* MuzzleSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* DeathSound;

	// FUNCTIONS

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwnComp, float NewHealth, float Delta);
	virtual void PostInitializeComponents() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Crouch();

	void PrimaryInteract();
	void PrimaryAttack();
	void SecondaryAttack();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);


	// VARIABLES

	bool bIsCrouch;

	float DamageAmount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
