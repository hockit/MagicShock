// Fill out your copyright notice in the Description page of Project Settings.


#include "MPickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MAttributeComponent.h"

// Sets default values
AMPickupItem::AMPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>("BottleMesh");
	RootComponent = BottleMesh;
}


void AMPickupItem::Interact_Implementation(APawn* InstigatorPawn)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, EffectVFX, GetActorLocation());
	UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(InstigatorPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
	if (AttributeComp && !AttributeComp->IsFullHealth())
	{
		AttributeComp->ApplyHealthChange(20.f);
	}
	Destroy();
}