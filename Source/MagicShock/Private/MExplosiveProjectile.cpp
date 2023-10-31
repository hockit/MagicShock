// Fill out your copyright notice in the Description page of Project Settings.


#include "MExplosiveProjectile.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "MAttributeComponent.h"


AMExplosiveProjectile::AMExplosiveProjectile()
{
	DamageAmount = 100.f;
}

void AMExplosiveProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		SphereComp->SetSphereRadius(300.f);
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

		for (auto Actor : OverlappingActors)
		{
			UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(Actor->GetComponentByClass(UMAttributeComponent::StaticClass()));
			
			if (AttributeComp)
			{
				AttributeComp->ApplyHealthChange(-DamageAmount);
			}
		}
	}
	Explode();
}