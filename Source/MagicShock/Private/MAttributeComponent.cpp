// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttributeComponent.h"

// Sets default values for this component's properties
UMAttributeComponent::UMAttributeComponent()
{
	Health = 100.f;
}

bool UMAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool UMAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChange.Broadcast(nullptr, this, Health, Delta);

	return true;
}