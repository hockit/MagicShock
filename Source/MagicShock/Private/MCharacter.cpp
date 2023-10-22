// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MInteractionComponent.h"
#include "MAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundBase.h"


// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(RootComponent);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
	GunMesh->SetupAttachment(CameraComp);

	InteractionComp = CreateDefaultSubobject<UMInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
	bIsCrouch = false;
	DamageAmount = 20.f;
}

void AMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChange.AddDynamic(this, &AMCharacter::OnHealthChange);
}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMCharacter::Jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMCharacter::Crouch);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AMCharacter::SecondaryAttack);
}


// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMCharacter::Crouch()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		if (!bIsCrouch)
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.f;
			GetCapsuleComponent()->SetCapsuleHalfHeight(44.f);
			bIsCrouch = true;			
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
			GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
			bIsCrouch = false;
		}
	}
	
}

void AMCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AMCharacter::PrimaryAttack()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleVFX, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	GetActorEyesViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * 5000;

	FHitResult Hit;
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bSuccess = GetWorld()->LineTraceSingleByObjectType(Hit, Location, End, ObjectParams, Params);
	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Blue, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			UMAttributeComponent* AttributeComponent = Cast<UMAttributeComponent>(HitActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
			if (AttributeComponent)
			{
				AttributeComponent->ApplyHealthChange(-DamageAmount);
			}
		}
	}
}


void AMCharacter::SecondaryAttack()
{
	SpawnProjectile(ProjectileClass);
}

void AMCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FVector PlayerLocation = GunMesh->GetSocketLocation("MuzzleFlashSocket");
		FRotator PlayerRotation = CameraComp->GetComponentRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ClassToSpawn, PlayerLocation, PlayerRotation, SpawnParams);
	}
}


void AMCharacter::OnHealthChange(AActor* InstigatorActor, UMAttributeComponent* OwnComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, this->GetActorLocation());
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, this->GetActorLocation());
	}
}