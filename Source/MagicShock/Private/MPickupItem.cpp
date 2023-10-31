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
	UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(InstigatorPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
	if (AttributeComp && !AttributeComp->IsFullHealth())
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, EffectVFX, GetActorLocation());
		AttributeComp->ApplyHealthChange(20.f);
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("You have full health!"));
	}
}