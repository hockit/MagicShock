// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MAICharacter.h"
#include "MAttributeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMAICharacter::AMAICharacter()
{
	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChange.AddDynamic(this, &AMAICharacter::OnHealthChange);
}

void AMAICharacter::OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwnComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		if (NewHealth <= 0.f)
		{
			
			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Killed");
			}

			
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathVFX, GetActorLocation());
			SetLifeSpan(10.f);
			
		}
	}
}

void AMAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComponent();
		BlackBoardComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 5.f, true);
	}
}
