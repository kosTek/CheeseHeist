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
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"

#include "RatThrowObject.h"
#include "RatCharacter.h"
#include "InteractActor.h"
#include "CollectActor.h"
#include "BagObject.h"

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

	RatMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RatMesh"));
	RatMesh->SetOnlyOwnerSee(true);
	RatMesh->SetupAttachment(Mesh1P, FName("Wrist_RSocket"));
	RatMesh->bCastDynamicShadow = false;
	RatMesh->CastShadow = false;
	RatMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	bHasRat = true;

	bCanPickupRat = false;

	InteractionRange = 100.f;

	RatAnimThrowDelay = 0.7f;
	RatAnimPickupDelay = 0.6f;

	CheeseWheelsInBag = 0;
	CheeseSlicesInBag = 0;
	CollectablesFound = 0;

	MaxCheeseWheelsInBag = 2;
	MaxCheeseSlicesInBag = 4;

	BagThrowForce = 90000.f;

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

		// Throw Bag
		EnhancedInputComponent->BindAction(ThrowBagAction, ETriggerEvent::Started, this, &ACheeseHeistCharacter::ThrowBag);

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

	if (bHasRat) {
		if (bRatThrowAnimActive) { return; }

		bRatThrowAnimActive = true;

		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (!AnimInstance) { return; }

		AnimInstance->Montage_Play(AnimStartRatThrow);
		GetWorldTimerManager().SetTimer(TRatThrow, this, &ACheeseHeistCharacter::ThrowRat, RatAnimThrowDelay, false, RatAnimThrowDelay);

	} else {
		if (!bCanSwitch) { return; }

		AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), Rat);

		ARatCharacter* RatCharacter = Cast<ARatCharacter>(Actor);

		if (RatCharacter != nullptr) {

			AController* PlayerController = GetController();

			PlayerController->UnPossess();
			PlayerController->Possess(RatCharacter);

			OnSwitchCharacter.Broadcast();
		}
	}
}

void ACheeseHeistCharacter::ThrowRat() {

	if (bHasRat) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.bNoFail;

		ARatThrowObject* RatObject = GetWorld()->SpawnActor<ARatThrowObject>(RatThrowableObject, FirstPersonCameraComponent->GetComponentLocation() + ( FirstPersonCameraComponent->GetForwardVector() * 100), this->GetActorRotation(), SpawnInfo);
		RatMesh->SetVisibility(false);

		RatObject->Mesh->AddImpulseAtLocation(FirstPersonCameraComponent->GetForwardVector() * 15000.f, RatObject->GetActorLocation());

		bHasRat = false;
		bRatThrowAnimActive = false;

		OnThrowRat.Broadcast();
	}

}

void ACheeseHeistCharacter::StartRatPickup() {
	if (!bHasRat) {
		bCanSwitch = false;

		if (bRatPickupAnimActive) { return; }

		bRatPickupAnimActive = true;

		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (!AnimInstance) { return; }

		AnimInstance->Montage_Play(AnimPickupRat);
		GetWorldTimerManager().SetTimer(TRatPickup, this, &ACheeseHeistCharacter::PickupRat, RatAnimPickupDelay, false, RatAnimPickupDelay);
	}
}

void ACheeseHeistCharacter::PickupRat() {

	auto* RatCharacter = UGameplayStatics::GetActorOfClass(GetWorld(), ARatCharacter::StaticClass());
	//ARatCharacter* RatCharacter = Cast<ARatCharacter>(Actor);

	if (RatCharacter != nullptr) {
		RatCharacter->Destroy();
		RatMesh->SetVisibility(true);
	}

	bRatPickupAnimActive = false;
	bCanSwitch = true;
	bHasRat = true;

	OnPickupRat.Broadcast();

}

void ACheeseHeistCharacter::Interact() {

	if (bCanPickupRat) {
		StartRatPickup();

		return;
	}

	if (TargetInteractObject != nullptr) {
		TargetInteractObject->Interact();
	}

}

void ACheeseHeistCharacter::InteractTrace() {

	FHitResult HitResult;

	FVector StartVector = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector();
	FVector EndVector = StartVector + (FirstPersonCameraComponent->GetForwardVector() * InteractionRange);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	//DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Blue, false, 1, 0, 1);

	bool GotHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector, ECC_Visibility, CollisionParams);

	if (GotHit) {

		ARatCharacter* RatCharacterObject = Cast<ARatCharacter>(HitResult.GetActor());

		if (RatCharacterObject) {
			bCanPickupRat = true;

			//UE_LOG(LogTemp, Warning, TEXT("Can pickup rat"));

			return;
		}

		auto* Object = Cast<AInteractActor>(HitResult.GetActor());

		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), Object);
		if (Object != nullptr && !Object->GetCanInteract()) {
			SetInteractObject(Object);
		} else {
			SetInteractObject(nullptr);
		}
		
		return;

	}

	bCanPickupRat = false;
	SetInteractObject(nullptr);
}

void ACheeseHeistCharacter::SetInteractObject(AInteractActor* Object) {

	TargetInteractObject = Object;

}

void ACheeseHeistCharacter::CollectObject(ECollectableType ObjectType, ACollectActor* Actor) {
	
	if (Actor == nullptr) { return; }

	if (ObjectType == ECollectableType::CHEESEWHEEL) {

		if (CheeseWheelsInBag + 1 > MaxCheeseWheelsInBag) {
			UE_LOG(LogTemp, Warning, TEXT("[Collectable] Too many collected!"));
			return;
		}

		CheeseWheelsInBag += 1;
		UE_LOG(LogTemp, Warning, TEXT("[Collectable] Cheese Wheel collected! %i in bag"), CheeseWheelsInBag);
	}

	if (ObjectType == ECollectableType::CHEESESLICE) {

		if (CheeseSlicesInBag + 1 > MaxCheeseSlicesInBag) {
			UE_LOG(LogTemp, Warning, TEXT("[Collectable] Too many collected!"));
			return;
		}

		CheeseSlicesInBag += 1;
		UE_LOG(LogTemp, Warning, TEXT("[Collectable] Cheese Slice collected! % i in bag"), CheeseSlicesInBag);
	}

	if (ObjectType == ECollectableType::COLLECTABLE) {
		CollectablesFound += 1;
		UE_LOG(LogTemp, Warning, TEXT("[Collectable] Collectable found!"));
	}

	Actor->Destroy();

}

void ACheeseHeistCharacter::ThrowBag() {

	if (BagObject == nullptr) { return; }

	if ((CheeseWheelsInBag == 0) && (CheeseSlicesInBag == 0)) { return; }

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.bNoFail;

	ABagObject* Object = GetWorld()->SpawnActor<ABagObject>(BagObject, FirstPersonCameraComponent->GetComponentLocation() - FVector(0,0,40) + (FirstPersonCameraComponent->GetForwardVector() * 100), this->GetActorRotation(), SpawnInfo);

	//Object->StaticMesh->AddImpulseAtLocation(FirstPersonCameraComponent->GetForwardVector() * 15000.f, Object->GetActorLocation());
	Object->SetContent(CheeseWheelsInBag, CheeseSlicesInBag);
	Object->StaticMesh->AddForce(FirstPersonCameraComponent->GetForwardVector() * BagThrowForce * Object->StaticMesh->GetMass());

	CheeseWheelsInBag -= CheeseWheelsInBag;
	CheeseSlicesInBag -= CheeseSlicesInBag;

}

void ACheeseHeistCharacter::PickupBag(ABagObject* Bag) {

	if (Bag == nullptr) { return; }
	
	FVector2D Contents = Bag->GetContent();
	int Wheels = Contents.X;
	int Slices = Contents.Y;

	if ((CheeseWheelsInBag + Wheels > MaxCheeseWheelsInBag) || (CheeseSlicesInBag + Slices > MaxCheeseSlicesInBag)) {
		// Notify the player

		UE_LOG(LogTemp, Warning, TEXT("[Collectable] Contents exceed the capacity!"));
		return; 
	}

	CheeseWheelsInBag += Wheels;
	CheeseSlicesInBag += Slices;

	Bag->Destroy();
}