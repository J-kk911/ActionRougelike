// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JAttributeComponent.h"

// Sets default values for this component's properties
UJAttributeComponent::UJAttributeComponent()
{
	Health = 100.0f;
}


bool UJAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UJAttributeComponent::ApplyHealthChange(float Delta)
{
	//UE_LOG(LogTemp, Warning, TEXT("ATTACK!!"))

	if (Health == 0)return false;
	Health += Delta;
	if (Health < 0) Health = 0;
	if (Health > 100) Health = 100;
	OnHealthChanged.Broadcast(nullptr,this,Health,Delta);
	return true;
}

float UJAttributeComponent::GetHealth()
{
	return this->Health;
}


