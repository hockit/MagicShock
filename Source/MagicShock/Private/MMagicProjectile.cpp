// Fill out your copyright notice in the Description page of Project Settings.


#include "MMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "MAttributeComponent.h"

AMMagicProjectile::AMMagicProjectile()
{
	SphereComp->SetSphereRadius(20.f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMMagicProjectile::OnActorOverlap);

	DamageAmount = 25.f;
}

void AMMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);
			Explode();
		}
	}
}