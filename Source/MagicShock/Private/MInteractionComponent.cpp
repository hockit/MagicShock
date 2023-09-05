// Fill out your copyright notice in the Description page of Project Settings.


#include "MInteractionComponent.h"
#include "MGameplayInterface.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UMInteractionComponent::UMInteractionComponent()
{
	
}


void UMInteractionComponent::PrimaryInteract()
{
	TArray<FHitResult> Hits;

	FVector EyeLocation;
	FRotator EyeRotation;

	AActor* MyOwner = GetOwner();
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLocation = EyeLocation + (EyeRotation.Vector() * 500);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	float Radius = 20.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLocation,FQuat::Identity, ObjectQueryParams, Shape);

	FColor ColorLine = bBlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<UMGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IMGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 24, ColorLine, false, 2.f);
	}
	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, ColorLine, false, 2.f, 0, 2.f);
}