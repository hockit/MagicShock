// Fill out your copyright notice in the Description page of Project Settings.


#include "MExplosiveProjectile.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "MAttributeComponent.h"

AMExplosiveProjectile::AMExplosiveProjectile()
{
	SphereComp->SetSphereRadius(20.f);
}

void AMExplosiveProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		SphereComp->SetSphereRadius(100.f);
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

		for (auto Actor : OverlappingActors)
		{
			UE_LOG(LogTemp, Display, TEXT("Actor damage by explosive: %s"), *Actor->GetName());
		}
	}
	Explode();
}