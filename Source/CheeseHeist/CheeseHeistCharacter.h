// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
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
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACheeseHeistCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rat)
	float RatAnimThrowDelay;

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

		/** END Anim Values */


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

		/** Rat Anims */

	bool bHasRat;

	UFUNCTION()
	void StartRatThrow();

	UFUNCTION()
	void ThrowRat();

	UFUNCTION()
	void StartRatPickup();

	UFUNCTION()
	void PickupRat();

		/** END Rat Anims */
};

