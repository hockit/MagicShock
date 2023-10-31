// Fill out your copyright notice in the Description page of Project Settings.


#include "MItemChest.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


AMItemChest::AMItemChest()
{
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    RootComponent = BaseMesh;

    LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
    LidMesh->SetupAttachment(BaseMesh);

    TreasureMesh = CreateDefaultSubobject<UStaticMeshComponent>("TreasureMesh");
    TreasureMesh->SetupAttachment(BaseMesh);

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(BaseMesh);

    TargetRoll = -130;
}

void AMItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
    LidMesh->SetRelativeRotation(FRotator(0, 0, TargetRoll));
}

