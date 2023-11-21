// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttributeComponent.h"

UMAttributeComponent::UMAttributeComponent()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
}

bool UMAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

float UMAttributeComponent::GetHealthMax() const
{
	return MaxHealth;
}

float UMAttributeComponent::GetCurrentHealth() const
{
	return Health;
}

bool UMAttributeComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

bool UMAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);

	float ActualDelta = Health - OldHealth;
	OnHealthChange.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}

