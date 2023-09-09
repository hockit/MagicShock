// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MAttributeComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange, AActor*, Instigator, UMAttributeComponent*, OwnComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICSHOCK_API UMAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMAttributeComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(float Delta);

protected:

	UPROPERTY(EditDefaultsOnly)
	float Health;
};
