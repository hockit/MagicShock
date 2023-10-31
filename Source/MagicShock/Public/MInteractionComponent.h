// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MInteractionComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICSHOCK_API UMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UMInteractionComponent();

	void PrimaryInteract();

protected:
	float MaxRange;
};