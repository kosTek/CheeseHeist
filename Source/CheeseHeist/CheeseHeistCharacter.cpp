// Copyright Epic Games, Inc. All Rights Reserved.

#include "CheeseHeistCharacter.h"
#include "CheeseHeistProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "RatThrowObject.h"
#include "RatCharacter.h"
#include "InteractActor.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACheeseHeistCharacter

ACheeseHeistCharacter::ACheeseHeistCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	bHasRat = true;

	InteractionRange = 100.f;

	RatAnimThrowDelay = 0.7f;

}

void ACheeseHeistCharacter::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
		//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void ACheeseHeistCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


	InteractTrace();
}

//////////////////////////////////////////////////////////////////////////// Input

void ACheeseHeistCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACheeseHeistCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACheeseHeistCharacter::Look);

		// Throw Rat
		EnhancedInputComponent->BindAction(ThrowRatAction, ETriggerEvent::Started, this, &ACheeseHeistCharacter::StartRatThrow);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACheeseHeistCharacter::Interact);
	}else {
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACheeseHeistCharacter::Move(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr){
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACheeseHeistCharacter::Look(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACheeseHeistCharacter::SetHasRifle(bool bNewHasRifle) {
	bHasRifle = bNewHasRifle;
}

bool ACheeseHeistCharacter::GetHasRifle() {
	return bHasRifle;
}

void ACheeseHeistCharacter::StartRatThrow() {

}

void ACheeseHeistCharacter::ThrowRat() {

	if (bHasRat) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.bNoFail;

		ARatThrowObject* RatObject = GetWorld()->SpawnActor<ARatThrowObject>(RatThrowableObject, FirstPersonCameraComponent->GetComponentLocation() + ( FirstPersonCameraComponent->GetForwardVector() * 100), this->GetActorRotation(), SpawnInfo);

		RatObject->Mesh->AddImpulseAtLocation(FirstPersonCameraComponent->GetForwardVector() * 15000.f, RatObject->GetActorLocation());

		bHasRat = false;
	} else if (!bHasRat){

		AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), Rat);

		ARatCharacter* RatCharacter = Cast<ARatCharacter>(Actor);

		if (RatCharacter != nullptr) {

			AController* PlayerController = GetController();

			PlayerController->UnPossess();
			PlayerController->Possess(RatCharacter);
		}


	}

}

void ACheeseHeistCharacter::StartRatPickup() {
	return;
}

void ACheeseHeistCharacter::PickupRat() {
	return;
}

void ACheeseHeistCharacter::Interact() {

	if (TargetInteractObject != nullptr) {
		TargetInteractObject->OnInteract();
	}

}

void ACheeseHeistCharacter::InteractTrace() {

	FHitResult HitResult;

	FVector StartVector = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector();
	FVector EndVector = StartVector + (FirstPersonCameraComponent->GetForwardVector() * InteractionRange);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool GotHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector, ECC_Visibility, CollisionParams);

	if (GotHit) {

		auto* Object = Cast<AInteractActor>(HitResult.GetActor());

		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), Object);

		SetInteractObject(Object);

		return;

	}

	SetInteractObject(nullptr);
}

void ACheeseHeistCharacter::SetInteractObject(AInteractActor* Object) {

	TargetInteractObject = Object;

}
