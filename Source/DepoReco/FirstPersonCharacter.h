// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "FirstPersonCharacter.generated.h"

const float DEFAULT_AUDIO_QUEUE_LIFETIME = 10.f;

UCLASS()
class DEPORECO_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<USoundBase*> SoundsToPlay;

	// Represents the amount of time a sound would be able to live in the queue without being played. This is checked upon enqueuing a new sound and determined whether the new sound is added in the first place.
	UPROPERTY(EditAnywhere, Category = Audio)
	float LifetimeInQueue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio)
	UAudioComponent* SoundPlayer;

	// If there is a sound in the queue and this audio component is playing no sounds, then the top sound of the queue will be taken out of the queue and played.
	UFUNCTION(BlueprintCallable)
	void AssessSoundQueueStatus();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	// Currently unused but implemented for practice. Sets jump flag when key is pressed.
	UFUNCTION()
	void Unused_StartJump();

	// Currently unused but implemented for practice. Sets jump flag when key is released.
	UFUNCTION()
	void Unused_StopJump();

	// FPS Camera.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* FirstPersonJarMesh;

	// First-person mesh (tool), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* FirstPersonToolMesh;

	UPROPERTY(EditAnywhere, Category = Audio)
	TArray<USoundBase*> SuccessSounds;

	UPROPERTY(EditAnywhere, Category = Audio)
	TArray<USoundBase*> FailureSounds;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<USoundBase*>& GetSuccessSounds() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<USoundBase*>& GetFailureSounds() const;

	/// <summary>
	/// If true, a new sound can be added to the queue. If false, attempting to call EnqueueSound will not result in any sounds being added.
	/// This is based on the length of the queue and the state of the current sounds being played, so if this is false you should just try again later.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool IsAcceptingSoundsToEnqueue() const;

	UFUNCTION(BlueprintCallable)
	bool IsAcceptingSoundsToEnqueueWithLifetime(float lifetimeSeconds) const;

	/// <summary>
	/// Attempts to add a sound to the queue. If there are no sounds in the queue, this one will be played immediately. Returns whether the attempt to add the sound was successful.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool EnqueueSound(USoundBase* soundToPlay);

	UFUNCTION(BlueprintCallable)
	bool EnqueueSoundWithLifetime(USoundBase* soundToPlay, float lifetimeSeconds);

	// Puts the sound at the back of the queue without checking for lifetime.
	UFUNCTION(BlueprintCallable)
	void ForceEnqueueSound(USoundBase* soundToPlay);

	UFUNCTION(BlueprintCallable)
	void ForceSoundToFrontOfQueue(USoundBase* soundToPlay);
};
