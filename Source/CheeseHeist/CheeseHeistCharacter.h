// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Enumerations.h"
#include "CheeseHeistCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class ARatThrowObject;
class ARatCharacter;
class AInteractActor;
class UAnimMontage;
class ACollectActor;
class ABagObject;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACheeseHeistCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* RatMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	// Actions
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Throw Rat Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowRatAction;

	/** Throw Bag Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowBagAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Interact Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	// End Actions

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ARatThrowObject> RatThrowableObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Rat;

	
public:
	ACheeseHeistCharacter();
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = Interactable)
	AInteractActor* GetTargetInteractObject() { return TargetInteractObject; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
	float InteractionRange;

		/** Anim Montages */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* AnimStartRatThrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* AnimPickupRat;

		/** END Anim Montages */

		/** Anim Values */

	UFUNCTION(BlueprintCallable, Category = Rat)
	bool GetHasRat() { return bHasRat; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rat)
	float RatAnimThrowDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rat)
	float RatAnimPickupDelay;

		/** END Anim Values */

		/** Anim Timers */

	UPROPERTY()
	FTimerHandle TRatThrow;

	UPROPERTY()
	FTimerHandle TRatPickup;

		/** END Anim Timers*/

		/** Collectables & Throw Bags */

	UFUNCTION(BlueprintCallable, Category = Collectable)
	void CollectObject(ECollectableType ObjectType, ACollectActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collectable)
	int MaxCheeseWheelsInBag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collectable)
	int MaxCheeseSlicesInBag;

	/** Handles picking up the bag by the player */
	UFUNCTION(Category = Collectable)
	void PickupBag(ABagObject* Bag);

	/** Bag Object used to store collected loot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collectable)
	TSubclassOf<ABagObject> BagObject;

	/** The force that the bag will experience when player throws it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collectable)
	float BagThrowForce;

		/** END Collectables & Throw Bags */
	
protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	UPROPERTY()
	AInteractActor* TargetInteractObject;

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void InteractTrace();

	UFUNCTION()
	void SetInteractObject(AInteractActor* Object);

		/** Rat Interaction */

	UPROPERTY()
	bool bRatThrowAnimActive{ false };

	UPROPERTY()
	bool bRatPickupAnimActive{ false };
	
	UPROPERTY()
	bool bCanSwitch{ true };

	UPROPERTY()
	bool bHasRat;

	UFUNCTION()
	void StartRatThrow();

	UFUNCTION()
	void ThrowRat();

	UFUNCTION()
	void StartRatPickup();

	UFUNCTION()
	void PickupRat();

	UPROPERTY()
	bool bCanPickupRat{ false };

		/** END Rat Interaction */

		/** Collectables & Throw Bags */

	UPROPERTY()
	int CheeseWheelsInBag;

	UPROPERTY()
	int CheeseSlicesInBag;

	UPROPERTY()
	int CollectablesFound;

	UFUNCTION()
	void ThrowBag();

	UPROPERTY()
	bool bHasBag;

		/** END Collectables & Throw Bags */

};

