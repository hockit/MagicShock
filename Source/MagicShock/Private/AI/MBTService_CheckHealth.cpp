// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTService_CheckHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MAttributeComponent.h"
#include "AIController.h"

void UMBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		if (ensure(AIController))
		{
			APawn* AIPawn = AIController->GetPawn();
			if (ensure(AIPawn))
			{
				UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(AIPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
				if(ensure(AttributeComp))
				{
					bool bIsLowHealth = AttributeComp->GetCurrentHealth() <= 20.f;

					BlackboardComp->SetValueAsBool(HealthLevelKey.SelectedKeyName, bIsLowHealth);
				}
			}
		}
	}
}