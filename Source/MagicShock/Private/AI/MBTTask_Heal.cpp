// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTTask_Heal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "MAttributeComponent.h"

EBTNodeResult::Type UMBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		APawn* AIPawn = Cast<APawn>(AIController->GetPawn());
		if (AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		UMAttributeComponent* AttributeComp = Cast<UMAttributeComponent>(AIPawn->GetComponentByClass(UMAttributeComponent::StaticClass()));
		if (AttributeComp == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		bool bIsHeal = AttributeComp->ApplyHealthChange(AttributeComp->GetHealthMax());

		UE_LOG(LogTemp, Display, TEXT("AI Character is healed"));
		return bIsHeal ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}