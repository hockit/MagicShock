// Fill out your copyright notice in the Description page of Project Settings.


#include "MBaseSpell.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMBaseSpell::AMBaseSpell()
{
	
}


void AMBaseSpell::Explode()
{
	AActor* MyActor = Cast<AActor>(GetOwner());
	if (MyActor != nullptr)
	{
		FVector Location;
		FRotator Rotation;
		MyActor->GetActorEyesViewPoint(Location, Rotation);
		FVector End = Location + Rotation.Vector() * 5000;
			

		FHitResult Hit;
		FCollisionObjectQueryParams ObjectParams;
		ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(MyActor);

		bool bSuccess = GetWorld()->LineTraceSingleByObjectType(Hit, Location, End, ObjectParams, Params);
		if (bSuccess)
		{
			DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectVFX, Hit.Location);
			
		}
	}
}