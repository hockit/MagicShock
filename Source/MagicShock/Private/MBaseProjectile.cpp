// Fill out your copyright notice in the Description page of Project Settings.


#include "MBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMBaseProjectile::AMBaseProjectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AMBaseProjectile::OnActorHit);
	RootComponent = SphereComp;
	SphereComp->SetSphereRadius(20.f);

	ProjectileComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	ProjectileComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	DamageAmount = 1.f;
}

void AMBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AMBaseProjectile::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactCue, GetActorLocation(), GetActorRotation());
		ProjectileComp->DeactivateSystem();
		
		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		Destroy();
	}
}

